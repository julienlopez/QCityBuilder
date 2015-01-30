#ifndef RECT_HPP
#define RECT_HPP

#include "point.hpp"
#include "size.hpp"

#include <cassert>

BEGIN_NAMESPACE_UTILS

template<class T> class Rect_
{
public:
    using type_point = Point_<T>;
    using type_size = Size_<T>;

    Rect_(type_point topLeft_, type_size size_): m_topLeft(topLeft_), m_size(size_)
    {}

    Rect_(type_point topLeft_, type_point bottomRight_): m_topLeft(topLeft_),
        m_size(bottomRight_.x() - topLeft_.x() + 1, bottomRight_.y() - topLeft_.y() + 1)
    {
        assert(bottomRight_.x() > topLeft_.x() && bottomRight_.y() > topLeft_.y());
    }

    const type_point& topLeft() const
    {
        return m_topLeft;
    }

    type_point topRight() const
    {
        return type_point(m_topLeft.x() + m_size.width() - 1, m_topLeft.y());
    }

    type_point bottomLeft() const
    {
        return type_point(m_topLeft.x(), m_topLeft.y() + m_size.height() - 1);
    }

    type_point bottomRight() const
    {
        return type_point(m_topLeft.x() + m_size.width() - 1, m_topLeft.y() + m_size.height() - 1);
    }

    const type_size& size() const
    {
        return m_size;
    }

    bool contains(const type_point& p) const
    {
        auto bt = bottomRight();
        return p.x() >= m_topLeft.x() && p.x() <= bt.x() && p.y() >= m_topLeft.y() && p.y() <= bt.y();
    }

    template<class FCT>
    void for_each(FCT fct) const
    {
        auto bt = bottomRight();
        for(T x = topLeft().x(); x <= bt.x(); x++)
            for(T y = topLeft().y(); y <= bt.y(); y++)
                fct(type_point(x, y));
    }

private:
    type_point m_topLeft;
    type_size m_size;
};

template<class T, class U>
bool operator==(const Rect_<T>& r1, const Rect_<U>& r2)
{
    return r1.topLeft() == r2.topLeft() && r1.size() == r2.size();
}

using Rect = Rect_<int>;
using RectU = Rect_<std::size_t>;
using RectF = Rect_<double>;

END_NAMESPACE_UTILS

#endif // RECT_HPP
