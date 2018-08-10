#include <catch.hpp>

#include <guihelper.hpp>

TEST_CASE("Test Gui Helper")
{

    SECTION("Find Best Line Between Two Points Same Points")
    {
        const utils::PointU p1(10, 11);
        const auto res = GuiHelper::findBestLineBetweenTwoPoints(p1, p1);
        CHECK(p1 == res.topLeft());
        CHECK(p1 == res.bottomRight());
        CHECK(utils::SizeU(1, 1) == res.size());
    }

    SECTION("Find Best Line Between Two Points One To The Right")
    {
        const std::size_t span = 1;
        const utils::PointU p1(10, 11);
        const auto p2 = p1 + utils::PointU(span, 0);
        const auto res = GuiHelper::findBestLineBetweenTwoPoints(p1, p2);
        CHECK(p1 == res.topLeft());
        CHECK(p2 == res.bottomRight());
        CHECK(utils::SizeU(span + 1, 1) == res.size());
    }

    SECTION("Find Best Line Between Two Points One To The Left")
    {
        const std::size_t span = 1;
        const utils::PointU p1(10, 11);
        const auto p2 = p1 - utils::PointU(span, 0);
        const auto res = GuiHelper::findBestLineBetweenTwoPoints(p1, p2);
        CHECK(p2 == res.topLeft());
        CHECK(p1 == res.bottomRight());
        CHECK(utils::SizeU(span + 1, 1) == res.size());
    }

    SECTION("Find Best Line Between Two Points To The Right")
    {
        const std::size_t span = 5;
        const utils::PointU p1(10, 11);
        const auto p2 = p1 + utils::PointU(span, 0);
        const auto res = GuiHelper::findBestLineBetweenTwoPoints(p1, p2);
        CHECK(p1 == res.topLeft());
        CHECK(p2 == res.bottomRight());
        CHECK(utils::SizeU(span + 1, 1) == res.size());
    }

    SECTION("Find Best Line Between Two Points To The Left")
    {
        const std::size_t span = 5;
        const utils::PointU p1(10, 11);
        const auto p2 = p1 - utils::PointU(span, 0);
        const auto res = GuiHelper::findBestLineBetweenTwoPoints(p1, p2);
        CHECK(p2 == res.topLeft());
        CHECK(p1 == res.bottomRight());
        CHECK(utils::SizeU(span + 1, 1) == res.size());
    }

    SECTION("Find Best Line Between Two Points One To The Bottom")
    {
        const std::size_t span = 1;
        const utils::PointU p1(10, 11);
        const auto p2 = p1 + utils::PointU(0, span);
        const auto res = GuiHelper::findBestLineBetweenTwoPoints(p1, p2);
        CHECK(p1 == res.topLeft());
        CHECK(p2 == res.bottomRight());
        CHECK(utils::SizeU(1, span + 1) == res.size());
    }

    SECTION("Find Best Line Between Two Points One To The Top")
    {
        const std::size_t span = 1;
        const utils::PointU p1(10, 11);
        const auto p2 = p1 - utils::PointU(0, span);
        const auto res = GuiHelper::findBestLineBetweenTwoPoints(p1, p2);
        CHECK(p2 == res.topLeft());
        CHECK(p1 == res.bottomRight());
        CHECK(utils::SizeU(1, span + 1) == res.size());
    }

    SECTION("Find Best Line Between Two Points To The Bottom")
    {
        const std::size_t span = 5;
        const utils::PointU p1(10, 11);
        const auto p2 = p1 + utils::PointU(0, span);
        const auto res = GuiHelper::findBestLineBetweenTwoPoints(p1, p2);
        CHECK(p1 == res.topLeft());
        CHECK(p2 == res.bottomRight());
        CHECK(utils::SizeU(1, span + 1) == res.size());
    }

    SECTION("Find Best Line Between Two Points To The Top")
    {
        const std::size_t span = 5;
        const utils::PointU p1(10, 11);
        const auto p2 = p1 - utils::PointU(0, span);
        const auto res = GuiHelper::findBestLineBetweenTwoPoints(p1, p2);
        CHECK(p2 == res.topLeft());
        CHECK(p1 == res.bottomRight());
        CHECK(utils::SizeU(1, span + 1) == res.size());
    }

    SECTION("Find Best Line Between Two Points Diagonal Bottom Left Left")
    {
        const std::size_t span = 5;
        const utils::PointU p1(10, 11);
        const auto p2 = p1 - utils::PointU(span, span / 2);
        const auto res = GuiHelper::findBestLineBetweenTwoPoints(p1, p2);
        CHECK(utils::PointU(p2.x(), p1.y()) == res.topLeft());
        CHECK(p1 == res.bottomRight());
        CHECK(utils::SizeU(span + 1, 1) == res.size());
    }

    SECTION("Find Best Line Between Two Points Diagonal Bottom Left")
    {
        const std::size_t span = 5;
        const utils::PointU p1(10, 11);
        const auto p2 = p1 - utils::PointU(span, span);
        const auto res = GuiHelper::findBestLineBetweenTwoPoints(p1, p2);
        CHECK(utils::PointU(p2.x(), p1.y()) == res.topLeft());
        CHECK(p1 == res.bottomRight());
        CHECK(utils::SizeU(span + 1, 1) == res.size());
    }

    SECTION("Find Best Line Between Two Points Diagonal Bottom Bottom Left")
    {
        const std::size_t span = 5;
        const utils::PointU p1(10, 11);
        const auto p2 = p1 - utils::PointU(span / 2, span);
        const auto res = GuiHelper::findBestLineBetweenTwoPoints(p1, p2);
        CHECK(utils::PointU(p1.x(), p2.y()) == res.topLeft());
        CHECK(p1 == res.bottomRight());
        CHECK(utils::SizeU(1, span + 1) == res.size());
    }
}
