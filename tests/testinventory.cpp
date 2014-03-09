#include <gtest/gtest.h>

#include <inventory.hpp>

struct TestInventory : public ::testing::Test
{
    Inventory inventory {200};
};

TEST_F(TestInventory, EmptyOnCreation)
{
    ASSERT_TRUE(inventory.empty());
    ASSERT_EQ(0, inventory.count());
}

TEST_F(TestInventory, SpaceAvailableEqualsCapacityWhenEmpty)
{
    ASSERT_TRUE(inventory.spaceAvailable() == inventory.capacity());
}

struct TestInventoryWithTenOfZero : public TestInventory
{
    virtual void SetUp() override
    {
        inventory.add(0, amount);
    }

    const std::size_t amount = 10;
};

TEST_F(TestInventoryWithTenOfZero, NotEmptyAfterAdding10UnitsOfOneElement)
{
    ASSERT_FALSE(inventory.empty());
    ASSERT_EQ(1, inventory.count());
    ASSERT_EQ(amount, inventory.amount(0));
}

TEST_F(TestInventoryWithTenOfZero, SpaceOccupiedIsUpdatedAfterAddingElements)
{
    ASSERT_EQ(amount, inventory.spaceOccupied());
}

TEST_F(TestInventoryWithTenOfZero, SpaceAvailableIsUpdatedAfterAddingElements)
{
    ASSERT_EQ(inventory.capacity() - amount, inventory.spaceAvailable());
}

TEST_F(TestInventoryWithTenOfZero, AmountIsUpdatedAfterTakingSome)
{
    inventory.take(0, 5);
    ASSERT_EQ(5, inventory.amount(0));
}

TEST_F(TestInventoryWithTenOfZero, TakingThrowsIfNotEnough)
{
    ASSERT_ANY_THROW(inventory.take(0, amount+1));
}

TEST_F(TestInventoryWithTenOfZero, TakingThrowsIfNotAnyOfThatElement)
{
    ASSERT_ANY_THROW(inventory.take(1, 1));
}
