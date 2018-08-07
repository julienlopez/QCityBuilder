#include <gtest/gtest.h>

#include <world/buildingtypehandler.hpp>
#include <world/currentcityholder.hpp>
#include <world/city.hpp>
#include <world/jsonsaver.hpp>
#include <world/jsonloader.hpp>

#include <QJsonObject>

using namespace World;
const std::string strJsonEmptyCity = "{\"buildings\": [],\"name\": \"TestTown\",\"roads\": [],\"size\": {\"height\": 10,\"width\": 10}}";
const std::string strJsonCityWithARoad = "{\"buildings\": [],\"name\": \"TestTown\",\"roads\": [{\"x\": 3,\"y\": 5},{\"x\": 4,\"y\": 5},{\"x\": 5,\"y\": 5},{\"x\": 6,\"y\": 5}],\"size\": {\"height\": 10,\"width\": 10}}";
const std::string strJsonCityWithOneBuilding = "{\"buildings\": [{\"entrance\": {\"x\": 5,\"y\": 5},\"rectangle\": {\"size\": {\"height\": 3,\"width\": 4},\"topleft\": {\"x\": 2,\"y\": 2}},\"type\": \"test_building\"}],\"name\": \"TestTown\",\"roads\": [],\"size\": {\"height\": 10,\"width\": 10}}";

TEST_CASE("Test City")
{
    std::string buildingName = "test_building";
    const auto buildingID = BuildingTypeHandler::instance().add(BuildingType(buildingName, {5, 5}, {}));

SECTION("loadingEmptyCityFromJson")
{
    auto c = JsonLoader::parseCity(JsonLoader::stringToJsonObject(strJsonEmptyCity));
    ASSERT_EQ(utils::SizeU(10, 10), c.map().size());
    ASSERT_EQ("TestTown", c.name());
    ASSERT_TRUE(c.buildings().empty());
}

SECTION("loadingCityWithOneBuildingFromJson")
{
    auto c = JsonLoader::parseCity(JsonLoader::stringToJsonObject(strJsonCityWithOneBuilding));
    ASSERT_EQ(utils::SizeU(10, 10), c.map().size());
    ASSERT_EQ("TestTown", c.name());
    ASSERT_EQ(1, c.buildings().size());
    const auto& b = c.buildings().front();
    ASSERT_EQ(utils::PointU(5, 5), b.entrance());
    ASSERT_EQ(utils::RectU(utils::PointU(2, 2), utils::SizeU(4, 3)), b.rectangle());
    ASSERT_EQ(BuildingTypeHandler::instance().getByName("test_building"), b.type());
}

SECTION("loadingCityWithARoad")
{
    auto c = JsonLoader::parseCity(JsonLoader::stringToJsonObject(strJsonCityWithARoad));
    const auto& map = c.map();
    for(std::size_t x = 0; x < map.width(); x++)
        for(std::size_t y = 0; y < map.height(); y++)
        {
            if(x >= 3 && x <= 6 && y == 5)
                ASSERT_EQ(Map::SquareType::Road, map.squareType(utils::PointU(x, y))) << "{" << x << ", " << y << "} != Road";
            else
                ASSERT_EQ(Map::SquareType::Empty, map.squareType(utils::PointU(x, y))) << "{" << x << ", " << y << "} != Empty";
        }
}

}

TEST_CASE("TestEmptyCity")
{
    City city {"TestTown", {10, 10}};

SECTION(TestEmptyCity, savingToJson)
{
    std::ostringstream oss;
    JsonSaver::writeToStream(JsonSaver::saveCity(city), oss);
    ASSERT_EQ(strJsonEmptyCity, oss.str());
}

SECTION(TestEmptyCity, savingToJsonWithARoad)
{
    city.addRoad({{3, 5}, {4, 5}, {5, 5}, {6, 5}});
    std::ostringstream oss;
    JsonSaver::writeToStream(JsonSaver::saveCity(city), oss);
    ASSERT_EQ(strJsonCityWithARoad, oss.str());
}

}

TEST_CASE("TestCityWithOneBuilding")
{
    City city {"TestTown", {10, 10}};
    city.add(Building(buildingID, utils::PointU(5, 5), utils::RectU(utils::PointU(2, 2), utils::PointU(5, 4))));

SECTION(TestCityWithOneBuilding, savingToJson)
{
    std::ostringstream oss;
    JsonSaver::writeToStream(JsonSaver::saveCity(city), oss);
    ASSERT_EQ(strJsonCityWithOneBuilding, oss.str());
}

SECTION(TestCityWithOneBuilding, currentCityHolder)
{
    ASSERT_FALSE(CurrentCityHolder::isInitialized());
    const std::string name = "city1";
    const utils::SizeU size {50, 50};
    CurrentCityHolder::initialize(name, size);
    ASSERT_TRUE(CurrentCityHolder::isInitialized());
    ASSERT_EQ(name, CurrentCityHolder::get().name());
    ASSERT_EQ(size, CurrentCityHolder::get().map().size());
}

SECTION(TestCityWithOneBuilding, isAreaFreeToBuild)
{
    ASSERT_TRUE(city.isAreaFreeToBuild(utils::RectU(utils::PointU(0, 0), utils::PointU(1, 1))));
    ASSERT_FALSE(city.isAreaFreeToBuild(utils::RectU(utils::PointU(1, 1), utils::PointU(2, 2))));
}

TEST_CASE("City With Two Buildings")
{

    City city {"TestTown", {10, 10}};
        ResourcesHandler::clear();

        ResourcesHandler::loadResources({"wood", "stone", "iron"});
        idWood = ResourcesHandler::const_instance().idOf("wood");
        idStone = ResourcesHandler::const_instance().idOf("stone");
        idIron = ResourcesHandler::const_instance().idOf("iron");

        Building b1(buildingID, utils::PointU(1, 1), utils::RectU(utils::PointU(1, 1), utils::PointU(2, 2)));
        b1.inventory().add(idWood, 50);
        b1.inventory().add(idStone, 100);
        city.add(b1);

        Building b2(buildingID, utils::PointU(4, 4), utils::RectU(utils::PointU(3, 3), utils::PointU(4, 4)));
        b2.inventory().add(idStone, 100);
        b2.inventory().add(idIron, 100);
        city.add(b2);
    }

    ResourcesHandler::type_identifier idWood;
    ResourcesHandler::type_identifier idStone;
    ResourcesHandler::type_identifier idIron;

SECTION(TestCityWithTwoBuilding, testTotalInventory)
{
    auto summary = city.totalInventory();
    EXPECT_EQ(summary.amount(idWood), 50);
    EXPECT_EQ(summary.amount(idStone), 200);
    EXPECT_EQ(summary.amount(idIron), 100);
}

}
