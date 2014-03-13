#ifndef CITY_HPP
#define CITY_HPP

#include "building.hpp"
#include "map.hpp"

#include <string>

BEGIN_NAMESPACE_WORLD

class City
{
public:
    using container_building = std::vector<Building>;

    City(std::string name_, utils::SizeU size_);
    ~City() = default;

    void add(Building b);

    const Map& map() const;

    const std::string& name() const;

    const container_building& buildings() const;

private:
    std::string m_name;
    Map m_map;
    container_building m_buildings;
};

END_NAMESPACE_WORLD

#endif // CITY_HPP
