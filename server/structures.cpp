#include "structures.hpp"

EventsStructure::EventsStructure(SentInfosType typeOfEvent,
								 bool isEventTreated,
								 InteractionInfos intEv_infos,
								 std::vector<EntityInformations> teamEv_infos,
								 bool event_team1,
								 VersionNumber versEv_number):
							typeOfEvent(typeOfEvent),
							isEventTreated(isEventTreated),
							intEv_infos(intEv_infos),
							teamEv_infos(teamEv_infos),
							event_team1(event_team1),
							versEv_number(versEv_number)
{

}

EventsStructure::EventsStructure():
		typeOfEvent(FIGHT_INTERACTION), isEventTreated(true), intEv_infos(), event_team1(true), versEv_number()
{

}