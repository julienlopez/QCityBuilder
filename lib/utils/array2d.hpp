#ifndef ARRAY2D_HPP
#define ARRAY2D_HPP

#include "utils/size.hpp"
#include <utils/point.hpp>

#include <vector>

BEGIN_NAMESPACE_UTILS

template <class T, class CONST_PARAMETER_TYPE = T> class Array2D
{
public:
    Array2D(SizeU size_)
        : m_data(size_.volume())
        , m_size(std::move(size_))
    {
    }

    Array2D(SizeU size_, CONST_PARAMETER_TYPE t)
        : m_data(size_.volume(), t)
        , m_size(std::move(size_))
    {
    }

    std::size_t width() const
    {
        return m_size.width();
    }

    std::size_t height() const
    {
        return m_size.height();
    }

    const SizeU& size() const
    {
        return m_size;
    }

    CONST_PARAMETER_TYPE operator()(const PointU& p) const
    {
        return m_data[p.x() + width() * p.y()];
    }

    T& operator()(const PointU& p)
    {
        return m_data[p.x() + width() * p.y()];
    }

private:
    using type_container = std::vector<T>;
    type_container m_data;
    SizeU m_size;
};

END_NAMESPACE_UTILS

#endif // ARRAY2D_HPP
