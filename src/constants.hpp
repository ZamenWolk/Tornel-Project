#ifndef CONSTANTS_HPP_INCLUDED
#define CONSTANTS_HPP_INCLUDED

#include <SFML/Network.hpp>

//#include "../version.hpp"

   /**
	*	\file constants.hpp
	*	\brief Contains all the preprocessor definitions
	*/

#define WINDOW_HEIGHT 600 ///< Height of the game window in pixels

#define WINDOW_WIDTH 1067 ///< Width of the window in pixels

#define OLD_EXPERIENCE_TO_LEVEL ExponentialFunction(true, 0.9996, 11485.0, 100.0, 0.0, 4000.0) ///< Function converting the number of experience points to the level
#define EXPERIENCE_TO_LEVEL ExponentialFunction(true, 0.99996, 114900.0, 100.1, 0.0, 40000.0) ///< New function to convert the experience to the level (Still waiting for approval)

#define STRENGTH_TO_ATTACK_FACTOR ThirdPowerFunction(1, 0.00275, -0.000000625) ///< Function converting entities' strength into attack factor

#define STRENGTH_TO_STAMINA ThirdPowerFunction(0, 0.1, -0.000011) ///< Function converting entities' strength into stamina

#define WISDOM_TO_ATTACK_FACTOR ThirdPowerFunction(1, 0.00275, -0.000000625) ///< Function converting entities' wisdom into attack factor

#define WISDOM_TO_MANA ThirdPowerFunction(0, 0.4, -0.0001) ///< Function converting entities' wisdom into mana

#define TOUGHNESS_TO_ATTACK_REDUCTION ThirdPowerFunction(1, -0.0009, 0.000000225) ///< Function converting entities' toughness into attack reduction

#define TOUGHNESS_TO_LIFE ThirdPowerFunction(0, 8.0/30.0, -2.0/30000.0, 0, 2000) ///< Function converting entities' toughness into life

#define MENTAL_RESISTANCE_TO_ATTACK_REDUCTION ThirdPowerFunction(1, -0.0009, 0.000000225) ///< Function converting entities' mental resistance into attack reduction

#define MENTAL_RESISTANCE_TO_LIFE ThirdPowerFunction(0, 4.0/30.0, -1.0/30000.0, 0, 2000) ///< Function converting entities' mental resistance into life


   /**
    *   \brief Precise the type of the attack
    */

enum AttackType{	WEAPON_ATTACK = 0, ///< Weapon attack
					SPELL = 1, ///< Mana-oriented skill
					ABILITY = 2, ///< Stamina-oriented skill
					};

   /**
	* \brief Lists all possible outputs for combat interactions
	*/

enum ActionType{    NONE = 0, ///< Do nothing
                    DEAL_DAMAGE = 1, ///< Deal damage to the target
                    HEAL = 2, ///< Heal the target
                    END_OF_FIGHT = 3, ///< The fight ended
                    };

   /**
    * \brief Lists all possible attributes of the returns from the server
    */

enum SpecialAttribute{  NO_SPECIAL = 0, ///< Nothing special
                        NOT_ENOUGH_CP = 1, ///< Not enough capacity points
                        MISSED = 2, ///< Missed the interaction
                        DODGED = 3, ///< Target dodged the interaction
                        BLOCKED = 4, ///< Target blocked the interaction
                        CRITICAL = 5, ///< Critical output for interaction
                        };

   /**
	* 	\brief Lists all possible ways to control a team during fights
	*/

enum Controls{	KEYBOARD, ///< Controlled by keyboard
				CONTROLLER, ///< Controlled by a gamepad
				AI, ///< Controlled by the AI
				ONLINE, ///< Actions received from online
				FROM_FILE, ///< Actions read from a file
				};

   /**
	*	\brief Lists all possible menus the player might be in during combat
	*/

enum CombatMenu{	MAIN, ///< Main part of the menu
					CHARACTER_CHOOSING, ///< Character choosing menu
					TARGET_CHOOSING, ///< Target choosing menu
					SPELL_CHOOSING, ///< Spell choosing menu
					ABILITY_CHOOSING, ///< Ability choosing menu
					};

   /**
	*	\brief Lists all possible types of equipement
	*/

enum EquipementType{HELMET, ///< Head equipement
					CHESTPLATE, ///< Torso equipement
					LEGGINGS, ///< Legs equipement
					BOOTS, ///< Feet equipement
					WEAPON, ///< Weapon equipement
					};

   /**
    *   \brief Lists possible types of informations sent between server and client
    */

enum SentInfosType{ FIGHT_INTERACTION = 0, ///< Interaction sent to the server to describe an interaction between players
                    TEAM_DATA = 1, ///< Data sent to the server to describe the client's team
                    VERSION_NUMBER = 2, ///< Data sent to the server to check if client and server version match
                    PING = 3,
                    };

   /**
    *   \brief Structures used to send version numbers between server and client
    */

struct VersionNumber
{
   /**
    *   \param[in] status_b Status of the game
    *   \param[in] major_b Major number of the game version
    *   \param[in] minor_b Minor number of the game version
    */

    VersionNumber(  std::string status,
                    sf::Int32 major,
					sf::Int32 minor,
					sf::Int32 patch):
                        status(status),
                        major(major),
   						minor(minor),
   						patch(patch)
    {

    }

    VersionNumber():
                status(""),
                major(0),
				minor(0),
				patch(0)
    {

    }

    std::string status; ///< Status of the game
    sf::Int32 major; ///< Major number of the game version
	sf::Int32 minor; ///< Minor number of the game version
	sf::Int32 patch; ///< Patch number of the game version
};

   /**
    *   \brief Structures used to send interactions between server and client
    */

struct InteractionInfos
{
   /**
    *   \param[in] attackerID_b ID of the attacker
    *   \param[in] targetID_b ID of the target
    *   \param[in] type_b Type of the interaction
    *   \param[in] spellName_b Name of the spell, if used
    */

    InteractionInfos(   sf::Uint32 attackerID,
                        sf::Uint32 targetID,
                        AttackType type,
                        std::string spellName):
                            attackerID(attackerID),
                            targetID(targetID),
                            type(type),
                            spellName(spellName)
    {

    }

    InteractionInfos():
                attackerID(0),
                targetID(0),
                type(WEAPON_ATTACK),
                spellName("")
    {

    }

    sf::Uint32  attackerID, ///< ID of the attacker
                targetID; ///< ID of the target
    AttackType  type; ///< Type of the interaction
    std::string spellName; ///< Name of the spell, if used
};

   /**
	*	\brief Function called in case of error
	*/

void errorReport(std::string errorMessage, bool isFatal = 1);

#endif // CONSTANTS_HPP_INCLUDED
