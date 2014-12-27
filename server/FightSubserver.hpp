#ifndef FIGHTSUBSERVER_HPP_INCLUDED
#define FIGHTSUBSERVER_HPP_INCLUDED

/**
* \file FightSubserver.hpp
* \brief contains the FightSubserver class, as well as the subserver-related functions
*/

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>

#include "ServerClients.hpp"
#include "../src/AIControlledEntity.hpp"
#include "structures.hpp"
#include "../version.hpp"
#include "../communication.hpp"

/**
* \addtogroup server Server side
* \brief Compounds used in the server application
* @{
*/

/**
* \brief Subserver handling a fight between 2 clients
*/

class FightSubserver
{
public:

	ServerClient clients[2]; ///< Sockets of the clients

	FightSubserver();

	~FightSubserver();

	/**
	* \return If the server is full or not
	*/

	bool isFull() const;

	/**
	* \brief Resets the server to it's original state
	*/

	void reset();

	/**
	* \brief Connects an incoming client to one of the sockets of the subserver, if possible
	* \param[in] listener Listener to receive the incoming connection request from
	* \param[in] socketSelector to link the Socket to
	* \return Pointer to the newly connected ServerClient
	*/

	ServerClient *connect(sf::TcpListener *listener, sf::SocketSelector *socketSelector = 0);

	/**
	* \brief Disconnects one of the clients of the subserver
	* \param[in] isClient1 Is client 1 or 2 concerned
	* \return ServerClient who got disconnected
	*/

	ServerClient *disconnect(bool isClient1);

	/**
	* \brief Transfers a new event from the client-server thread to the subserver
	* \param[in] eventInfos Description of the interaction requested from server
	*/

	void newEvent(SentInfosType infoType, const EventsUnion &eventInfos, bool isTeam1);

	/**
	* \return Whether the last event has already been treated
	*/

	bool isLastEventTreated();

	EntityInformations *IDToInformations(sf::Uint32 searchID, bool isTeam1);

protected:

	EventsStructure                 eventsStructure; ///< Structure of possible interactions between server and client
	bool                            stopSubServer; ///< Turns true if the subserver needs to be stopped
	std::vector<EntityInformations> *teams[2]; ///< Team members of both subservers

private:

	/// \todo Finish that
	int threadFunction();

	sf::Thread serverThread; ///< Thread running the subserver
};

/**
* \brief Finds an open subserver in all the available subservers
* \param[in] serverVector vector of all the subservers to test
* \param[out] returnedSubserver Variable to return the open subserver to
* \return If the function found an open subserver or not
*/

bool findOpenSubserver(std::vector<FightSubserver *> &serverVector, FightSubserver **returnedSubserver);

#endif // FIGHTSUBSERVER_HPP_INCLUDED

/// @}