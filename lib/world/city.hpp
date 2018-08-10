#ifndef CITY_HPP
#define CITY_HPP

#include "building.hpp"
#include "map.hpp"
#include "villager.hpp"

#include <string>

class InventorySummary;

BEGIN_NAMESPACE_WORLD

class City
{
public:
    using container_building = std::vector<Building>;
    using VillagerContainer_t = std::vector<Villager>;

    City(std::string name_, utils::SizeU size_);
    ~City() = default;

    void add(Building b);

    const Map& map() const;

    const std::string& name() const;

    const container_building& buildings() const;

    const VillagerContainer_t& villagers() const;

    void addRoad(Map::square_container_t squares);

    bool isAreaFreeToBuild(const utils::RectU& area) const;

    InventorySummary totalInventory() const;

    bool isOutOfBound(const utils::RectU& area) const;

private:
    std::string m_name;
    Map m_map;
    container_building m_buildings;
    VillagerContainer_t m_villagers;
};

END_NAMESPACE_WORLD

#endif // CITY_HPP
