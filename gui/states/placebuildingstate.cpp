#include "placebuildingstate.hpp"

#include <world/city.hpp>

PlaceBuildingState::PlaceBuildingState(World::BuildingTypeHandler::type_identifier id)
    : m_id(id)
{
}

utils::RectU PlaceBuildingState::computeRectFromPos(const utils::PointU& pos) const
{
    const auto& bt = World::BuildingTypeHandler::instance().get(m_id);
    return utils::RectU({pos.x() - bt.size.width() / 2, pos.y() - bt.size.width() / 2}, bt.size);
}

std::string PlaceBuildingState::impl_message() const
{
    const auto& bt = World::BuildingTypeHandler::instance().get(m_id);
    return "Placing a " + bt.name;
}

utils::RectU PlaceBuildingState::impl_area(const utils::PointU& pos) const
{
    return computeRectFromPos(pos);
}

void PlaceBuildingState::impl_leftClick(World::City& city, const utils::PointU& pos)
{
    const auto buildingArea = computeRectFromPos(pos);
    if(city.isAreaFreeToBuild(buildingArea))
    {
        city.add(World::Building(m_id, pos, buildingArea));
    }
}
