#include "production.hpp"

Production::Production(container_pairs_identifier_amount inputs, container_pairs_identifier_amount outputs):
    m_inputs(std::move(inputs)), m_outputs(std::move(outputs))
{}
