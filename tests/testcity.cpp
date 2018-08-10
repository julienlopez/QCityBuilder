#include <catch.hpp>

#include <world/buildingtypehandler.hpp>
#include <world/city.hpp>
#include <world/jsonloader.hpp>
#include <world/jsonsaver.hpp>

#include <sstream>

#include <QJsonObject>

using namespace World;
const std::string strJsonEmptyCity
    = "{\"buildings\":[],\"name\":\"TestTown\",\"roads\":[],\"size\":{\"height\":10,\"width\":10}}";
const std::string strJsonCityWithARoad = "{\"buildings\":[],\"name\":\"TestTown\",\"roads\":[{\"x\":3,\"y\":"
                                         "5},{\"x\":4,\"y\":5},{\"x\":5,\"y\":5},{\"x\":6,\"y\":5}],\"size\":"
                                         "{\"height\":10,\"width\":10}}";
const std::string strJsonCityWithOneBuilding = "{\"buildings\":[{\"entrance\":{\"x\":5,\"y\":5},\"rectangle\":"
                                               "{\"size\":{\"height\":3,\"width\":4},\"topleft\":{\"x\":2,\"y\":"
                                               "2}},\"type\":\"test_building\"}],\"name\":\"TestTown\",\"roads\":"
                                               "[],\"size\":{\"height\":10,\"width\":10}}";

TEST_CASE("Test City")
{
    std::string buildingName = "test_building";
    const auto buildingID = BuildingTypeHandler::instance().add(BuildingType(buildingName, {5, 5}, {}));

    SECTION("loadingEmptyCityFromJson")
    {
        auto c = JsonLoader::parseCity(JsonLoader::stringToJsonObject(strJsonEmptyCity));
        CHECK(utils::SizeU(10, 10) == c.map().size());
        CHECK("TestTown" == c.name());
        CHECK(c.buildings().empty());
    }

    SECTION("loadingCityWithOneBuildingFromJson")
    {
        auto c = JsonLoader::parseCity(JsonLoader::stringToJsonObject(strJsonCityWithOneBuilding));
        CHECK(utils::SizeU(10, 10) == c.map().size());
        CHECK("TestTown" == c.name());
        CHECK(1 == c.buildings().size());
        const auto& b = c.buildings().front();
        CHECK(utils::PointU(5, 5) == b.entrance());
        CHECK(utils::RectU(utils::PointU(2, 2), utils::SizeU(4, 3)) == b.rectangle());
        CHECK(BuildingTypeHandler::instance().getByName("test_building") == b.type());
    }

    SECTION("Loading City With A Road")
    {
        auto c = JsonLoader::parseCity(JsonLoader::stringToJsonObject(strJsonCityWithARoad));
        const auto& map = c.map();
        for(std::size_t x = 0; x < map.width(); x++)
            for(std::size_t y = 0; y < map.height(); y++)
            {
                if(x >= 3 && x <= 6 && y == 5)
                    CHECK(Map::SquareType::Road == map.squareType(utils::PointU(x, y)));
                else
                    CHECK(Map::SquareType::Empty == map.squareType(utils::PointU(x, y)));
            }
    }
}

TEST_CASE("Test Empty City")
{
    City city{"TestTown", {10, 10}};

    SECTION("Saving To Json")
    {
        std::ostringstream oss;
        JsonSaver::writeToStream(JsonSaver::saveCity(city), oss);
        CHECK(strJsonEmptyCity == oss.str());
    }

    SECTION("Saving To Json With A Road")
    {
        city.addRoad({{3, 5}, {4, 5}, {5, 5}, {6, 5}});
        std::ostringstream oss;
        JsonSaver::writeToStream(JsonSaver::saveCity(city), oss);
        CHECK(strJsonCityWithARoad == oss.str());
    }
}

TEST_CASE("Test City With One Building")
{
    std::string buildingName = "test_building";
    const auto buildingID = BuildingTypeHandler::instance().add(BuildingType(buildingName, {5, 5}, {}));

    City city{"TestTown", {10, 10}};
    city.add(Building(buildingID, utils::PointU(5, 5), utils::RectU(utils::PointU(2, 2), utils::PointU(5, 4))));

    SECTION("Saving To Json")
    {
        std::ostringstream oss;
        JsonSaver::writeToStream(JsonSaver::saveCity(city), oss);
        CHECK(strJsonCityWithOneBuilding == oss.str());
    }

    SECTION("Is Area Free To Build")
    {
        CHECK(city.isAreaFreeToBuild(utils::RectU(utils::PointU(0, 0), utils::PointU(1, 1))));
        CHECK(!city.isAreaFreeToBuild(utils::RectU(utils::PointU(1, 1), utils::PointU(2, 2))));
    }
}

TEST_CASE("City With Two Buildings")
{
    std::string buildingName = "test_building";
    const auto buildingID = BuildingTypeHandler::instance().add(BuildingType(buildingName, {5, 5}, {}));

    City city{"TestTown", {10, 10}};
    ResourcesHandler::clear();

    ResourcesHandler::loadResources({"wood", "stone", "iron"});
    const auto idWood = ResourcesHandler::const_instance().idOf("wood");
    const auto idStone = ResourcesHandler::const_instance().idOf("stone");
    const auto idIron = ResourcesHandler::const_instance().idOf("iron");

    Building b1(buildingID, utils::PointU(1, 1), utils::RectU(utils::PointU(1, 1), utils::PointU(2, 2)));
    b1.inventory().add(idWood, 50);
    b1.inventory().add(idStone, 100);
    city.add(b1);

    Building b2(buildingID, utils::PointU(4, 4), utils::RectU(utils::PointU(3, 3), utils::PointU(4, 4)));
    b2.inventory().add(idStone, 100);
    b2.inventory().add(idIron, 100);
    city.add(b2);

    SECTION("Test Total Inventory")
    {
        auto summary = city.totalInventory();
        CHECK(summary.amount(idWood) == 50);
        CHECK(summary.amount(idStone) == 200);
        CHECK(summary.amount(idIron) == 100);
    }
}
