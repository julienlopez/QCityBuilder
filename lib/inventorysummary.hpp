#ifndef INVENTORYSUMMARY_HPP
#define INVENTORYSUMMARY_HPP

#include "resourceshandler.hpp"

class Inventory;

class InventorySummary
{
public:
    using identifier = ResourcesHandler::type_identifier;

    InventorySummary() = default;

    InventorySummary& operator+=(const Inventory& inventory);

    bool empty() const;

    std::size_t count() const;

    void add(identifier id, std::size_t amount_);

    std::size_t amount(identifier id) const;

    std::size_t spaceOccupied() const;

    void take(identifier id, std::size_t amount_);

    bool hasEnough(identifier id, std::size_t amount_) const;

private:
    using type_map = std::map<identifier, std::size_t>;
    type_map m_map;

    type_map::const_iterator begin() const;
    type_map::const_iterator end() const;
};

#endif // INVENTORYSUMMARY_HPP
