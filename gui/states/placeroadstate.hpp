#ifndef PLACEROADSTATE_HPP
#define PLACEROADSTATE_HPP

#include "istate.hpp"

#include <optional>

class PlaceRoadState : public iState
{
public:
    PlaceRoadState() = default;

private:
    std::optional<utils::PointU> m_position;

    virtual std::string impl_message() const override;

    virtual utils::RectU impl_area(const utils::PointU& pos) const override;

    virtual void impl_leftClick(World::City& city, const utils::PointU& pos) override;
};

#endif // PLACEROADSTATE_HPP
