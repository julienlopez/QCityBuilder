#include "resourceshandler.hpp"

void ResourcesHandler::loadResources(const std::vector<std::string>& values)
{
    auto& inst = instance();
    assert(inst.empty());
    for(const auto& value : values)
        inst.add(value);
}

void ResourcesHandler::clear()
{
    instance().type_container::clear();
}

auto ResourcesHandler::findByName(const std::string& name) -> std::optional<type_identifier>
{
    for(const auto& value : instance())
    {
        if(value.second == name) return value.first;
    }
    return std::nullopt;
}
