#include <gtest/gtest.h>

#include <world/city.hpp>

using namespace World;

struct TestMap : public testing::Test
{
    City city {{10, 10}};
    const Map& map = city.map();
};

TEST_F(TestMap, EmptyOnCreation)
{
    for(std::size_t x = 0; x < map.width(); x++)
        for(std::size_t y = 0; y < map.height(); y++)
            ASSERT_TRUE(map.squareIsEmpty(utils::PointU(x, y)));
}

TEST_F(TestMap, SquaresNotEmptyAfterPlacingABuilding)
{
    city.add(Building(utils::PointU(5, 5), utils::RectU(utils::PointU(2, 2), utils::PointU(5, 4))));
    for(std::size_t x = 0; x < map.width(); x++)
        for(std::size_t y = 0; y < map.height(); y++)
        {
            if(x >= 2 && x <= 5 && y >= 2 && y <= 4)
                ASSERT_FALSE(map.squareIsEmpty(utils::PointU(x, y)));
            else
                ASSERT_TRUE(map.squareIsEmpty(utils::PointU(x, y)));
        }
}
