#ifndef MAKE_UNIQUE_HPP
#define MAKE_UNIQUE_HPP

#include <memory>

#include "namespace_utils.hpp"

BEGIN_NAMESPACE_UTILS

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

END_NAMESPACE_UTILS

#endif // MAKE_UNIQUE_HPP
