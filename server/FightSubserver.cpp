#include <vector>

#include "FightSubserver.hpp"

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

ServerClient* FightSubserver::connect(sf::TcpListener *listener, sf::SocketSelector *socketSelector)
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

void FightSubserver::newEvent(const InteractionInfos &eventInfos)
{
	eventsStructure.typeOfEvent    = FIGHT_INTERACTION;
	eventsStructure.intEv_infos    = eventInfos;
	eventsStructure.isEventTreated = false;
}

void FightSubserver::newEvent(std::vector<EntityInformations> &teamInfo, bool isTeam1)
{
	eventsStructure.typeOfEvent    = TEAM_DATA;
	eventsStructure.teamEv_infos   = teamInfo;
	eventsStructure.event_team1    = isTeam1;
	eventsStructure.isEventTreated = false;
}

void FightSubserver::newEvent(const VersionNumber &versionNumber, bool isTeam1)
{
	eventsStructure.typeOfEvent    = VERSION_NUMBER;
	eventsStructure.versEv_number  = versionNumber;
	eventsStructure.event_team1    = isTeam1;
	eventsStructure.isEventTreated = false;
}

bool FightSubserver::isLastEventTreated()
{
	return eventsStructure.isEventTreated;
}

void FightSubserver::threadFunction()
{
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
