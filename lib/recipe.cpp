#include "recipe.hpp"

Recipe::Recipe(std::size_t timeout_, container_pairs_identifier_amount inputs_,
               container_pairs_identifier_amount outputs_)
    : m_timeout(timeout_)
    , m_inputs(std::move(inputs_))
    , m_outputs(std::move(outputs_))
{
}

auto Recipe::inputs() const -> const container_pairs_identifier_amount&
{
    return m_inputs;
}

auto Recipe::outputs() const -> const container_pairs_identifier_amount&
{
    return m_outputs;
}

std::size_t Recipe::timeout() const
{
    return m_timeout;
}
