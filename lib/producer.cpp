#include "producer.hpp"

#include <utility>

Producer::Producer(std::size_t capacity, Production production): m_production(std::move(production)), m_inventory(capacity)
{}

const Inventory& Producer::inventory() const
{
    return m_inventory;
}

void Producer::update()
{

}
