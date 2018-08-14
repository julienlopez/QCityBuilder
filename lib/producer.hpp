#ifndef PRODUCER_HPP
#define PRODUCER_HPP

#include "inventory.hpp"
#include "recipe.hpp"

#include <optional>

class Producer
{
public:
    Producer(std::size_t capacity, std::optional<Recipe> recipe = std::nullopt);

    Inventory& inventory();

    const Inventory& inventory() const;

    void update();

    void update(std::size_t nbOfTicks);

    bool isBusy() const;

private:
    std::optional<Recipe> m_recipe;
    Inventory m_inventory;
    std::size_t m_currentTimeout;
};

#endif // PRODUCER_HPP
