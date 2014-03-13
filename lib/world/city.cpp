#include "city.hpp"

BEGIN_NAMESPACE_WORLD

City::City(utils::SizeU size_): m_map(std::move(size_))
{}

void City::add(Building b)
{
    m_map.placeBuilding(b.rectangle());
    m_buildings.push_back(std::move(b));
}

const Map& City::map() const
{
    return m_map;
}

END_NAMESPACE_WORLD
