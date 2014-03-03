#include <gtest/gtest.h>

#include <inventory.hpp>

struct TestInvetory : public ::testing::Test
{
    Inventory inventory;
};

TEST_F(TestInvetory, EmptyOnCreation)
{
    ASSERT_TRUE(inventory.empty());
    ASSERT_EQ(0, inventory.count());
}

TEST_F(TestInvetory, NotEmptyAfterAdding10Elements)
{
    inventory.add(0, 10);

    ASSERT_FALSE(inventory.empty());
    ASSERT_EQ(1, inventory.count());

    ASSERT_EQ(10, inventory.amount(0));
}
