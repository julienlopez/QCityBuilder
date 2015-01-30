#include <gtest/gtest.h>

#include <utils/rect.hpp>

TEST(TestRect, ConstructionWithTwoPoints)
{
    const utils::PointU topLeft(1, 1);
    const utils::PointU bottomRight(5, 2);
    const utils::SizeU size(5, 2);
    const utils::RectU rect(topLeft, bottomRight);

    ASSERT_EQ(topLeft, rect.topLeft());
    ASSERT_EQ(bottomRight, rect.bottomRight());
    ASSERT_EQ(size, rect.size());
    ASSERT_EQ(utils::PointU(bottomRight.x(), topLeft.y()), rect.topRight());
    ASSERT_EQ(utils::PointU(topLeft.x(), bottomRight.y()), rect.bottomLeft());
}

TEST(TestRect, ConstructionWithAPointAndASize)
{
    const utils::PointU topLeft(1, 1);
    const utils::PointU bottomRight(5, 2);
    const utils::SizeU size(5, 2);
    const utils::RectU rect(topLeft, size);

    ASSERT_EQ(topLeft, rect.topLeft());
    ASSERT_EQ(bottomRight, rect.bottomRight());
    ASSERT_EQ(size, rect.size());
    ASSERT_EQ(utils::PointU(bottomRight.x(), topLeft.y()), rect.topRight());
    ASSERT_EQ(utils::PointU(topLeft.x(), bottomRight.y()), rect.bottomLeft());
}
