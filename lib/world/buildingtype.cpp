#include "buildingtype.hpp"

BEGIN_NAMESPACE_WORLD

BuildingType::BuildingType(std::string name_, utils::RectU rectangle_, requirements_map_t requirements_):
    name(std::move(name_)), rectangle(std::move(rectangle_)), requirements(std::move(requirements_))
{}

END_NAMESPACE_WORLD
