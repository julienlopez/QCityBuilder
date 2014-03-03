#ifndef RESSOURCESHANDLER_HPP
#define RESSOURCESHANDLER_HPP

#include <utils/containerwithidentifier.hpp>
#include <utils/singleton.hpp>

class RessourcesHandler : public utils::singleton<RessourcesHandler>, public utils::containerwithidentifier<uint8_t, std::string>
{

};

#endif // RESSOURCESHANDLER_HPP
