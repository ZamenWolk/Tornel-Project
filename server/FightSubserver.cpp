#include <vector>

#include "FightSubserver.hpp"

using namespace std;
using namespace sf;

FightSubserver::FightSubserver():
		clients(),
		serverThread(&FightSubserver::threadFunction, this),
		stopSubServer(0),
		eventsStructure()
{
	teams[0] = 0;
	teams[1] = 0;
}

FightSubserver::~FightSubserver()
{
	stopSubServer = true;
	serverThread.wait();
	delete teams[0];
	delete teams[1];
}

bool FightSubserver::isFull() const
{
	return !(clients[0].isSocketFree() || clients[1].isSocketFree());
}


void FightSubserver::reset()
{
	disconnect(true);
	disconnect(false);
}

ServerClient* FightSubserver::connect(TcpListener *listener, SocketSelector *socketSelector)
{
	ServerClient                    *concernedClient(nullptr);
	std::vector<EntityInformations> *concernedTeamVector(nullptr);
	bool                            isClient1(false);

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

	while (eventsStructure.isEventTreated || eventsStructure.team1 != isClient1)
	{
		sleep(milliseconds(1000));
	}

	if (eventsStructure.typeOfEvent != VERSION_NUMBER)
	{
		errorReport("The information received is not a VERSION_NUMBER");
		concernedClient->disconnect();
	}

	if (eventsStructure.infos.versEv.status != AutoVersion::STATUS || eventsStructure.infos.versEv.major != AutoVersion::MAJOR)
	{
		disconnect(true);
		eventsStructure.isEventTreated = true;
		return 0;
	}

	concernedTeamVector = new std::vector<EntityInformations>;

	while (eventsStructure.isEventTreated || eventsStructure.team1 != isClient1)
	{
		sleep(milliseconds(1000));
	}

	if (eventsStructure.typeOfEvent != TEAM_DATA)
	{
		errorReport("The infformation received is not a TEAM_DATA");
		concernedClient->disconnect();
	}

	*concernedTeamVector = eventsStructure.infos.teamEv;

	if (isFull())
	{
		serverThread.launch();
	}

	eventsStructure.isEventTreated = true;
	return concernedClient;
}

ServerClient* FightSubserver::disconnect(bool isClient1)
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

void FightSubserver::newEvent(SentInfosType infoType, const EventsUnion &eventInfos, bool isTeam1)
{
	eventsStructure.typeOfEvent    = infoType;
	eventsStructure.infos    	   = eventInfos;
	eventsStructure.team1          = isTeam1;
	eventsStructure.isEventTreated = false;
}

bool FightSubserver::isLastEventTreated()
{
	return eventsStructure.isEventTreated;
}

void FightSubserver::threadFunction()
{
	sf::Packet teamsPacket;

	teamsPacket << TEAM_DATA << *teams[1];

	while (isFull() && !stopSubServer)
	{
		if (!eventsStructure.isEventTreated)
		{

		}
	}
}


bool findOpenSubserver(std::vector<FightSubserver *> &serverVector, FightSubserver **returnedSubserver)
{
	for (unsigned int i = 0; i < serverVector.size(); i++)
	{
		if (!(serverVector.operator[](i)->isFull()))
		{
			*returnedSubserver = serverVector[i];
			return true;
		}
	}

	return false;
}
