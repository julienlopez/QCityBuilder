#include "producer.hpp"

#include <utility>

Producer::Producer(std::size_t capacity, Production production)
    : m_production(std::move(production))
    , m_inventory(capacity)
{
    m_currentTimeout = 0;
}

Inventory& Producer::inventory()
{
    return m_inventory;
}

const Inventory& Producer::inventory() const
{
    return m_inventory;
}

void Producer::update()
{
    if(!isBusy())
    {
        const auto& needed = m_production.inputs();
        for(const auto& n : needed)
        {
            if(!m_inventory.hasEnough(n.first, n.second)) return;
        }
        for(const auto& n : needed)
        {
            m_inventory.take(n.first, n.second);
        }
    }
    m_currentTimeout++;
    if(m_currentTimeout >= m_production.timeout())
    {
        m_currentTimeout = 0;
        const auto& produced = m_production.outputs();
        for(const auto& p : produced)
        {
            m_inventory.add(p.first, p.second);
        }
    }
}

void Producer::update(std::size_t nbOfTicks)
{
    for(std::size_t i = 0; i < nbOfTicks; i++)
        update();
}

bool Producer::isBusy() const
{
    return m_currentTimeout != 0;
}
