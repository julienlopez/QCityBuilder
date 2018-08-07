#ifndef CONTAINERWITHIDENTIFIER_HPP
#define CONTAINERWITHIDENTIFIER_HPP

#include "namespace_utils.hpp"

#include <cassert>
#include <limits>
#include <map>

BEGIN_NAMESPACE_UTILS

template <class ID, class T> class containerwithidentifier
{
public:
    containerwithidentifier() = default;
    ~containerwithidentifier() = default;

    using type_identifier = ID;
    using type_value = T;

    bool empty() const
    {
        return m_map.empty();
    }

    void clear()
    {
        m_map.clear();
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
        if(it == m_map.end()) throw std::invalid_argument("id " + std::to_string(id) + " dosen't exists.");
        return it->second;
    }

    T& get(ID id)
    {
        auto it = m_map.find(id);
        if(it == m_map.end()) throw std::invalid_argument("id " + std::to_string(id) + " dosen't exists.");
        return it->second;
    }

    ID idOf(const T& t) const
    {
        for(const auto& p : m_map)
        {
            if(p.second == t) return p.first;
        }
        throw std::invalid_argument("unable to find required element in the container.");
        return -1;
    }

    using type_map = std::map<ID, T>;
    using const_iterator = typename type_map::const_iterator;

    const_iterator begin() const
    {
        return m_map.begin();
    }

    const_iterator end() const
    {
        return m_map.end();
    }

    const_iterator cbegin() const
    {
        return m_map.begin();
    }

    const_iterator cend() const
    {
        return m_map.end();
    }

private:
    type_map m_map;
};

END_NAMESPACE_UTILS

#endif // CONTAINERWITHIDENTIFIER_HPP
