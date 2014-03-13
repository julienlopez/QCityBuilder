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

const utils::SizeU& Map::size() const
{
    return m_squares.size();
}

bool Map::squareIsEmpty(const utils::PointU &p) const
{
    return squareType(p) == SquareType::Empty;
}

void Map::placeBuilding(const utils::RectU& r)
{
    r.for_each([this](const utils::PointU& p){ m_squares(p) = SquareType::Building; });
}

auto Map::squareType(const utils::PointU& p) const -> SquareType
{
    return m_squares(p);
}

void Map::addRoad(square_container_t squares)
{
    for(const auto& s : squares)
        m_squares(s) = SquareType::Road;
}

END_NAMESPACE_WORLD
