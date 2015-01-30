#include "ressourceshandler.hpp"

void RessourcesHandler::loadRessources(const std::vector<std::string>& values)
{
    auto& inst = instance();
    assert(inst.empty());
    for(const auto& value : values)
        inst.add(value);
}

void RessourcesHandler::clear()
{
    instance().type_container::clear();
}
