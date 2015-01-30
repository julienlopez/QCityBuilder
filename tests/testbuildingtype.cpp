#include <gtest/gtest.h>

#include <world/buildingtype.hpp>
#include <world/jsonloader.hpp>
#include <world/jsonsaver.hpp>

#include <QJsonObject>

using namespace World;
const std::string strJsonBuildingTypeNoRequirements = "{\"name\": \"test_building\",\"requirements\": [],\"size\": {\"height\": 5,\"width\": 10}}";
const std::string strJsonBuildingType = "{\"name\": \"test_building\",\"requirements\": [{\"amount\": 10,\"name\": \"wood\"},{\"amount\": 20,\"name\": \"stone\"}],\"size\": {\"height\": 5,\"width\": 10}}";

struct TestBuildingType : public ::testing::Test
{
public:
    virtual void SetUp() override
    {
        ResourcesHandler::clear();
    }
};

TEST_F(TestBuildingType, loadingBuildingTypeNoRequirementsFromJson)
{
    auto bt = JsonLoader::parseBuildingType(JsonLoader::stringToJsonObject(strJsonBuildingTypeNoRequirements));
    ASSERT_EQ("test_building", bt.name);
    ASSERT_EQ(utils::SizeU(10, 5), bt.size);
    ASSERT_TRUE(bt.requirements.empty());
}

TEST_F(TestBuildingType, savingBuildingTypeNoRequirementsToJson)
{
    BuildingType bt = {"test_building", utils::SizeU(10, 5), {}};
    std::ostringstream oss;
    JsonSaver::writeToStream(JsonSaver::saveBuildingType(bt), oss);
    ASSERT_EQ(strJsonBuildingTypeNoRequirements, oss.str());
}

TEST_F(TestBuildingType, loadingBuildingTypeFromJson)
{
    ResourcesHandler::loadResources({"wood", "stone"});
    const auto idWood = ResourcesHandler::const_instance().idOf("wood");
    const auto idStone = ResourcesHandler::const_instance().idOf("stone");
    const auto bt = JsonLoader::parseBuildingType(JsonLoader::stringToJsonObject(strJsonBuildingType));
    ASSERT_EQ("test_building", bt.name);
    ASSERT_EQ(utils::SizeU(10, 5), bt.size);
    ASSERT_EQ(2, bt.requirements.size());

    auto it = bt.requirements.find(idWood);
    ASSERT_NE(it, bt.requirements.end());
    ASSERT_EQ(it->second, 10);

    it = bt.requirements.find(idStone);
    ASSERT_NE(it, bt.requirements.end());
    ASSERT_EQ(it->second, 20);
}

TEST_F(TestBuildingType, savingBuildingTypeToJson)
{
    ResourcesHandler::loadResources({"wood", "stone"});
    const auto idWood = ResourcesHandler::const_instance().idOf("wood");
    const auto idStone = ResourcesHandler::const_instance().idOf("stone");
    const BuildingType bt = {"test_building", utils::SizeU(10, 5), {{idWood, 10}, {idStone, 20}}};
    std::ostringstream oss;
    JsonSaver::writeToStream(JsonSaver::saveBuildingType(bt), oss);
    ASSERT_EQ(strJsonBuildingType, oss.str());
}
