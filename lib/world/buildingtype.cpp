#include "buildingtype.hpp"

BEGIN_NAMESPACE_WORLD

BuildingType::BuildingType(std::string name_, utils::SizeU size_, requirements_map_t requirements_,
                           recipes_container_t recipes_)
    : name(std::move(name_))
    , size(std::move(size_))
    , requirements(std::move(requirements_))
    , recipes(std::move(recipes_))
{
}

END_NAMESPACE_WORLD
