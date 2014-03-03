#ifndef POINT_HPP
#define POINT_HPP

#include "namespace_utils.hpp"

BEGIN_NAMESPACE_UTILS

template<class T> class Point_
{
public:
    Point_(T x_, T y_): m_x(x_), m_y(y_)
    {}

    Point_(const Point_&) = default;

    Point_& operator=(const Point_&) = default;

    ~Point_() = default;

    const T& x() const
    {
        return m_x;
    }

    const T& y() const
    {
        return m_y;
    }

private:
    T m_x;
    T m_y;
};

template<class T, class U>
bool operator==(const Point_<T>& p1, const Point_<U>& p2)
{
    return p1.x() == p2.x() && p1.y() == p2.y();
}

using Point = Point_<double>;

END_NAMESPACE_UTILS

#endif // POINT_HPP
