#include "structures.hpp"

EventsStructure::EventsStructure(SentInfosType typeOfEvent,
								 bool isEventTreated,
								 bool event_team1):
							typeOfEvent(typeOfEvent),
							isEventTreated(isEventTreated),
							team1(event_team1)
{

}

EventsStructure::EventsStructure():
		typeOfEvent(FIGHT_INTERACTION), isEventTreated(true), team1(true)
{

}