#include <catch.hpp>

#include "world/city.hpp"
#include "world/villager.hpp"

TEST_CASE("Basic Villager tests")
{

    SECTION("A brand new villager is idle")
    {
        World::City city("A", {50, 50});
        World::Villager v(city);
        CHECK(v.state() == World::Villager::State::Idle);
    }
}
