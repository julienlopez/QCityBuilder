#ifndef NONINSTANTIABLE_HPP
#define NONINSTANTIABLE_HPP

#include "noncopiable.hpp"

BEGIN_NAMESPACE_UTILS

/**
  * \brief Defines a non-instantiable class.
  */
class noninstantiable : private noncopiable
{
protected:
    noninstantiable() = delete;
};

END_NAMESPACE_UTILS

#endif // NONINSTANTIABLE_HPP
