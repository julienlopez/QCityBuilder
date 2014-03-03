#include <gtest/gtest.h>

#include <utils/containerwithidentifier.hpp>

struct TestContainerWithIdentifier : public ::testing::Test
{
    using type_container = utils::containerwithidentifier<uint8_t, std::string>;

    type_container container;
};

TEST_F(TestContainerWithIdentifier, EmptyOnCreation)
{
    ASSERT_TRUE(container.empty());
}

TEST_F(TestContainerWithIdentifier, NotEmptyAfterAddingAnElement)
{
    container.add("one");
    ASSERT_FALSE(container.empty());
}

TEST_F(TestContainerWithIdentifier, IdentifiersDifferent)
{
    auto id1 = container.add("one");
    auto id2 = container.add("two");
    ASSERT_NE(id1, id2);
}

TEST_F(TestContainerWithIdentifier, IdentifiersGetReturnTheRightElement)
{
    std::string str1 = "one";
    std::string str2 = "two";
    auto id1 = container.add(str1);
    auto id2 = container.add(str2);
    ASSERT_EQ(str1, container.get(id1));
    ASSERT_EQ(str2, container.get(id2));
}
