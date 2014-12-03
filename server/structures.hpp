#ifndef STRUCTURES_HPP_INCLUDED
#define STRUCTURES_HPP_INCLUDED

/**
* \file structures.hpp
* \brief Contains the structures that are specific to the server
*/

#include <vector>
#include <ctime>

#include "../src/constants.hpp"
#include "../src/AIControlledEntity.hpp"
#include "../communication.hpp"

/**
* \addtogroup server
* @{
*/

/**
* \brief Structure keeping data from the different communications from the client to the server
*/

struct EventsUnion
{
	InteractionInfos intEv;
	std::vector<EntityInformations> teamEv;
	VersionNumber versEv;
	std::tm timeEv;
};

struct EventsStructure
{
	/**
	* \param[in] typeOfEvent Type of the event
	* \param[in] isEventTreated Does the event still have to be treated
	* \param[in] intEv_infos InteractionInfos structure, in case of a fight interaction
	* \param[in] teamEv_infos EntityInformations vector, in case of team data
	* \param[in] event_team1 true if the event concerns team1, false if team2
	* \param[in] versEv_number Version number sent from the client
	*/

	EventsStructure(	 SentInfosType typeOfEvent,
						 bool isEventTreated,
						 bool event_team1);

	EventsStructure();

	SentInfosType   typeOfEvent; ///< Type of the event
	bool            isEventTreated; ///< Does the event still have to be treated
	bool            team1; ///< Which team does the event concern. true if the event concerns team1, false if team2
	EventsUnion		infos;

};

/// @}

#endif // STRUCTURES_HPP_INCLUDED
