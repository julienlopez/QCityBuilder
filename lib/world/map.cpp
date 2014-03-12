#include "map.hpp"

BEGIN_NAMESPACE_WORLD

Map::Map(std::size_t width_, std::size_t height_): m_width(width_), m_height(height_)
{}

std::size_t Map::width() const
{
    return m_width;
}

std::size_t Map::height() const
{
    return m_height;
}

bool Map::squareIsEmpty(const utils::PointU &p) const
{
    for(const auto& b : m_buildings)
    {
        if(b.rectangle().contains(p))
            return false;
    }
    return true;
}

void Map::add(Building b)
{
    m_buildings.push_back(std::move(b));
}

END_NAMESPACE_WORLD
