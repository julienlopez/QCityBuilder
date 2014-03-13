#include "map.hpp"

BEGIN_NAMESPACE_WORLD

Map::Map(utils::SizeU size_): m_squares(std::move(size_), SquareType::Empty)
{}

std::size_t Map::width() const
{
    return m_squares.width();
}

std::size_t Map::height() const
{
    return m_squares.height();
}

bool Map::squareIsEmpty(const utils::PointU &p) const
{
    return m_squares(p) == SquareType::Empty;
}

void Map::placeBuilding(const utils::RectU& r)
{
    r.for_each([this](const utils::PointU& p){ m_squares(p) = SquareType::Building; });
}

END_NAMESPACE_WORLD
