#ifndef CURRENTCITYHOLDER_HPP
#define CURRENTCITYHOLDER_HPP

#include <utils/singleton.hpp>

#include "city.hpp"

#include <memory>

BEGIN_NAMESPACE_WORLD

class CurrentCityHolder : public utils::singleton<CurrentCityHolder>
{
    friend class utils::singleton<CurrentCityHolder>;

public:
    static City& get();
    static bool isInitialized();

    static void initialize(std::string name, utils::SizeU size);

protected:
    CurrentCityHolder() = default;

private:
    std::unique_ptr<City> m_currentCity;
};

END_NAMESPACE_WORLD

#endif // CURRENTCITYHOLDER_HPP
