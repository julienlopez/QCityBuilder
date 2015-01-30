#include "building.hpp"

#include <utility>

BEGIN_NAMESPACE_WORLD

Building::Building(type_identifier type_, utils::PointU entrance_, utils::RectU rectangle_):
    m_type(type_), m_entrance(std::move(entrance_)), m_rectangle(std::move(rectangle_)), m_inventory(50)
{}

auto Building::type() const -> type_identifier
{
    return m_type;
}

const utils::PointU& Building::entrance() const
{
    return m_entrance;
}

const utils::RectU& Building::rectangle() const
{
    return m_rectangle;
}

const Inventory& Building::inventory() const
{
    return m_inventory;
}

Inventory& Building::inventory()
{
    return m_inventory;
}

END_NAMESPACE_WORLD
