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
#include "Screen.hpp"

extern sf::Clock    mainClock; ///< Main clock of the program
extern IndexesIndex indexes; ///< Indexes of the game

/**
* \file Combat.hpp
* \brief Contains classes and functions associated to combats
*/

/**
* \addtogroup client Client side
* \brief Coumpounds used in the client application
* @{
*/

/**
* \brief Lists all possible menus the player might be in during combat
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
	* \param[in] entity Entity to copy to the created entity
	*/

	CombatEntity(EntityModel *entity);

	CombatEntity(Entity &entity);

	~CombatEntity();

	/**
	* \brief Changes the current target of the entity
	* \param[in] newTarget New current target
	*/

	void changeTarget(CombatEntity *newTarget = NULL);

	void changeInteractionTimes(sf::Time lastInteracTime, sf::Time interacCooldown);

	/// \return Current entity of the CombatEntity
	EntityModel *getEntity() const;

	/// \return Current target of the entity
	CombatEntity *getTarget() const;

	/// \return Effects of the entity
	CombatEffects getEffects() const;

	sf::Time getLastInteractionTime() const;

	sf::Time getInteractionCooldown() const;

protected:

	EntityModel   *entity; ///< Subject of the CombatEntity
	CombatEntity  *target; ///< Current target of the entity
	CombatEffects effects; ///< Effects of the entity
	sf::Time      lastInteractionTime, ///< Time of last interaction
	              interactionCooldown; ///< Current cooldown
	bool          dynamicallyAllowed;
};

/**
* \brief Combat-handling class
* \details Contains both team as well as the main loop function
*/

class Combat : public Screen
{
public:

	/**
	* \param[in,out] team1Fighters Array of the members of Team 1
	* \param[in,out] team2Fighters Array of the members of Team 2
	* \param[in] team1Control Way the team 1 is controlled
	* \param[in] team2Control Way the team 2 is controlled
	* \warning Each teams can contain at max 5 fighters
	*/

	Combat();

	/**
	* \brief Main loop during a combat
	* \param[out] window Window of the game
	* \param[in] IPAddress Address of the server to connect to
	* \param[in] addressPort Port to connect to on the server
	* \return 1 if team 1 won, 0 if team 2 won
	*/

	virtual std::string Run(sf::RenderWindow &app, std::map<std::string, Screen *> &screens);

	virtual void Reset();

	/**
	* \brief sets up the class with the server before using it
	* \param[in] IPAddress Address of the server to connect to
	* \param[in] addressPort Port to connect to on the server
	*/

	int Setup(std::vector<CombatEntity> yourTeam, Controls controlTeam1, Controls controlTeam2, std::string IPAddress = "localhost", unsigned short addressPort = 2715);

	/**
	* \brief Handles end of combat after the actual fight ends
	* \return true if you won the battle
	* \todo Enhance so it makes real things
	*/

	std::string endOfCombat();

	/// Checks if the created Combat function will be able to run
	bool combatChecking();

	int fillFightersVector(std::vector<CombatEntity> &teamVector, bool isTeam1);

protected:

	/**
	* \brief Function running on a different thread and taking care of processing both team's events (1 function per team)
	* \param[in] team1 Is true if the function concerns the team 1
	*/

	void teamInstructions(bool team1);

	void serverHandling();

	/**
	* \brief Takes an ID and finds the entity in the fight that has this ID
	* \param[in] entityID ID to search the entity with
	* \return Pointer to the entity with the corresponding ID
	*/

	CombatEntity *IDToEntity(unsigned long entityID);

	/**
	* \brief Reads and decodes instructions for the keyboard
	* \param[in] currentTeam Team controlled for the function
	* \param[in] currentEnemies Enemies of the team controlled
	*/

	void keyboardInstructions(std::vector<CombatEntity> *currentTeam, std::vector<CombatEntity> *currentEnemies);

	void checkActionToSend(CombatEntity &attacker, CombatEntity &target, AttackType type, int baseDamage, Skill* skill = indexes.skillIndex.searchByName());

	/**
	* \brief Send an interaction to the server to be handled
	* \param[in] attacker Address of the attacker to use as an identifier to the server
	* \param[in] target Address of the target to use as an identifier to the server
	* \param[in] type Type of the attack
	* \param[in] spellName Name of the spell for the server to find in the indexes
	*/

	void sendToServer(CombatEntity &attacker, CombatEntity &target, AttackType type, int baseDamage, std::string skillName = "");

	std::vector<CombatEntity> team1Fighters, ///< Array of the members of Team 1
	                          team2Fighters; ///< Array of the members of Team 2
	Controls                  team1Control, ///< Way the team 1 is controlled
	                          team2Control; ///< Way the team 2 is controlled
	bool                      team1EventProcessed, ///< Is true if the team 1 thread processed the actual event
	                          team2EventProcessed, ///< Is true if the team 2 thread processed the actual event
	                          aboutToStop, ///< Becomes true when the end of fuction Run is reached
	                          launched;
	sf::Thread                team1Thread, ///< Thread in charge of processing team 1's events
	                          team2Thread, ///< Thread in charge of processing team 2's events
	                          serverThread; ///< Thread in charge of receiving and handling returns from server
	sf::TcpSocket             onlinePort; ///< Port to connect to in case of an online fight
	sf::Mutex                 onlineMutex; ///< Mutex protecting calls to onlinePort
};

/// @}

#endif // COMBAT_HPP_INCLUDED

#pragma clang diagnostic pop