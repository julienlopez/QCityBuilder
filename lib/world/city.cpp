#include "city.hpp"

#include "inventorysummary.hpp"

BEGIN_NAMESPACE_WORLD

City::City(std::string name_, utils::SizeU size_)
    : m_name(std::move(name_))
    , m_map(std::move(size_))
{
}

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

auto City::villagers() const -> const VillagerContainer_t&
{
    return m_villagers;
}

void City::addRoad(Map::square_container_t squares)
{
    m_map.addRoad(std::move(squares));
}

bool City::isAreaFreeToBuild(const utils::RectU& area) const
{
    bool res = true;
    area.for_each([&res, this](const utils::PointU& p) { res &= m_map.squareIsEmpty(p); });
    return res;
}

InventorySummary City::totalInventory() const
{
    InventorySummary res;
    for(const auto& building : m_buildings)
    {
        res += building.inventory();
    }
    return res;
}

END_NAMESPACE_WORLD
