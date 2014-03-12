#include <gtest/gtest.h>

#include <world/map.hpp>

using namespace World;

struct TestMap : public testing::Test
{
    Map map {10, 10};
};

TEST_F(TestMap, EmptyOnCreation)
{
    for(std::size_t x = 0; x < map.width(); x++)
        for(std::size_t y = 0; y < map.height(); y++)
            ASSERT_TRUE(map.squareIsEmpty(utils::PointU(x, y)));
}

TEST_F(TestMap, SquaresNotEmptyAfterPlacingABuilding)
{
    map.add(Building(utils::PointU(5, 5), utils::RectU(utils::PointU(2, 2), utils::PointU(5, 4))));
    for(std::size_t x = 0; x < map.width(); x++)
        for(std::size_t y = 0; y < map.height(); y++)
        {
            if(x >= 2 && x <= 5 && y >= 2 && y <= 4)
                ASSERT_FALSE(map.squareIsEmpty(utils::PointU(x, y)));
            else
                ASSERT_TRUE(map.squareIsEmpty(utils::PointU(x, y)));
        }
}
