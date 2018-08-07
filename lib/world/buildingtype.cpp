#include "buildingtype.hpp"

BEGIN_NAMESPACE_WORLD

BuildingType::BuildingType(std::string name_, utils::SizeU size_, requirements_map_t requirements_)
    : name(std::move(name_))
    , size(std::move(size_))
    , requirements(std::move(requirements_))
{
}

END_NAMESPACE_WORLD
