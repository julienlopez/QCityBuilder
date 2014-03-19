#include "placebuildingstate.hpp"

PlaceBuildingState::PlaceBuildingState(World::BuildingTypeHandler::type_identifier id): m_id(id)
{}

std::string PlaceBuildingState::impl_message() const
{
    const auto& bt = World::BuildingTypeHandler::instance().get(m_id);
    return "Placing a " + bt.name;
}
