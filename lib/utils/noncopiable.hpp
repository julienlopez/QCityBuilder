#ifndef NONCOPIABLE_HPP
#define NONCOPIABLE_HPP

#include "namespace_utils.hpp"

BEGIN_NAMESPACE_UTILS

/**
  * \brief Defines a non-copiable class.
  */
class noncopiable
{
protected:
    noncopiable() = default;

    noncopiable(const noncopiable&) = delete;

    noncopiable& operator=(const noncopiable&) = delete;
};

END_NAMESPACE_UTILS

#endif // NONCOPIABLE_HPP
