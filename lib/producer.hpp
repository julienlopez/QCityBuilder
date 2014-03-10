#ifndef PRODUCER_HPP
#define PRODUCER_HPP

#include "production.hpp"
#include "inventory.hpp"

class Producer
{
public:
    Producer(std::size_t capacity, Production production);

    const Inventory& inventory() const;

    void update();

private:
    Production m_production;
    Inventory m_inventory;
};

#endif // PRODUCER_HPP
