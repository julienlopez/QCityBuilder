#include <catch.hpp>

#include <world/buildingtype.hpp>
#include <world/jsonloader.hpp>
#include <world/jsonsaver.hpp>

#include <sstream>

#include <QJsonObject>

using namespace World;
const std::string strJsonBuildingTypeNoRequirements = "{\"name\": \"test_building\",\"requirements\": [],\"size\": {\"height\": 5,\"width\": 10}}";
const std::string strJsonBuildingType = "{\"name\": \"test_building\",\"requirements\": [{\"amount\": 10,\"name\": \"wood\"},{\"amount\": 20,\"name\": \"stone\"}],\"size\": {\"height\": 5,\"width\": 10}}";

TEST_CASE("Test of Building Type")
{
    ResourcesHandler::clear();

    SECTION("Loading Building Type No Requirements From Json")
    {
        auto bt = JsonLoader::parseBuildingType(JsonLoader::stringToJsonObject(strJsonBuildingTypeNoRequirements));
        CHECK("test_building" == bt.name);
        CHECK(utils::SizeU(10, 5) == bt.size);
        CHECK(bt.requirements.empty());
    }

    SECTION("Saving Building Type No Requirements To Json")
    {
        BuildingType bt = {"test_building", utils::SizeU(10, 5), {}};
        std::ostringstream oss;
        JsonSaver::writeToStream(JsonSaver::saveBuildingType(bt), oss);
        CHECK(strJsonBuildingTypeNoRequirements == oss.str());
    }

    SECTION("Loading Building Type From Json")
    {
        ResourcesHandler::loadResources({"wood", "stone"});
        const auto idWood = ResourcesHandler::const_instance().idOf("wood");
        const auto idStone = ResourcesHandler::const_instance().idOf("stone");
        const auto bt = JsonLoader::parseBuildingType(JsonLoader::stringToJsonObject(strJsonBuildingType));
        CHECK("test_building" == bt.name);
        CHECK(utils::SizeU(10, 5) == bt.size);
        CHECK(bt.requirements.size() == 2);

        auto it = bt.requirements.find(idWood);
        REQUIRE(it != bt.requirements.end());
        CHECK(it->second == 10);

        it = bt.requirements.find(idStone);
        REQUIRE(it != bt.requirements.end());
        CHECK(it->second == 20);
    }

    SECTION("Saving Building Type To Json")
    {
        ResourcesHandler::loadResources({"wood", "stone"});
        const auto idWood = ResourcesHandler::const_instance().idOf("wood");
        const auto idStone = ResourcesHandler::const_instance().idOf("stone");
        const BuildingType bt = {"test_building", utils::SizeU(10, 5), {{idWood, 10}, {idStone, 20}}};
        std::ostringstream oss;
        JsonSaver::writeToStream(JsonSaver::saveBuildingType(bt), oss);
        CHECK(strJsonBuildingType == oss.str());
    }
}
