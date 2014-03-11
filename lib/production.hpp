#ifndef PRODUCTION_HPP
#define PRODUCTION_HPP

#include "ressourceshandler.hpp"

#include <vector>

class Production
{
public:
    using identifier = RessourcesHandler::type_identifier;
    using pair_identifier_amount = std::pair<identifier, std::size_t>;
    using container_pairs_identifier_amount = std::vector<pair_identifier_amount>;

    Production(std::size_t timeout_, container_pairs_identifier_amount inputs_, container_pairs_identifier_amount output_s);

    const container_pairs_identifier_amount& inputs() const;
    const container_pairs_identifier_amount& outputs() const;

    std::size_t timeout() const;

private:
    std::size_t m_timeout;
    container_pairs_identifier_amount m_inputs;
    container_pairs_identifier_amount m_outputs;
};

#endif // PRODUCTION_HPP
