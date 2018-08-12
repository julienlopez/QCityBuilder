#ifndef BUILDINGTYPE_HPP
#define BUILDINGTYPE_HPP

#include <utils/noncopiable.hpp>
#include <utils/size.hpp>

#include <recipe.hpp>
#include <resourceshandler.hpp>

#include "namespace_world.hpp"

#include <string>

BEGIN_NAMESPACE_WORLD

struct BuildingType : private utils::noncopiable
{
    using requirements_map_t = std::map<ResourcesHandler::type_identifier, std::size_t>;
    using recipes_container_t = std::vector<Recipe>;

    BuildingType(std::string name_, utils::SizeU size_, requirements_map_t requirements_,
                 recipes_container_t recipes_ = {});

    const std::string name;
    const utils::SizeU size;
    const requirements_map_t requirements;
    const recipes_container_t recipes;
};

END_NAMESPACE_WORLD

#endif // BUILDINGTYPE_HPP
