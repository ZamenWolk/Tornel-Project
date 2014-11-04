#ifndef ENUMS_HPP_INCLUDED
#define ENUMS_HPP_INCLUDED

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

#endif