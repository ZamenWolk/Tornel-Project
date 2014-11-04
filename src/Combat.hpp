#pragma clang diagnostic push
#ifndef COMBAT_HPP_INCLUDED
#define COMBAT_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <Thor/Input.hpp>

#include "AIControlledEntity.hpp"
#include "Skill.hpp"
#include "../version.hpp"
#include "../communication.hpp"

extern sf::Clock    mainClock; ///< Main clock of the program
extern IndexesIndex indexes; ///< Indexes of the game

/**
*	\file Combat.hpp
*	\brief Contains classes and functions associated to combats
*/

/**
* \addtogroup client Client side
* \brief Coumpounds used in the client application
* @{
*/

/**
*	\brief Lists all possible menus the player might be in during combat
*/

enum CombatMenu
{
	MAIN, ///< Main part of the menu
	CHARACTER_CHOOSING, ///< Character choosing menu
	TARGET_CHOOSING, ///< Target choosing menu
	SPELL_CHOOSING, ///< Spell choosing menu
	ABILITY_CHOOSING, ///< Ability choosing menu
};

/**
* 	\brief Entity for combat
* 	\details Contains extra variables and pointers to be used in combat
*/

class CombatEntity
{

public:

	/**
	*	\param[in] entity Entity to copy to the created entity
	*/

	CombatEntity(EntityModel *entity);

	/**
	*	\brief Changes the current target of the entity
	*   \param[in] newTarget New current target
	*/

	void changeTarget(CombatEntity *newTarget = NULL);

	/// \return Current entity of the CombatEntity
	EntityModel *getEntity() const;

	/// \return Current target of the entity
	CombatEntity *getTarget() const;

	/// \return Effects of the entity
	CombatEffects getEffects() const;

	/// \return ID of the entity
	unsigned long getID() const;

protected:

	EntityModel *const entity; ///< Subject of the CombatEntity
	CombatEntity *target; ///< Current target of the entity
	CombatEffects effects; ///< Effects of the entity
	unsigned long ID; ///< ID of the entity
	sf::Time      lastInteractionTime, ///< Time of last interaction
				  interactionCooldown; ///< Current cooldown
};

/**
* 	\brief Combat-handling class
* 	\details Contains both team as well as the main loop function
*/

class Combat
{
public:

	/**
	*   \param[in,out] team1Fighters Array of the members of Team 1
	*   \param[in,out] team2Fighters Array of the members of Team 2
	*	\param[in] team1Control Way the team 1 is controlled
	*	\param[in] team2Control Way the team 2 is controlled
	*	\warning Each teams can contain at max 5 fighters
	*/

	Combat(std::vector<CombatEntity> team1Fighters,
		   std::vector<CombatEntity> team2Fighters,
		   const Controls team1Control,
		   const Controls team2Control);

	/**
	*	\brief Change the current enemy team with the new team
	*	\param[in] newTeam team to replace the current team with
	*/

	void changeEnemyTeam(std::vector<CombatEntity> newTeam);

	/**
	*	\brief Main loop during a combat
	*   \param[out] window Window of the game
	*	\param[in] IPAddress Address of the server to connect to
	*	\param[in] addressPort Port to connect to on the server
	*	\return 1 if team 1 won, 0 if team 2 won
	*/

	int combatRunning(sf::RenderWindow &window, std::string IPAddress = "localhost", unsigned short addressPort = 2715);

	void setUpServer(std::string IPAddress, unsigned short addressPort);

	bool endOfCombat();

	/// Checks if the created Combat function will be able to run
	void combatChecking()
	{
		if (team1Control == AI || team1Control == ONLINE || team1Control == FROM_FILE || team1Control == KEYBOARD && team2Control == KEYBOARD || team1Control == CONTROLLER && team2Control == CONTROLLER)
		{
			errorReport("Error in combat checking");
		}
	}

protected:

	void teamInstructions(bool team1);

	void serverHandling();

	CombatEntity *IDToEntity(unsigned long entityID);

	void keyboardInstructions(std::vector<CombatEntity> *currentTeam, std::vector<CombatEntity> *currentEnemies);

	void sendToServer(CombatEntity &attacker, CombatEntity &target, AttackType type, std::string spellName = "");

	std::vector<CombatEntity> team1Fighters, ///< Array of the members of Team 1
							  team2Fighters; ///< Array of the members of Team 2

	const Controls team1Control, ///< Way the team 1 is controlled
				   team2Control; ///< Way the team 2 is controlled

	bool team1EventProcessed, ///< Is true if the team 1 thread processed the actual event
		 team2EventProcessed, ///< Is true if the team 2 thread processed the actual event
		 aboutToStop; ///< Becomes true when the end of fuction combatRunning is reached

	sf::Thread team1Thread, ///< Thread in charge of processing team 1's events
			   team2Thread, ///< Thread in charge of processing team 2's events
			   serverThread; ///< Thread in charge of receiving and handling returns from server

	sf::TcpSocket onlinePort; ///< Port to connect to in case of an online fight

	sf::Mutex onlineMutex; ///< Mutex protecting calls to onlinePort
};

/// @}

#endif // COMBAT_HPP_INCLUDED

#pragma clang diagnostic pop