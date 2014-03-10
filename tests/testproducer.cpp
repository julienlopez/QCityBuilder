#include <gtest/gtest.h>

#include <producer.hpp>

struct TestProducer : public testing::Test
{
    std::size_t input_type1 = 1;
    std::size_t input_amount1 = 2;
    std::size_t input_type2 = 2;
    std::size_t input_amount2 = 5;
    std::size_t output_type1 = 3;
    std::size_t output_amount1 = 1;

    Producer producer = {200, Production({std::make_pair(input_type1, input_amount1), std::make_pair(input_type2, input_amount2)},
                         {std::make_pair(output_type1, output_amount1)})};
};

TEST_F(TestProducer, InventoryEmptyOnCreation)
{
    ASSERT_TRUE(producer.inventory().empty());
}

TEST_F(TestProducer, DoesntProduceAnythingWithAnEmptyInventory)
{
    producer.update();
    ASSERT_TRUE(producer.inventory().empty());
}
