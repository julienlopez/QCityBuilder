#ifndef DEEP_PTR_HPP
#define DEEP_PTR_HPP

#include <memory>

#include "namespace_utils.hpp"

BEGIN_NAMESPACE_UTILS

struct deep_ptr_basic_copy
{
    template<class T>
    static T* clone(const T& t)
    {
        return new T(t);
    }
};

struct deep_ptr_clone_copy
{
    template<class T>
    static T* clone(const T& t)
    {
        return t.clone();
    }
};

template<class T, class COPY_POLICY = deep_ptr_basic_copy> class deep_ptr
{
public:
    deep_ptr(T* t): m_ptr(t)
    {}

    template<class U>
    deep_ptr(const deep_ptr<U>& p): m_ptr(COPY_POLICY::clone(*p.m_ptr))
    {}

    deep_ptr(const deep_ptr& p): m_ptr(COPY_POLICY::clone(*p.m_ptr))
    {}

    deep_ptr(deep_ptr&&) = default;

    deep_ptr& operator=(const deep_ptr& p)
    {
        m_ptr = ptr_t(new T(*p.m_ptr));
    }

    deep_ptr& operator=(deep_ptr&&) = default;

    T& operator*()
    {
        return *m_ptr;
    }

    const T& operator*() const
    {
        return *m_ptr;
    }

    bool operator==(const deep_ptr& p) const
    {
        return m_ptr == p.m_ptr;
    }

    bool operator!=(const deep_ptr& p) const
    {
        return !(*this == p);
    }

private:
    using ptr_t = std::unique_ptr<T>;
    ptr_t m_ptr;
};

END_NAMESPACE_UTILS

#endif // DEEP_PTR_HPP
