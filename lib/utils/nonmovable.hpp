#ifndef NONMOVABLE_HPP
#define NONMOVABLE_HPP

#include "namespace_utils.hpp"

BEGIN_NAMESPACE_UTILS

/**
  * \brief Defines a non-copiable class.
  */
class nonmovable
{
protected:
    nonmovable(nonmovable&&) = delete;

    nonmovable& operator=(nonmovable&&) = delete;
};

END_NAMESPACE_UTILS

#endif // NONMOVABLE_HPP
