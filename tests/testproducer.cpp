#include <catch.hpp>

#include <producer.hpp>

TEST_CASE("Test Producer")
{
    const std::size_t input_type1 = 1;
    const std::size_t input_amount1 = 2;
    const std::size_t input_type2 = 2;
    const std::size_t input_amount2 = 5;
    const std::size_t output_type1 = 3;
    const std::size_t output_amount1 = 1;
    const std::size_t timeout = 20;

    Producer producer
        = {200,
           Production(timeout, {std::make_pair(input_type1, input_amount1), std::make_pair(input_type2, input_amount2)},
                      {std::make_pair(output_type1, output_amount1)})};

    SECTION("Inventory Empty On Creation")
    {
        CHECK(producer.inventory().empty());
    }

    SECTION("Isnt Busy On Creation")
    {
        CHECK(!producer.isBusy());
    }

    SECTION("Doesnt Produce Anything With An Empty Inventory")
    {
        producer.update();
        CHECK(producer.inventory().empty());
    }

    SECTION("Continue Production For Ten Cycles If Enough Materials")
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
        CHECK(nbCycle * timeout + 1 == tick);
        CHECK(1 == producer.inventory().count());
        CHECK(nbCycle * output_amount1 == producer.inventory().amount(output_type1));
    }
}

TEST_CASE("Test Producer Enough For One Round")
{
    const std::size_t input_type1 = 1;
    const std::size_t input_amount1 = 2;
    const std::size_t input_type2 = 2;
    const std::size_t input_amount2 = 5;
    const std::size_t output_type1 = 3;
    const std::size_t output_amount1 = 1;
    const std::size_t timeout = 20;

    Producer producer
        = {200,
           Production(timeout, {std::make_pair(input_type1, input_amount1), std::make_pair(input_type2, input_amount2)},
                      {std::make_pair(output_type1, output_amount1)})};

    producer.inventory().add(input_type1, input_amount1);
    producer.inventory().add(input_type2, input_amount2);

    SECTION("Inventory Emptied After One Update")
    {
        producer.update();
        CHECK(producer.inventory().empty());
    }

    SECTION("Is Busy After One Update")
    {
        producer.update();
        CHECK(producer.isBusy());
    }

    SECTION("One Production Round Done After Enough Time")
    {
        producer.update(timeout);
        CHECK(1 == producer.inventory().count());
        CHECK(output_amount1 == producer.inventory().amount(output_type1));
        CHECK(!producer.isBusy());
    }
}
