#include "placeroadstate.hpp"

#include <guihelper.hpp>
#include <world/city.hpp>

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
        World::Map::square_container_t points;
        const auto rect = GuiHelper::findBestLineBetweenTwoPoints(*m_position, pos);
        if(city.isAreaFreeToBuild(rect))
        {
            rect.for_each([&points](const utils::PointU& p) { points.push_back(p); });
            city.addRoad(points);
            m_position.reset();
        }
    }
    else
    {
        m_position = pos;
    }
}
