#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "buildingtypehandler.hpp"
#include "inventory.hpp"

#include <utils/rect.hpp>

BEGIN_NAMESPACE_WORLD

class Building
{
public:
    using type_identifier = BuildingTypeHandler::type_identifier;

    Building(type_identifier type_, utils::PointU entrance_, utils::RectU rectangle_);

    type_identifier type() const;
    const utils::PointU& entrance() const;
    const utils::RectU& rectangle() const;

    const Inventory& inventory() const;
    Inventory& inventory();

private:
    type_identifier m_type;
    utils::PointU m_entrance;
    utils::RectU m_rectangle;
    Inventory m_inventory;
};

END_NAMESPACE_WORLD

#endif // BUILDING_HPP
