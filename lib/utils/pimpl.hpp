#ifndef PIMPL_HPP
#define PIMPL_HPP

#include "namespace_utils.hpp"

#include <memory>

BEGIN_NAMESPACE_UTILS

template<class Impl>
class pimpl
{
protected:
//    template<class ... Args>
//    pimpl(Args... args): m_ptr(new Impl(std::forward<Args>(args)...))
//    {}

    pimpl(): m_ptr(new Impl)
    {}

    ~pimpl() = default;

    pimpl(const pimpl&) = delete;
    pimpl(pimpl&& p): m_ptr(std::move(p.m_ptr))
    {}

    pimpl& operator=(const pimpl&) = delete;
    pimpl& operator=(pimpl&& p)
    {
        m_ptr = std::move(p.m_ptr);
    }

    Impl& get()
    {
        return *m_ptr;
    }

    const Impl& get() const
    {
        return *m_ptr;
    }

private:
    std::unique_ptr<Impl> m_ptr;
};

END_NAMESPACE_UTILS

#endif // PIMPL_HPP
