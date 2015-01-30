#include "placeroadstate.hpp"

#include <guihelper.hpp>

std::string PlaceRoadState::impl_message() const
{
    return "Placing a road";
}
#include <QDebug>
utils::RectU PlaceRoadState::impl_area(const utils::PointU& pos) const
{
    if(m_position)
    {
        return GuiHelper::findBestLineBetweenTwoPoints(*m_position, pos);
    }
    else
    {
        return utils::RectU(pos, utils::SizeU(1, 1));
    }
}

void PlaceRoadState::impl_leftClick(World::City& city, const utils::PointU& pos)
{
    if(m_position)
    {

    }
    else
    {
        m_position = pos;
    }
}
