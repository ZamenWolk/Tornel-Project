#ifndef COMMUNICATION_HPP_INCLUDED
#define COMMUNICATION_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <string>
#include <vector>
#include <SFML/System.hpp>
#include "src/Skill.hpp"
#include "src/Equipement.hpp"
#include "src/operators.hpp"
#include "src/Equipement.hpp"

/**
* \file ccommunication.hpp
* \brief Contains all the functions and enums for the communication between client and server
*/

/**
* \addtogroup both Shared
* \brief Compounds shared between client and server
* \ingroup server client
* @{
*/

/**
*   \brief Precise the type of the attack
*/

enum AttackType
{
	WEAPON_ATTACK = 0, ///< Weapon attack
	SPELL         = 1, ///< Mana-oriented skill
	ABILITY       = 2, ///< Stamina-oriented skill
};
/**
* \brief Lists all possible outputs for combat interactions
*/

enum ActionType
{
	NONE         = 0, ///< Do nothing
	DEAL_DAMAGE  = 1, ///< Deal damage to the target
	HEAL         = 2, ///< Heal the target
	END_OF_FIGHT = 3, ///< The fight ended
};
/**
* \brief Lists all possible attributes of the returns from the server
*/

enum SpecialAttribute
{
	NO_SPECIAL    = 0, ///< Nothing special
	NOT_ENOUGH_CP = 1, ///< Not enough capacity points
	MISSED        = 2, ///< Missed the interaction
	DODGED        = 3, ///< Target dodged the interaction
	BLOCKED       = 4, ///< Target blocked the interaction
	CRITICAL      = 5, ///< Critical output for interaction
};
/**
*   \brief Lists possible types of informations sent between server and client
*/

enum SentInfosType
{
	FIGHT_INTERACTION = 0, ///< Interaction sent to the server to describe an interaction between players
	TEAM_DATA         = 1, ///< Data sent to the server to describe the client's team
	VERSION_NUMBER    = 2, ///< Data sent to the server to check if client and server version match
	PING              = 3,
};

/**
*   \brief Structures used to send version numbers between server and client
*/

struct VersionNumber
{
	/**
	*   \param[in] status Status of the game
	*   \param[in] major Major number of the game version
	*   \param[in] minor Minor number of the game version
	*   \param[in] patch Patch number of the game version
	*/

	VersionNumber(std::string status, sf::Int32 major, sf::Int32 minor, sf::Int32 patch) :
			status(status), major(major), minor(minor), patch(patch)
	{

	}

	VersionNumber() :
			status(""), major(0), minor(0), patch(0)
	{

	}

	std::string status; ///< Status of the game
	sf::Int32   major; ///< Major number of the game version
	sf::Int32   minor; ///< Minor number of the game version
	sf::Int32   patch; ///< Patch number of the game version
};

/**
*   \brief Structures used to send interactions between server and client
*/

struct InteractionInfos
{
	/**
	*   \param[in] attackerID ID of the attacker
	*   \param[in] targetID ID of the target
	*   \param[in] type Type of the interaction
	*   \param[in] spellName Name of the spell, if used
	*/

	InteractionInfos(sf::Uint32 attackerID, sf::Uint32 targetID, AttackType type, std::string spellName) :
			attackerID(attackerID), targetID(targetID), type(type), spellName(spellName)
	{

	}

	InteractionInfos() :
			attackerID(0), targetID(0), type(WEAPON_ATTACK), spellName("")
	{

	}

	sf::Uint32 attackerID, ///< ID of the attacker
				targetID; ///< ID of the target
	AttackType  type; ///< Type of the interaction
	std::string spellName; ///< Name of the spell, if used
};

/**
*	\brief Informations received from server to create premade entities
*/

struct EntityInformations
{
	std::string name; ///< Name of the entity
	int         life, ///< Current life of the entity
				mana, ///< Current mana of the entity
						 stamina; ///< Current stamina of the entity
	std::vector<Skill *> knownAbilities, ///< Known abilities of the entity
						 knownSpells; ///< Known spells of the entity
	CombatEffects        effects; ///< Current effects of the entity
};

/// @}

#endif