#include "placebuildingstate.hpp"

PlaceBuildingState::PlaceBuildingState(World::BuildingTypeHandler::type_identifier id): m_id(id)
{}

std::string PlaceBuildingState::impl_message() const
{
    const auto& bt = World::BuildingTypeHandler::instance().get(m_id);
    return "Placing a " + bt.name;
}

utils::RectU PlaceBuildingState::impl_area(const utils::PointU& pos) const
{
    const auto& bt = World::BuildingTypeHandler::instance().get(m_id);
    return utils::RectU({pos.x() - bt.size.width()/2, pos.y() - bt.size.width()/2}, bt.size);
}
