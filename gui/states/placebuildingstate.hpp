#ifndef PLACEBUILDINGSTATE_HPP
#define PLACEBUILDINGSTATE_HPP

#include "istate.hpp"

#include <world/buildingtypehandler.hpp>

class PlaceBuildingState : public iState
{
public:
    PlaceBuildingState(World::BuildingTypeHandler::type_identifier id);

private:
    World::BuildingTypeHandler::type_identifier m_id;

    virtual std::string impl_message() const override;

    virtual utils::RectU impl_area(const utils::PointU& pos) const override;
};

#endif // PLACEBUILDINGSTATE_HPP
