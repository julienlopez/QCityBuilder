#include <catch.hpp>

#include <inventory.hpp>

TEST_CASE("Test Inventory")
{
    Inventory inventory{200};

    SECTION("Empty On Creation")
    {
        CHECK(inventory.empty());
        CHECK(inventory.count() == 0);
    }

    SECTION("Space Available Equals Capacity When Empty")
    {
        CHECK(inventory.spaceAvailable() == inventory.capacity());
    }
}

TEST_CASE("Test Inventory With Ten Of Zero")
{
    const std::size_t amount = 10;
    Inventory inventory{200};
    inventory.add(0, amount);

    SECTION("Not Empty After Adding10 Units Of One Element")
    {
        CHECK(!inventory.empty());
        CHECK(1 == inventory.count());
        CHECK(amount == inventory.amount(0));
    }

    SECTION("Space Occupied Is Updated After Adding Elements")
    {
        CHECK(amount == inventory.spaceOccupied());
    }

    SECTION("Space Available Is Updated After Adding Elements")
    {
        CHECK(inventory.capacity() - amount == inventory.spaceAvailable());
    }

    SECTION("Amount Is Updated After Taking Some")
    {
        inventory.take(0, 5);
        CHECK(inventory.amount(0) == 5);
    }

    SECTION("Taking Throws If Not Enough")
    {
        CHECK_THROWS(inventory.take(0, amount + 1));
    }

    SECTION("Taking Throws If Not Any Of That Element")
    {
        CHECK_THROWS(inventory.take(1, 1));
    }
}
