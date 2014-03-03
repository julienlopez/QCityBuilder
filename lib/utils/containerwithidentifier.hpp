#ifndef CONTAINERWITHIDENTIFIER_HPP
#define CONTAINERWITHIDENTIFIER_HPP

#include "namespace_utils.hpp"

#include <map>
#include <limits>

BEGIN_NAMESPACE_UTILS

template<class ID, class T>
class containerwithidentifier
{
public:
    containerwithidentifier() = default;
    ~containerwithidentifier() = default;

    using type_identifier = ID;

    bool empty() const
    {
        return m_map.empty();
    }

    ID add(T t)
    {
        ID id = 0;
        if(!m_map.empty())
        {
            id = m_map.rbegin()->first + 1;
        }
        assert(id <= std::numeric_limits<ID>::max());
        m_map.emplace(std::make_pair(id, std::move(t)));
        return id;
    }

    const T& get(ID id) const
    {
        auto it = m_map.find(id);
        if(it == m_map.end())
            throw std::invalid_argument("id " + std::to_string(id) + " dosen't exists.");
        return it->second;
    }

    T& get(ID id)
    {
        auto it = m_map.find(id);
        if(it == m_map.end())
            throw std::invalid_argument("id " + std::to_string(id) + " dosen't exists.");
        return it->second;
    }

private:
    using type_map = std::map<ID, T>;
    type_map m_map;
};


END_NAMESPACE_UTILS

#endif // CONTAINERWITHIDENTIFIER_HPP
