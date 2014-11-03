#ifndef FIGHTSUBSERVER_HPP_INCLUDED
#define FIGHTSUBSERVER_HPP_INCLUDED

/**
*   \file FightSubserver.hpp
*   \brief contains the FightSubserver class, as well as the subserver-related functions
*/

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>

#include "ServerClients.hpp"
#include "../src/operators.hpp"
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
*   \brief Subserver handling a fight between 2 clients
*/

class FightSubserver
{
public:

	ServerClient clients[2]; ///< Sockets of the clients

	FightSubserver() :
			clients(),
			serverThread(&FightSubserver::threadFunction, this),
			stopSubServer(0),
			eventsStructure()
	{
		teams[0] = 0;
		teams[1] = 0;
	}

	~FightSubserver()
	{
		stopSubServer = true;
		serverThread.wait();
		delete teams[0];
		delete teams[1];
	}

	/**
	*   \return If the server is full or not
	*/

	bool isFull() const
	{
		return !(clients[0].isSocketFree() || clients[1].isSocketFree());
	}

	/**
	*   \brief Resets the server to it's original state
	*/

	void reset()
	{
		disconnect(true);
		disconnect(false);
	}

	/**
	*   \brief Connects an incoming client to one of the sockets of the subserver, if possible
	*   \param[in] listener Listener to receive the incoming connection request from
	*   \param[in] socketSelector to link the Socket to
	*   \return Pointer to the newly connected ServerClient
	*   \todo Handle team data reception
	*/

	ServerClient *connect(sf::TcpListener *listener, sf::SocketSelector *socketSelector = 0)
	{
		ServerClient                    *concernedClient(nullptr);
		std::vector<EntityInformations> *concernedTeamVector(nullptr);
		bool                            isClient1(false);
		SentInfosType 					type;
		sf::Packet 						versionPacket;

		if (clients[0].isSocketFree())
		{
			concernedClient     = &clients[0];
			concernedTeamVector = teams[0];
			isClient1           = true;
		}
		else if (clients[1].isSocketFree())
		{
			concernedClient     = &clients[1];
			concernedTeamVector = teams[1];
			isClient1           = false;
		}
		else
		{
			ServerClient buffer;
			buffer.connect(*listener);
			buffer.disconnect();
			return 0;
		}

		concernedClient->connect(*listener, socketSelector);
		concernedClient->receive(versionPacket);

		infoTypeInPacket(versionPacket, type);
		deconstructPacket(versionPacket, eventsStructure.versEv_number, type);
		eventsStructure.isEventTreated = true;

		if (eventsStructure.versEv_number.status == AutoVersion::STATUS && eventsStructure.versEv_number.major == AutoVersion::MAJOR)
		{
			concernedTeamVector = new std::vector<EntityInformations>;
			if (isFull())
			{
				serverThread.launch();
			}
			return concernedClient;
		}
		else
		{
			disconnect(true);
			eventsStructure.isEventTreated = true;
			return 0;
		}
	}

	/**
	*   \brief Disconnects one of the clients of the subserver
	*   \param[in] isClient1 Is client 1 or 2 concerned
	*   \return ServerClient who got disconnected
	*/

	ServerClient *disconnect(bool isClient1)
	{
		if (isClient1)
		{
			clients[0].disconnect();
			delete teams[0];
			return &clients[0];
		}
		else
		{
			clients[1].disconnect();
			delete teams[1];
			return &clients[1];
		}
	}

	/**
	*   \brief Transfers a new event from the client-server thread to the subserver
	*   \param[in] eventInfos Description of the interaction requested from server
	*/

	void newEvent(const InteractionInfos &eventInfos)
	{
		eventsStructure.typeOfEvent    = FIGHT_INTERACTION;
		eventsStructure.intEv_infos    = eventInfos;
		eventsStructure.isEventTreated = false;
	}

	/**
	*   \brief Transfers a new event from the client-server thread to the subserver
	*   \param[in] teamInfo Team sent to server by client
	*   \param[in] isTeam1 Is the described team team1 or team2
	*/

	void newEvent(std::vector<EntityInformations> &teamInfo, bool isTeam1)
	{
		eventsStructure.typeOfEvent    = TEAM_DATA;
		eventsStructure.teamEv_infos   = teamInfo;
		eventsStructure.event_team1    = isTeam1;
		eventsStructure.isEventTreated = false;
	}

	/**
	*   \brief Transfers a new event from the client-server thread to the subserver
	*   \param versionNumber Version number of the client
	*   \param isTeam1 Is the version number team1's or team2's
	*/

	void newEvent(const VersionNumber &versionNumber, bool isTeam1)
	{
		eventsStructure.typeOfEvent    = VERSION_NUMBER;
		eventsStructure.versEv_number  = versionNumber;
		eventsStructure.event_team1    = isTeam1;
		eventsStructure.isEventTreated = false;
	}

	/**
	*   \return Whether the last event has already been treated
	*/

	bool isLastEventTreated()
	{
		return eventsStructure.isEventTreated;
	}

protected:

	EventsStructure                 eventsStructure; ///< Structure of possible interactions between server and client
	bool                            stopSubServer; ///< Turns true if the subserver needs to be stopped
	std::vector<EntityInformations> *teams[2]; ///< Team members of both subservers

private:

	///\todo Finish that
	void threadFunction()
	{
		while (isFull() && !stopSubServer)
		{
			if (!eventsStructure.isEventTreated)
			{

			}
		}
	}

	sf::Thread serverThread; ///< Thread running the subserver
};

/**
*   \brief Finds an open subserver in all the available subservers
*   \param[in] serverVector vector of all the subservers to test
*   \param[out] returnedSubserver Variable to return the open subserver to
*   \return If the function found an open subserver or not
*/

bool findOpenSubserver(std::vector<FightSubserver *> &serverVector, FightSubserver **returnedSubserver);

#endif // FIGHTSUBSERVER_HPP_INCLUDED

/// @}