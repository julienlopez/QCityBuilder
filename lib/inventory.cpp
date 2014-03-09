#include "inventory.hpp"

#include <algorithm>

Inventory::Inventory(std::size_t capacity_): m_capacity(capacity_)
{}

bool Inventory::empty() const
{
    return m_map.empty();
}

std::size_t Inventory::count() const
{
    return m_map.size();
}

void Inventory::add(identifier id, std::size_t amount_)
{
    m_map[id] += amount_;
}

std::size_t Inventory::amount(identifier id) const
{
    auto it = m_map.find(id);
    if(it == m_map.end()) return 0;
    return it->second;
}

std::size_t Inventory::capacity() const
{
    return m_capacity;
}

std::size_t Inventory::spaceAvailable() const
{
    return capacity() - spaceOccupied();
}

std::size_t Inventory::spaceOccupied() const
{
    return std::accumulate(m_map.begin(), m_map.end(), 0,
                           [](std::size_t count, const type_map::value_type& p)
                            { return count + p.second; });
}

void Inventory::take(identifier id, std::size_t amount_)
{
    if(m_map.find(id) == m_map.end()) throw std::invalid_argument("not any of " + std::to_string(id));
    if(m_map[id] < amount_)
        throw std::invalid_argument("not enough of " + std::to_string(id) + ": "
                                    + std::to_string(m_map[id]) + " < " + std::to_string(amount_));
    m_map[id] -= amount_;
}
