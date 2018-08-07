#include "inventory.hpp"

Inventory::Inventory(std::size_t capacity_)
    : m_capacity(capacity_)
{
}

void Inventory::add(identifier id, std::size_t amount_)
{
    InventorySummary::add(id, amount_);
}

std::size_t Inventory::capacity() const
{
    return m_capacity;
}

std::size_t Inventory::spaceAvailable() const
{
    return capacity() - spaceOccupied();
}
