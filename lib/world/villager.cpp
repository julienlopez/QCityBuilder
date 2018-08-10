#include "villager.hpp"

namespace World
{

Villager::Villager(const City& city)
    : m_city(city)
{
}

auto Villager::state() const -> State
{
    return m_state;
}

} // World
