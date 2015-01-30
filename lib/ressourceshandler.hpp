#ifndef RESSOURCESHANDLER_HPP
#define RESSOURCESHANDLER_HPP

#include "utils/containerwithidentifier.hpp"
#include "utils/singleton.hpp"

#include <vector>

class RessourcesHandler : private utils::singleton<RessourcesHandler>, private utils::containerwithidentifier<uint8_t, std::string>
{
public:
    using type_container = utils::containerwithidentifier<uint8_t, std::string>;
    using type_identifier = type_container::type_identifier;

    using utils::singleton<RessourcesHandler>::const_instance;

    using type_container::idOf;
    using type_container::get;
    using type_container::cbegin;
    using type_container::cend;

    static void loadRessources(const std::vector<std::string>& values);

    static void clear();
};

#endif // RESSOURCESHANDLER_HPP
