#include <gtest/gtest.h>

#include <guihelper.hpp>

TEST(TestGuiHelper, findBestLineBetweenTwoPointsSamePoints)
{
    const utils::PointU p1(10, 11);
    const auto res = GuiHelper::findBestLineBetweenTwoPoints(p1, p1);
    ASSERT_EQ(p1, res.topLeft());
    ASSERT_EQ(p1, res.bottomRight());
    ASSERT_EQ(utils::SizeU(1, 1), res.size());
}

TEST(TestGuiHelper, findBestLineBetweenTwoPointsOneToTheRight)
{
    const std::size_t span = 1;
    const utils::PointU p1(10, 11);
    const auto p2 = p1 + utils::PointU(span, 0);
    const auto res = GuiHelper::findBestLineBetweenTwoPoints(p1, p2);
    ASSERT_EQ(p1, res.topLeft());
    ASSERT_EQ(p2, res.bottomRight());
    ASSERT_EQ(utils::SizeU(span + 1, 1), res.size());
}

TEST(TestGuiHelper, findBestLineBetweenTwoPointsOneToTheLeft)
{
    const std::size_t span = 1;
    const utils::PointU p1(10, 11);
    const auto p2 = p1 - utils::PointU(span, 0);
    const auto res = GuiHelper::findBestLineBetweenTwoPoints(p1, p2);
    ASSERT_EQ(p2, res.topLeft());
    ASSERT_EQ(p1, res.bottomRight());
    ASSERT_EQ(utils::SizeU(span + 1, 1), res.size());
}

TEST(TestGuiHelper, findBestLineBetweenTwoPointsToTheRight)
{
    const std::size_t span = 5;
    const utils::PointU p1(10, 11);
    const auto p2 = p1 + utils::PointU(span, 0);
    const auto res = GuiHelper::findBestLineBetweenTwoPoints(p1, p2);
    ASSERT_EQ(p1, res.topLeft());
    ASSERT_EQ(p2, res.bottomRight());
    ASSERT_EQ(utils::SizeU(span + 1, 1), res.size());
}

TEST(TestGuiHelper, findBestLineBetweenTwoPointsToTheLeft)
{
    const std::size_t span = 5;
    const utils::PointU p1(10, 11);
    const auto p2 = p1 - utils::PointU(span, 0);
    const auto res = GuiHelper::findBestLineBetweenTwoPoints(p1, p2);
    ASSERT_EQ(p2, res.topLeft());
    ASSERT_EQ(p1, res.bottomRight());
    ASSERT_EQ(utils::SizeU(span + 1, 1), res.size());
}

TEST(TestGuiHelper, findBestLineBetweenTwoPointsOneToTheBottom)
{
    const std::size_t span = 1;
    const utils::PointU p1(10, 11);
    const auto p2 = p1 + utils::PointU(0, span);
    const auto res = GuiHelper::findBestLineBetweenTwoPoints(p1, p2);
    ASSERT_EQ(p1, res.topLeft());
    ASSERT_EQ(p2, res.bottomRight());
    ASSERT_EQ(utils::SizeU(1, span + 1), res.size());
}

TEST(TestGuiHelper, findBestLineBetweenTwoPointsOneToTheTop)
{
    const std::size_t span = 1;
    const utils::PointU p1(10, 11);
    const auto p2 = p1 - utils::PointU(0, span);
    const auto res = GuiHelper::findBestLineBetweenTwoPoints(p1, p2);
    ASSERT_EQ(p2, res.topLeft());
    ASSERT_EQ(p1, res.bottomRight());
    ASSERT_EQ(utils::SizeU(1, span + 1), res.size());
}

TEST(TestGuiHelper, findBestLineBetweenTwoPointsToTheBottom)
{
    const std::size_t span = 5;
    const utils::PointU p1(10, 11);
    const auto p2 = p1 + utils::PointU(0, span);
    const auto res = GuiHelper::findBestLineBetweenTwoPoints(p1, p2);
    ASSERT_EQ(p1, res.topLeft());
    ASSERT_EQ(p2, res.bottomRight());
    ASSERT_EQ(utils::SizeU(1, span + 1), res.size());
}

namespace utils
{
::std::ostream& operator<<(::std::ostream& o, const SizeU& size)
{
    o << "(" << size.width() << ", " << size.height() << ")";
    return o;
}
::std::ostream& operator<<(::std::ostream& o, const PointU& point)
{
    o << "{" << point.x() << ", " << point.y() << "}";
    return o;
}
::std::ostream& operator<<(::std::ostream& o, const RectU& rect)
{
    o << "[" << rect.topLeft() << ", " << rect.bottomRight() << " => " << rect.size() << "}";
    return o;
}
}

TEST(TestGuiHelper, findBestLineBetweenTwoPointsToTheTop)
{
    const std::size_t span = 5;
    const utils::PointU p1(10, 11);
    const auto p2 = p1 - utils::PointU(0, span);
    const auto res = GuiHelper::findBestLineBetweenTwoPoints(p1, p2);
    ASSERT_EQ(p2, res.topLeft());
    ASSERT_EQ(p1, res.bottomRight());
    ASSERT_EQ(utils::SizeU(1, span + 1), res.size());
}

TEST(TestGuiHelper, findBestLineBetweenTwoPointsDiagonalBottomLeftLeft)
{
    const std::size_t span = 5;
    const utils::PointU p1(10, 11);
    const auto p2 = p1 - utils::PointU(span, span / 2);
    const auto res = GuiHelper::findBestLineBetweenTwoPoints(p1, p2);
    ASSERT_EQ(utils::PointU(p2.x(), p1.y()), res.topLeft());
    ASSERT_EQ(p1, res.bottomRight());
    ASSERT_EQ(utils::SizeU(span + 1, 1), res.size()) << res.size() << " != " << utils::SizeU(span + 1, 1);
}

TEST(TestGuiHelper, findBestLineBetweenTwoPointsDiagonalBottomLeft)
{
    const std::size_t span = 5;
    const utils::PointU p1(10, 11);
    const auto p2 = p1 - utils::PointU(span, span);
    const auto res = GuiHelper::findBestLineBetweenTwoPoints(p1, p2);
    ASSERT_EQ(utils::PointU(p2.x(), p1.y()), res.topLeft());
    ASSERT_EQ(p1, res.bottomRight());
    ASSERT_EQ(utils::SizeU(span + 1, 1), res.size());
}

TEST(TestGuiHelper, findBestLineBetweenTwoPointsDiagonalBottomBottomLeft)
{
    const std::size_t span = 5;
    const utils::PointU p1(10, 11);
    const auto p2 = p1 - utils::PointU(span / 2, span);
    const auto res = GuiHelper::findBestLineBetweenTwoPoints(p1, p2);
    ASSERT_EQ(utils::PointU(p1.x(), p2.y()), res.topLeft());
    ASSERT_EQ(p1, res.bottomRight());
    ASSERT_EQ(utils::SizeU(1, span + 1), res.size());
}
