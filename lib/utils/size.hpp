#ifndef SIZE_HPP
#define SIZE_HPP

#include "namespace_utils.hpp"

BEGIN_NAMESPACE_UTILS

template<class T> class Size_
{
public:
    Size_(T width_, T height_): m_width(width_), m_height(height_)
    {}

    T width() const
    {
        return m_width;
    }

    T height() const
    {
        return m_height;
    }

    T volume() const
    {
        return m_width * m_height;
    }

private:
    T m_width;
    T m_height;
};

using Size = Size_<int>;
using SizeU = Size_<std::size_t>;
using SizeF = Size_<double>;

END_NAMESPACE_UTILS

#endif // SIZE_HPP
