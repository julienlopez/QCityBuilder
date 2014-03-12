#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "namespace_world.hpp"

#include <utils/rect.hpp>

BEGIN_NAMESPACE_WORLD

class Building
{
public:
    Building(utils::PointU entrance_, utils::RectU rectangle_);

    const utils::PointU& entrance() const;
    const utils::RectU& rectangle() const;

private:
    utils::PointU m_entrance;
    utils::RectU m_rectangle;
};

END_NAMESPACE_WORLD

#endif // BUILDING_HPP
