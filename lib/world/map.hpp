#ifndef MAP_HPP
#define MAP_HPP

#include "building.hpp"

#include <vector>

BEGIN_NAMESPACE_WORLD

class Map
{
public:
    Map(std::size_t width_, std::size_t height_);

    std::size_t width() const;
    std::size_t height() const;

    bool squareIsEmpty(const utils::PointU& p) const;

    void add(Building b);

private:
    std::size_t m_width;
    std::size_t m_height;

    using container_building = std::vector<Building>;
    container_building m_buildings;
};

END_NAMESPACE_WORLD

#endif // MAP_HPP
