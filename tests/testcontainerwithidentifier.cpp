#include <catch.hpp>

#include <utils/containerwithidentifier.hpp>

using type_container = utils::containerwithidentifier<uint8_t, std::string>;

TEST_CASE("Test Container With Identifier")
{
    type_container container;

    SECTION("Empty On Creation")
    {
        CHECK(container.empty());
    }

    SECTION("Not Empty After Adding An Element")
    {
        container.add("one");
        CHECK(! container.empty());
    }
}

TEST_CASE("Test Container With Identifier And Two Elements")
{
    type_container container;
    std::vector<std::pair<type_container::type_identifier, type_container::type_value>> addedElements;

    const type_container::type_value e1 = "one";
    addedElements.push_back(std::make_pair(container.add(e1), e1));

    const type_container::type_value e2 = "two";
    addedElements.push_back(std::make_pair(container.add(e2), e2));

    assert(addedElements.size() == 2);

    SECTION("IdentifiersDifferent")
    {
        CHECK(addedElements.front().first != addedElements.back().first);
    }

    SECTION("getReturnTheRightElement")
    {
        CHECK(addedElements.front().second == container.get(addedElements.front().first));
        CHECK(addedElements.back().second == container.get(addedElements.back().first));
    }

    SECTION("get With Bad Id Throws")
    {
        CHECK_THROWS_AS(container.get(addedElements.back().first + 1), std::invalid_argument);
    }

    SECTION("id Of Return The Right Key")
    {
        CHECK(addedElements.front().first == container.idOf(addedElements.front().second));
        CHECK(addedElements.back().first == container.idOf(addedElements.back().second));
    }

    SECTION("id Of With Bad Value Throws")
    {
        CHECK_THROWS_AS(container.idOf("bad value"), std::invalid_argument);
    }

    SECTION("iterators Ok")
    {
        CHECK(std::distance(container.begin(), container.end()) == 2);
    }
}
