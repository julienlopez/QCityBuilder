#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "ressourceshandler.hpp"

class Inventory
{
public:
    using identifier = RessourcesHandler::type_identifier;

    Inventory();

    bool empty() const;

    std::size_t count() const;

    void add(identifier id, std::size_t amount_);

    std::size_t amount(identifier id) const;

private:
    using type_map = std::map<identifier, std::size_t>;
    type_map m_map;
};

#endif // INVENTORY_HPP
