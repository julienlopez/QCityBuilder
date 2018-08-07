#include <catch.hpp>

#include <utils/rect.hpp>

TEST_CASE("Test Rect")
{

    SECTION("Construction With Two Points")
    {
        const utils::PointU topLeft(1, 1);
        const utils::PointU bottomRight(5, 2);
        const utils::SizeU size(5, 2);
        const utils::RectU rect(topLeft, bottomRight);

        CHECK(topLeft == rect.topLeft());
        CHECK(bottomRight == rect.bottomRight());
        CHECK(size == rect.size());
        CHECK(utils::PointU(bottomRight.x(), topLeft.y()) == rect.topRight());
        CHECK(utils::PointU(topLeft.x(), bottomRight.y()) == rect.bottomLeft());
    }

    SECTION("Construction With A Point And A Size")
    {
        const utils::PointU topLeft(1, 1);
        const utils::PointU bottomRight(5, 2);
        const utils::SizeU size(5, 2);
        const utils::RectU rect(topLeft, size);

        CHECK(topLeft == rect.topLeft());
        CHECK(bottomRight == rect.bottomRight());
        CHECK(size == rect.size());
        CHECK(utils::PointU(bottomRight.x(), topLeft.y()) == rect.topRight());
        CHECK(utils::PointU(topLeft.x(), bottomRight.y()) == rect.bottomLeft());
    }
}
