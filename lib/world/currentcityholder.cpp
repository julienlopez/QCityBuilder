#include "currentcityholder.hpp"

#include <utils/make_unique.hpp>

#include <cassert>

BEGIN_NAMESPACE_WORLD

City& CurrentCityHolder::get()
{
    assert(instance().m_currentCity);
    return *instance().m_currentCity;
}

bool CurrentCityHolder::isInitialized()
{
    return (bool)instance().m_currentCity;
}

void CurrentCityHolder::initialize(std::string name, utils::SizeU size)
{
    instance().m_currentCity = utils::make_unique<City>(std::move(name), std::move(size));
}

END_NAMESPACE_WORLD
