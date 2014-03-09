#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "ressourceshandler.hpp"

class Inventory
{
public:
    using identifier = RessourcesHandler::type_identifier;

    Inventory(std::size_t capacity_);

    bool empty() const;

    std::size_t count() const;

    void add(identifier id, std::size_t amount_);

    std::size_t amount(identifier id) const;

    std::size_t capacity() const;

    std::size_t spaceAvailable() const;

    std::size_t spaceOccupied() const;

    void take(identifier id, std::size_t amount_);

private:
    using type_map = std::map<identifier, std::size_t>;

    std::size_t m_capacity;
    type_map m_map;
};

#endif // INVENTORY_HPP
