#ifndef CLASSES_SERVER_SUBSERVERS_HPP
#define CLASSES_SERVER_SUBSERVERS_HPP

#include <SFML/Network.hpp>

#include "../../Enums/communication.hpp"
#include "../../Enums/serverEvents.hpp"
#include "ServerClient.hpp"

class FightSubserver
{
public:

	ServerClient clients[2];

	FightSubserver();

	~FightSubserver();

	bool isFull() const;

	void reset();

	ServerClient *connect(sf::TcpListener *listener, sf::SocketSelector *socketSelector = 0);

	ServerClient *disconnect(bool isClient1);

	void newEvent(SentInfosType infoType, const EventsUnion &eventInfos, bool isTeam1);

	bool isLastEventTreated();

	EntityInformations *IDToInformations(sf::Uint32 searchID, bool isTeam1);

protected:

	EventsStructure                 eventsStructure;
	bool                            stopSubServer;
	std::vector<EntityInformations> *teams[2];

private:

	/// \todo Finish that
	int threadFunction();

	sf::Thread serverThread;
};

bool findOpenSubserver(std::vector<FightSubserver *> &serverVector, FightSubserver **returnedSubserver);

#endif