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

struct TestContainerWithIdentifierAndTwoElements : public TestContainerWithIdentifier
{
    virtual void SetUp() override
    {
        const type_container::type_value e1 = "one";
        addedElements.push_back(std::make_pair(container.add(e1), e1));

        const type_container::type_value e2 = "two";
        addedElements.push_back(std::make_pair(container.add(e2), e2));

        assert(addedElements.size() == 2);
    }

    std::vector<std::pair<type_container::type_identifier, type_container::type_value>> addedElements;
};

TEST_F(TestContainerWithIdentifierAndTwoElements, IdentifiersDifferent)
{
    ASSERT_NE(addedElements.front().first, addedElements.back().first);
}

TEST_F(TestContainerWithIdentifierAndTwoElements, getReturnTheRightElement)
{
    ASSERT_EQ(addedElements.front().second, container.get(addedElements.front().first));
    ASSERT_EQ(addedElements.back().second, container.get(addedElements.back().first));
}

TEST_F(TestContainerWithIdentifierAndTwoElements, getWithBadIdThrows)
{
    ASSERT_THROW(container.get(addedElements.back().first + 1), std::invalid_argument);
}

TEST_F(TestContainerWithIdentifierAndTwoElements, idOfReturnTheRightKey)
{
    ASSERT_EQ(addedElements.front().first, container.idOf(addedElements.front().second));
    ASSERT_EQ(addedElements.back().first, container.idOf(addedElements.back().second));
}

TEST_F(TestContainerWithIdentifierAndTwoElements, idOfWithBadValueThrows)
{
    ASSERT_THROW(container.idOf("bad value"), std::invalid_argument);
}

TEST_F(TestContainerWithIdentifierAndTwoElements, iteratorsOk)
{
    ASSERT_EQ((std::size_t)2, std::distance(container.begin(), container.end()));
}
