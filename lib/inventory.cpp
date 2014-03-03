#include "inventory.hpp"

Inventory::Inventory()
{
}

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
