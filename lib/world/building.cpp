#include "building.hpp"

#include <utility>

BEGIN_NAMESPACE_WORLD

Building::Building(type_identifier type_, utils::PointU entrance_, utils::RectU rectangle_)
    : m_type(type_)
    , m_entrance(std::move(entrance_))
    , m_rectangle(std::move(rectangle_))
    , m_producter(50)
{
    if(recipes().size() == 1) m_current_recipe_index = 0;
}

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
    return m_producter.inventory();
}

Inventory& Building::inventory()
{
    return m_producter.inventory();
}

std::optional<Recipe> Building::currentRecipe() const
{
    if(m_current_recipe_index) return recipes()[*m_current_recipe_index];
    return std::nullopt;
}

const BuildingType::recipes_container_t& Building::recipes() const
{
    return BuildingTypeHandler::instance().get(m_type).recipes;
}

END_NAMESPACE_WORLD
