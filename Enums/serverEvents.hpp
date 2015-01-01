#ifndef ENUMS_SERVEREVENTS_HPP
#define ENUMS_SERVEREVENTS_HPP

#include "communication.hpp"
#include "../version.hpp"
#include "../Classes/communication.hpp"

struct EventsUnion
{
	InteractionInfos                intEv;
	std::vector<EntityInformations> teamEv;
	VersionNumber                   versEv;
};

struct EventsStructure
{

	EventsStructure(SentInfosType typeOfEvent, bool isEventTreated, bool event_team1);

	EventsStructure();

	SentInfosType typeOfEvent;
	bool          isEventTreated;
	bool          team1;
	EventsUnion   infos;

};

#endif