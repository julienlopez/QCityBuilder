#include "guihelper.hpp"

#include <cmath>

utils::RectU GuiHelper::findBestLineBetweenTwoPoints(const utils::PointU& p1, const utils::PointU& p2)
{
    const auto distanceX = (long)p2.x() - (long)p1.x();
    const auto distanceY = (long)p2.y() - (long)p1.y();

    if(std::abs(distanceX) >= std::abs(distanceY))
    {
        const utils::PointU left(distanceX >= 0 ? p1.x() : p2.x(), p1.y());
        utils::RectU res(left, utils::SizeU(std::abs(distanceX) + 1, 1));
        assert(res.size().width() == 1 || res.size().height() == 1);
        return res;
    }
    else
    {
        const utils::PointU top(p1.x(), distanceY >= 0 ? p1.y() : p2.y());
        utils::RectU res(top, utils::SizeU(1, std::abs(distanceY) + 1));
        assert(res.size().width() == 1 || res.size().height() == 1);
        return res;
    }
}
