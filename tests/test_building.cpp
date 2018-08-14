#include <catch.hpp>

#include <resourceshandler.hpp>

#include <world/building.hpp>
#include <world/buildingtypehandler.hpp>

using World::Building;

TEST_CASE("Basic Buildings tests")
{
    const auto house_bt = World::BuildingTypeHandler::instance().add(World::BuildingType{"House", {3, 3}, {}});

    SECTION("Creating a building that can't produce anything has no current recipe")
    {
        Building b{house_bt, {1, 1}, {{1, 0}, utils::SizeU{3, 3}}};
        CHECK_FALSE(b.currentRecipe());
    }

    ResourcesHandler::clear();
    ResourcesHandler::loadResources({"Wood", "Plank"});
    const auto wood_id = ResourcesHandler::const_instance().idOf("Wood");
    const auto plank_id = ResourcesHandler::const_instance().idOf("Plank");
    const auto lumbermill_bt = World::BuildingTypeHandler::instance().add(
        World::BuildingType{"LumberMill", {3, 3}, {}, {Recipe{1, {{wood_id, 1}}, {{plank_id, 1}}}}});

    SECTION("Creating a building with only one possible recipe has it as current recipe upon construction")
    {
        Building b{lumbermill_bt, {1, 1}, {{1, 0}, utils::SizeU{3, 3}}};
        CHECK(b.currentRecipe());
    }

    ResourcesHandler::clear();
    ResourcesHandler::loadResources({"Grain", "Flour", "Food"});
    const auto grain_id = ResourcesHandler::const_instance().idOf("Grain");
    const auto flour_id = ResourcesHandler::const_instance().idOf("Flour");
    const auto food_id = ResourcesHandler::const_instance().idOf("Food");
    const auto kitchen_bt = World::BuildingTypeHandler::instance().add(
        World::BuildingType{"Kitchen",
                            {3, 3},
                            {},
                            {Recipe{1, {{grain_id, 1}}, {{food_id, 1}}}, Recipe{1, {{flour_id, 1}}, {{food_id, 3}}}}});

    SECTION("Creating a building with several possible recipes has no current recipe upon construction")
    {
        Building b{kitchen_bt, {1, 1}, {{1, 0}, utils::SizeU{3, 3}}};
        CHECK_FALSE(b.currentRecipe());
    }

    World::BuildingTypeHandler::instance().clear();
}
