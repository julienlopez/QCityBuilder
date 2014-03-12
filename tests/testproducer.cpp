#include <gtest/gtest.h>

#include <producer.hpp>

struct TestProducer : public testing::Test
{
    const std::size_t input_type1 = 1;
    const std::size_t input_amount1 = 2;
    const std::size_t input_type2 = 2;
    const std::size_t input_amount2 = 5;
    const std::size_t output_type1 = 3;
    const std::size_t output_amount1 = 1;
    const std::size_t timeout = 20;

    Producer producer = {200, Production(timeout, {std::make_pair(input_type1, input_amount1), std::make_pair(input_type2, input_amount2)},
                         {std::make_pair(output_type1, output_amount1)})};
};

TEST_F(TestProducer, InventoryEmptyOnCreation)
{
    ASSERT_TRUE(producer.inventory().empty());
}

TEST_F(TestProducer, IsntBusyOnCreation)
{
    ASSERT_FALSE(producer.isBusy());
}

TEST_F(TestProducer, DoesntProduceAnythingWithAnEmptyInventory)
{
    producer.update();
    ASSERT_TRUE(producer.inventory().empty());
}

struct TestProducerEnoughForOneRound : public TestProducer
{
    virtual void SetUp() override
    {
        producer.inventory().add(input_type1, input_amount1);
        producer.inventory().add(input_type2, input_amount2);
    }
};

TEST_F(TestProducerEnoughForOneRound, InventoryEmptiedAfterOneUpdate)
{
    producer.update();
    ASSERT_TRUE(producer.inventory().empty());
}

TEST_F(TestProducerEnoughForOneRound, IsBusyAfterOneUpdate)
{
    producer.update();
    ASSERT_TRUE(producer.isBusy());
}

TEST_F(TestProducerEnoughForOneRound, OneProductionRoundDoneAfterEnoughTime)
{
    producer.update(timeout);
    ASSERT_EQ(1, producer.inventory().count());
    ASSERT_EQ(output_amount1, producer.inventory().amount(output_type1));
    ASSERT_FALSE(producer.isBusy());
}

TEST_F(TestProducer, ContinueProductionForTenCyclesIfEnoughMaterials)
{
    const std::size_t nbCycle = 10;
    producer.inventory().add(input_type1, nbCycle * input_amount1);
    producer.inventory().add(input_type2, nbCycle * input_amount2);
    std::size_t tick = 1;
    producer.update();
    while(producer.isBusy())
    {
        while(producer.isBusy())
        {
            producer.update();
            tick++;
        }
        producer.update();
        tick++;
    }
    ASSERT_EQ(nbCycle * timeout + 1, tick);
    ASSERT_EQ(1, producer.inventory().count());
    ASSERT_EQ(nbCycle * output_amount1, producer.inventory().amount(output_type1));
}
