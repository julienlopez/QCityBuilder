#ifndef UNIQUECONTAINERWITHNAME_HPP
#define UNIQUECONTAINERWITHNAME_HPP

#include "utils/noncopiable.hpp"

#include <vector>
#include <string>

BEGIN_NAMESPACE_UTILS

template<class T>
class UniqueContainerWithName : private utils::noncopiable
{
public:
    using container = std::vector<T>;
    using const_iterator = typename container::const_iterator;

    UniqueContainerWithName(std::string name_): m_name(std::move(name_))
    {}

    bool empty() const
    {
        return m_container.empty();
    }

    std::size_t count() const
    {
        return m_container.size();
    }

    const std::string& name() const
    {
        return m_name;
    }

    void add(T&& t)
    {
        m_container.push_back(std::move(t));
    }

    const_iterator begin() const
    {
        return m_container.begin();
    }

    const_iterator end() const
    {
        return m_container.end();
    }

private:
    std::string m_name;
    container m_container;
};

END_NAMESPACE_UTILS

#endif // UNIQUECONTAINERWITHNAME_HPP
