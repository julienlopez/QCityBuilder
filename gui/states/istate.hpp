#ifndef ISTATE_HPP
#define ISTATE_HPP

#include <utils/noncopiable.hpp>
#include <utils/nonmovable.hpp>
#include <utils/rect.hpp>

#include <string>

namespace World {
    class City;
}

class iState : private utils::noncopiable, private utils::nonmovable
{
public:
    virtual ~iState() = default;

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
