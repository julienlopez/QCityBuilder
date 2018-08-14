#include "producer.hpp"

#include <utility>

Producer::Producer(std::size_t capacity, std::optional<Recipe> recipe)
    : m_recipe(std::move(recipe))
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
    if(!m_recipe) return;
    if(!isBusy())
    {
        const auto& needed = m_recipe->inputs();
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
    if(m_currentTimeout >= m_recipe->timeout())
    {
        m_currentTimeout = 0;
        const auto& produced = m_recipe->outputs();
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
