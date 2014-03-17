#ifndef BUILDINGTYPE_HPP
#define BUILDINGTYPE_HPP

#include <utils/noncopiable.hpp>
#include <utils/size.hpp>

#include <ressourceshandler.hpp>

#include "namespace_world.hpp"

#include <string>

BEGIN_NAMESPACE_WORLD

struct BuildingType : private utils::noncopiable
{
    using requirements_map_t = std::map<RessourcesHandler::type_identifier, std::size_t>;

    BuildingType(std::string name_, utils::SizeU size_, requirements_map_t requirements_);

    const std::string name;
    const utils::SizeU size;
    const requirements_map_t requirements;
};

END_NAMESPACE_WORLD

#endif // BUILDINGTYPE_HPP
