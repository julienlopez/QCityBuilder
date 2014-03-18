#ifndef BUILDINGTYPEHANDLER_HPP
#define BUILDINGTYPEHANDLER_HPP

#include <utils/containerwithidentifier.hpp>
#include <utils/singleton.hpp>

#include "buildingtype.hpp"

BEGIN_NAMESPACE_WORLD

class BuildingTypeHandler : public utils::singleton<BuildingTypeHandler>, public utils::containerwithidentifier<uint8_t, BuildingType>
{
public:
    uint8_t getByName(const std::string& name) const;
};

END_NAMESPACE_WORLD

#endif // BUILDINGTYPEHANDLER_HPP
