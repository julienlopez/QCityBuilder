#ifndef CITY_HPP
#define CITY_HPP

#include "building.hpp"
#include "map.hpp"

BEGIN_NAMESPACE_WORLD

class City
{
public:
    City(utils::SizeU size_);
    ~City() = default;

    void add(Building b);

    const Map& map() const;

private:
    Map m_map;

    using container_building = std::vector<Building>;
    container_building m_buildings;
};

END_NAMESPACE_WORLD

#endif // CITY_HPP
