#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "inventorysummary.hpp"

class Inventory : private InventorySummary
{
public:
    using identifier = InventorySummary::identifier;

    Inventory(std::size_t capacity_);

    using InventorySummary::empty;

    using InventorySummary::count;

    void add(identifier id, std::size_t amount_);

    using InventorySummary::amount;

    std::size_t capacity() const;

    std::size_t spaceAvailable() const;

    using InventorySummary::spaceOccupied;

    using InventorySummary::take;

    using InventorySummary::hasEnough;

private:
    std::size_t m_capacity;
};

#endif // INVENTORY_HPP
