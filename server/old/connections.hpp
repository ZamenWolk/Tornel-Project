#ifndef CONNECTIONS_HPP_INCLUDED
#define CONNECTIONS_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <vector>

#include "FightSubserver.hpp"
#include "ServerClients.hpp"

/**
*   \todo Finish handling of received informations and receiving of pre-combat data
*/

void connectionHandler(std::vector<FightSubserver *> &subservers,
					   std::vector<ServerClient *> &clientsVector,
					   sf::SocketSelector *selector,
					   sf::TcpListener *listener);

#endif // CONNECTIONS_HPP_INCLUDED
