#include "city.hpp"

BEGIN_NAMESPACE_WORLD

City::City(std::string name_, utils::SizeU size_): m_name(std::move(name_)), m_map(std::move(size_))
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

const std::string& City::name() const
{
    return m_name;
}

auto City::buildings() const -> const container_building&
{
    return m_buildings;
}

void City::addRoad(Map::square_container_t squares)
{
    m_map.addRoad(std::move(squares));
}

END_NAMESPACE_WORLD
