#ifndef PRODUCER_HPP
#define PRODUCER_HPP

#include "inventory.hpp"
#include "recipe.hpp"

class Producer
{
public:
    Producer(std::size_t capacity, Recipe production);

    Inventory& inventory();

    const Inventory& inventory() const;

    void update();

    void update(std::size_t nbOfTicks);

    bool isBusy() const;

private:
    Recipe m_production;
    Inventory m_inventory;
    std::size_t m_currentTimeout;
};

#endif // PRODUCER_HPP
