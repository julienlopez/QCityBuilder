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
