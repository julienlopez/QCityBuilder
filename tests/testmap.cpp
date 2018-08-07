#include <catch.hpp>

#include <world/city.hpp>

using namespace World;

TEST_CASE("Test Map")
{
    City city{"TestTown", {10, 10}};
    const Map& map = city.map();

    SECTION("Empty On Creation")
    {
        for(std::size_t x = 0; x < map.width(); x++)
            for(std::size_t y = 0; y < map.height(); y++)
                CHECK(map.squareIsEmpty(utils::PointU(x, y)));
    }

    SECTION("Squares Not Empty After Placing A Building")
    {
        city.add(Building(0, utils::PointU(5, 5), utils::RectU(utils::PointU(2, 2), utils::PointU(5, 4))));
        for(std::size_t x = 0; x < map.width(); x++)
            for(std::size_t y = 0; y < map.height(); y++)
            {
                if(x >= 2 && x <= 5 && y >= 2 && y <= 4)
                    CHECK(!map.squareIsEmpty(utils::PointU(x, y)));
                else
                    CHECK(map.squareIsEmpty(utils::PointU(x, y)));
            }
    }

    SECTION("Add Straight Road")
    {
        city.addRoad({{5, 2}, {5, 3}, {5, 4}, {5, 5}});
        for(std::size_t x = 0; x < map.width(); x++)
            for(std::size_t y = 0; y < map.height(); y++)
            {
                if(x == 5 && y >= 2 && y <= 5)
                    CHECK(Map::SquareType::Road == map.squareType(utils::PointU(x, y)));
                else
                    CHECK(Map::SquareType::Empty == map.squareType(utils::PointU(x, y)));
            }
    }
}
