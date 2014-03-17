#ifndef BUILDINGTYPE_HPP
#define BUILDINGTYPE_HPP

#include <utils/noncopiable.hpp>
#include <utils/nonmovable.hpp>
#include <utils/rect.hpp>

#include <ressourceshandler.hpp>

#include "namespace_world.hpp"

#include <string>

BEGIN_NAMESPACE_WORLD

struct BuildingType : private utils::noncopiable, private utils::nonmovable
{
    using requirements_map_t = std::map<RessourcesHandler::type_identifier, std::size_t>;

    BuildingType(std::string name_, utils::RectU rectangle_, requirements_map_t requirements_);

    const std::string name;
    const utils::RectU rectangle;
    const requirements_map_t requirements;
};

END_NAMESPACE_WORLD

#endif // BUILDINGTYPE_HPP
