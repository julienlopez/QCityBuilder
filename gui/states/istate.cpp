#include "istate.hpp"

std::string iState::message() const
{
    return impl_message();
}

utils::RectU iState::area(const utils::PointU& pos) const
{
    return impl_area(pos);
}
