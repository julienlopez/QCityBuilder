#include "inventorysummary.hpp"
#include "inventory.hpp"

#include <algorithm>
#include <numeric>
#include <string>

InventorySummary& InventorySummary::operator+=(const Inventory& inventory)
{
    for(const auto& p : (InventorySummary&)inventory)
    {
        auto it = m_map.find(p.first);
        if(it == m_map.end())
        {
            m_map[p.first] = p.second;
        }
        else
        {
            it->second += p.second;
        }
    }
    return *this;
}

bool InventorySummary::empty() const
{
    return m_map.empty();
}

std::size_t InventorySummary::count() const
{
    return m_map.size();
}

void InventorySummary::add(identifier id, std::size_t amount_)
{
    m_map[id] += amount_;
}

std::size_t InventorySummary::amount(identifier id) const
{
    auto it = m_map.find(id);
    if(it == m_map.end()) return 0;
    return it->second;
}

std::size_t InventorySummary::spaceOccupied() const
{
    return std::accumulate(m_map.begin(), m_map.end(), 0,
                           [](std::size_t count, const type_map::value_type& p) { return count + p.second; });
}

void InventorySummary::take(identifier id, std::size_t amount_)
{
    auto it = m_map.find(id);
    if(it == m_map.end()) throw std::invalid_argument("not any of " + std::to_string(id));
    if(it->second < amount_)
        throw std::invalid_argument("not enough of " + std::to_string(id) + ": " + std::to_string(it->second) + " < "
                                    + std::to_string(amount_));
    it->second -= amount_;
    if(it->second == 0) m_map.erase(it);
}

bool InventorySummary::hasEnough(identifier id, std::size_t amount_) const
{
    return amount(id) >= amount_;
}

auto InventorySummary::begin() const -> type_map::const_iterator
{
    return m_map.begin();
}

auto InventorySummary::end() const -> type_map::const_iterator
{
    return m_map.end();
}
