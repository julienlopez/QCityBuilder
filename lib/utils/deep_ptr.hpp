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
    using ptr_t = std::unique_ptr<T>;
    using pointer = typename ptr_t::pointer;
    using element_type = typename ptr_t::element_type;
    using reference = typename std::add_lvalue_reference<element_type>::type;
    using const_reference = typename std::add_const<reference>::type;

    deep_ptr() noexcept = default;

    deep_ptr(pointer t) noexcept : m_ptr(t)
    {}

    template<class U>
    deep_ptr(const deep_ptr<U>& p): m_ptr(p.m_ptr ? COPY_POLICY::clone(*p.m_ptr) : nullptr)
    {}

    deep_ptr(const deep_ptr& p): m_ptr(p.m_ptr ? COPY_POLICY::clone(*p.m_ptr) : nullptr)
    {}

    deep_ptr(deep_ptr&&) = default;

    deep_ptr& operator=(const deep_ptr& p)
    {
        m_ptr.reset(p.m_ptr ? COPY_POLICY::clone(*p.m_ptr) : nullptr);
    }

    deep_ptr& operator=(deep_ptr&&) = default;

    reference operator*() noexcept
    {
        return *m_ptr;
    }

    const_reference operator*() const noexcept
    {
        return *m_ptr;
    }

    bool operator==(const deep_ptr& p) const noexcept
    {
        return m_ptr == p.m_ptr;
    }

    bool operator!=(const deep_ptr& p) const noexcept
    {
        return !(*this == p);
    }

    operator bool () const noexcept
    {
        return (bool)m_ptr;
    }

    pointer operator->() const noexcept
    {
        return m_ptr.get();
    }

    pointer get() const noexcept
    {
        return m_ptr.get();
    }

private:
    ptr_t m_ptr;
};

END_NAMESPACE_UTILS

#endif // DEEP_PTR_HPP
