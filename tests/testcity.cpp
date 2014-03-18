#include <gtest/gtest.h>

#include <world/buildingtypehandler.hpp>
#include <world/city.hpp>
#include <world/jsonsaver.hpp>
#include <world/jsonloader.hpp>

#include <QJsonObject>

using namespace World;
const std::string strJsonEmptyCity = "{\"buildings\": [],\"name\": \"TestTown\",\"roads\": [],\"size\": {\"height\": 10,\"width\": 10}}";
const std::string strJsonCityWithARoad = "{\"buildings\": [],\"name\": \"TestTown\",\"roads\": [{\"x\": 3,\"y\": 5},{\"x\": 4,\"y\": 5},{\"x\": 5,\"y\": 5},{\"x\": 6,\"y\": 5}],\"size\": {\"height\": 10,\"width\": 10}}";
const std::string strJsonCityWithOneBuilding = "{\"buildings\": [{\"entrance\": {\"x\": 5,\"y\": 5},\"rectangle\": {\"size\": {\"height\": 2,\"width\": 3},\"topleft\": {\"x\": 2,\"y\": 2}},\"type\": \"test_building\"}],\"name\": \"TestTown\",\"roads\": [],\"size\": {\"height\": 10,\"width\": 10}}";

struct TestCity : public ::testing::Test
{
    virtual void SetUp() override
    {
        try
        {
            buildingID = BuildingTypeHandler::instance().getByName(buildingName);
        }
        catch(std::invalid_argument& ex)
        {
            buildingID = BuildingTypeHandler::instance().add(BuildingType(buildingName, {5, 5}, {}));
        }
    }

    std::string buildingName = "test_building";
    BuildingTypeHandler::type_identifier buildingID;
};

TEST_F(TestCity, loadingEmptyCityFromJson)
{
    auto c = JsonLoader::parseCity(JsonLoader::stringToJsonObject(strJsonEmptyCity));
    ASSERT_EQ(utils::SizeU(10, 10), c.map().size());
    ASSERT_EQ("TestTown", c.name());
    ASSERT_TRUE(c.buildings().empty());
}

TEST_F(TestCity, loadingCityWithOneBuildingFromJson)
{
    auto c = JsonLoader::parseCity(JsonLoader::stringToJsonObject(strJsonCityWithOneBuilding));
    ASSERT_EQ(utils::SizeU(10, 10), c.map().size());
    ASSERT_EQ("TestTown", c.name());
    ASSERT_EQ(1, c.buildings().size());
    const auto& b = c.buildings().front();
    ASSERT_EQ(utils::PointU(5, 5), b.entrance());
    ASSERT_EQ(utils::RectU(utils::PointU(2, 2), utils::SizeU(3, 2)), b.rectangle());
    ASSERT_EQ(BuildingTypeHandler::instance().getByName("test_building"), b.type());
}

TEST_F(TestCity, loadingCityWithARoad)
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

struct TestEmptyCity : public TestCity
{
    City city {"TestTown", {10, 10}};
};

TEST_F(TestEmptyCity, savingToJson)
{
    std::ostringstream oss;
    JsonSaver::writeToStream(JsonSaver::saveCity(city), oss);
    ASSERT_EQ(strJsonEmptyCity, oss.str());
}

TEST_F(TestEmptyCity, savingToJsonWithARoad)
{
    city.addRoad({{3, 5}, {4, 5}, {5, 5}, {6, 5}});
    std::ostringstream oss;
    JsonSaver::writeToStream(JsonSaver::saveCity(city), oss);
    ASSERT_EQ(strJsonCityWithARoad, oss.str());
}

struct TestCityWithOneBuilding : public TestEmptyCity
{
    virtual void SetUp() override
    {
        TestEmptyCity::SetUp();
        city.add(Building(buildingID, utils::PointU(5, 5), utils::RectU(utils::PointU(2, 2), utils::PointU(5, 4))));
    }
};

TEST_F(TestCityWithOneBuilding, savingToJson)
{
    std::ostringstream oss;
    JsonSaver::writeToStream(JsonSaver::saveCity(city), oss);
    ASSERT_EQ(strJsonCityWithOneBuilding, oss.str());
}
