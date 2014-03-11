#include "production.hpp"

Production::Production(std::size_t timeout_, container_pairs_identifier_amount inputs_, container_pairs_identifier_amount outputs_):
    m_timeout(timeout_), m_inputs(std::move(inputs_)), m_outputs(std::move(outputs_))
{}

auto Production::inputs() const -> const container_pairs_identifier_amount&
{
    return m_inputs;
}

auto Production::outputs() const -> const container_pairs_identifier_amount&
{
    return m_outputs;
}

std::size_t Production::timeout() const
{
    return m_timeout;
}
