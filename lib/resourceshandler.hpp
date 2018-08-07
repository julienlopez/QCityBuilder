#ifndef RESOURCESHANDLER_HPP
#define RESOURCESHANDLER_HPP

#include "utils/containerwithidentifier.hpp"
#include "utils/singleton.hpp"

#include <vector>

class ResourcesHandler : private utils::singleton<ResourcesHandler>,
                         private utils::containerwithidentifier<uint8_t, std::string>
{
public:
    using type_container = utils::containerwithidentifier<uint8_t, std::string>;
    using type_identifier = type_container::type_identifier;

    using utils::singleton<ResourcesHandler>::const_instance;

    using type_container::cbegin;
    using type_container::cend;
    using type_container::get;
    using type_container::idOf;

    static void loadResources(const std::vector<std::string>& values);

    static void clear();
};

#endif // RESOURCESHANDLER_HPP
