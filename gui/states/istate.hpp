#ifndef ISTATE_HPP
#define ISTATE_HPP

#include <utils/rect.hpp>

#include <string>

namespace World
{
class City;
}

class iState
{
public:
    virtual ~iState() = default;

    iState(const iState&) = delete;
    iState(iState&&) = delete;

    iState& operator=(const iState&) = delete;
    iState& operator=(iState&&) = delete;

    std::string message() const;

    utils::RectU area(const utils::PointU& pos) const;

    void leftClick(World::City& city, const utils::PointU& pos);

protected:
    iState() = default;

    virtual std::string impl_message() const = 0;

    virtual utils::RectU impl_area(const utils::PointU& pos) const = 0;

    virtual void impl_leftClick(World::City& city, const utils::PointU& pos) = 0;
};

#endif // ISTATE_HPP
