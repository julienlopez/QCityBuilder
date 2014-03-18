#include "buildingtypehandler.hpp"

#include <algorithm>

BEGIN_NAMESPACE_WORLD

uint8_t BuildingTypeHandler::getByName(const std::string& name) const
{
    auto it = std::find_if(begin(), end(), [&name](const type_map::value_type& pair){ return pair.second.name == name; });
    if(it == end()) throw std::invalid_argument("Unable to find building type with name " + name);
    return it->first;
}

END_NAMESPACE_WORLD
