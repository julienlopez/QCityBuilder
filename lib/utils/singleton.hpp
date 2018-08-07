#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <utils/noncopiable.hpp>

BEGIN_NAMESPACE_UTILS

template <class T> class singleton : private noncopiable
{
public:
    static T& instance()
    {
        static T i;
        return i;
    }

    static const T& const_instance()
    {
        return instance();
    }

protected:
    singleton()
    {
    }
};

END_NAMESPACE_UTILS

#endif // SINGLETON_HPP
