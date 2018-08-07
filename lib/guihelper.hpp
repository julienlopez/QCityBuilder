#ifndef GUIHELPER_HPP
#define GUIHELPER_HPP

#include "utils/rect.hpp"

namespace GuiHelper
{
/**
 * @brief findBestLineBetweenTwoPoints
 * @param p1
 * @param p2
 * @return
 * @postcondition returns a rectangle with either a width or a height of 1.
 */
utils::RectU findBestLineBetweenTwoPoints(const utils::PointU& p1, const utils::PointU& p2);
}

#endif // GUIHELPER_HPP
