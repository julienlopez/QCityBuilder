#include "building.hpp"

#include <utility>

BEGIN_NAMESPACE_WORLD

Building::Building(utils::PointU entrance_, utils::RectU rectangle_): m_entrance(std::move(entrance_)), m_rectangle(std::move(rectangle_))
{}

const utils::PointU& Building::entrance() const
{
    return m_entrance;
}

const utils::RectU& Building::rectangle() const
{
    return m_rectangle;
}

END_NAMESPACE_WORLD
