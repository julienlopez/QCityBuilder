#include <catch.hpp>

#include <world/buildingtype.hpp>
#include <world/jsonloader.hpp>
#include <world/jsonsaver.hpp>

#include <sstream>

#include <QJsonObject>

using namespace World;
const std::string strJsonBuildingTypeNoRequirements
    = R"({"name":"test_building","recipes":[],"requirements":[],"size":{"height":5,"width":10}})";
const std::string strJsonBuildingType
    = R"({"name":"test_building","recipes":[],"requirements":[{"amount":10,"name":"wood"},{"amount":20,"name":"stone"}],"size":{"height":5,"width":10}})";
const std::string strJsonBuildingTypeWithOneRecipe
    = R"({"name":"test_building","recipes":[{"inputs":[{"ressource":"Wood","amount":1}],"outputs":[{"ressource":"Plank","amount":1}],"timeout":5}],"requirements":[],"size":{"height":5,"width":10}})";

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

    SECTION("Loading a building type with one recipe")
    {
        ResourcesHandler::loadResources({"Wood", "Plank"});
        const auto idWood = ResourcesHandler::const_instance().idOf("Wood");
        const auto idPlank = ResourcesHandler::const_instance().idOf("Plank");

        const auto bt = JsonLoader::parseBuildingType(JsonLoader::stringToJsonObject(strJsonBuildingTypeWithOneRecipe));
        REQUIRE(bt.recipes.size() == 1);
        const auto& recipe = bt.recipes.front();
        CHECK(recipe.timeout() == 5);
        REQUIRE(recipe.inputs().size() == 1);
        const auto input = recipe.inputs().front();
        CHECK(input.first == idWood);
        CHECK(input.second == 1);
        REQUIRE(recipe.outputs().size() == 1);
        const auto output = recipe.outputs().front();
        CHECK(output.first == idPlank);
        CHECK(output.second == 1);
    }
}
