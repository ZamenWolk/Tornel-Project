#ifndef COMMUNICATION_HPP_INCLUDED
#define COMMUNICATION_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <string>
#include <vector>
#include <SFML/System.hpp>

#include "src/Equipment.hpp"
#include "src/operators.hpp"
#include "communication.cpp"

class Skill;

/**
* \file communication.hpp
* \brief Contains all the functions and enums for the communication between client and server
*/

/**
* \addtogroup both Shared
* \brief Compounds shared between client and server
* \ingroup server client
* @{
*/

/**
* \brief Structures used to send version numbers between server and client
*/

struct VersionNumber
{
	/**
	* \param[in] status Status of the game
	* \param[in] major Major number of the game version
	* \param[in] minor Minor number of the game version
	* \param[in] patch Patch number of the game version
	*/

	VersionNumber(std::string status, sf::Int32 major, sf::Int32 minor, sf::Int32 patch) :
			status(status),
			major(major),
			minor(minor),
			patch(patch)
	{

	}

	VersionNumber() :
			status(""),
			major(0),
			minor(0),
			patch(0)
	{

	}

	~VersionNumber()
	{

	}

	std::string status; ///< Status of the game
	sf::Int32   major; ///< Major number of the game version
	sf::Int32   minor; ///< Minor number of the game version
	sf::Int32   patch; ///< Patch number of the game version
};

/**
* \brief Structures used to send interactions between server and client
*/

struct InteractionInfos
{
	/**
	* \param[in] attackerID ID of the attacker
	* \param[in] targetID ID of the target
	* \param[in] type Type of the interaction
	* \param[in] spellName Name of the spell, if used
	*/

	InteractionInfos(sf::Uint32 attackerID, sf::Uint32 targetID, AttackType type, sf::Uint32 baseDamage, std::string spellName) :
			attackerID(attackerID),
			targetID(targetID),
			type(type),
			spellName(spellName),
			baseDamage(baseDamage)
	{

	}

	InteractionInfos() :
			attackerID(0),
			targetID(0),
			type(WEAPON_ATTACK),
			spellName(""),
			baseDamage(0)
	{

	}

	~InteractionInfos()
	{

	}

	sf::Uint32 attackerID, ///< ID of the attacker
	            targetID, ///< ID of the target
				baseDamage;
	AttackType  type; ///< Type of the interaction
	std::string spellName; ///< Name of the spell, if used
};

/**
* \brief Informations received from server to create premade entities
*/

struct EntityInformations
{
	EntityInformations() :
			name(""),
			life(0),
			knownAbilities(),
			knownSpells(),
			effects()
	{
		ID = ((sf::Uint32)((long long int)this%4200000000));
	}

	EntityInformations(std::string name,
	                   int life,
	                   int mana,
	                   int stamina,
	                   std::vector<Skill *> knownAbilities,
	                   std::vector<Skill *> knownSpells,
	                   CombatEffects effects,
	                   sf::Uint32 ID) :
			name(name),
			life((sf::Int16)life),
			knownAbilities(knownAbilities),
			knownSpells(knownSpells),
			effects(effects),
			ID(ID)
	{

	}

	sf::Uint32           ID;
	std::string          name; ///< Name of the entity
	sf::Int16            life; ///< Current life of the entity
	std::vector<Skill *> knownAbilities, ///< Known abilities of the entity
	                     knownSpells; ///< Known spells of the entity
	CombatEffects        effects; ///< Current effects of the entity
};

struct FightAction
{
	FightAction() :
			actionType(),
			specialAttribute(),
			subjectID(0),
			targetID(0),
			skillName(""),
			attackType(),
			attackDamage(0),
			subject(0),
			target(0),
			skill(0)
	{

	}

	FightAction(ActionType actionType,
	            SpecialAttribute specialAttribute,
	            sf::Uint32 subjectID,
	            sf::Uint32 targetID,
	            std::string skillName,
	            AttackType attackType,
	            int attackDamage) :
			actionType(actionType),
			specialAttribute(specialAttribute),
			subjectID(subjectID),
			targetID(targetID),
			skillName(skillName),
			attackType(attackType),
			attackDamage(attackDamage),
			subject(0),
			target(0),
			skill(0)
	{

	}

	ActionType       actionType;
	SpecialAttribute specialAttribute;
	sf::Uint32       subjectID, targetID;
	std::string      skillName;
	AttackType       attackType;
	sf::Int32        attackDamage;
	CombatEntity     *subject, *target;
	Skill            *skill;
};

struct EOFStruct
{

};

sf::Packet &emptyPacket(sf::Packet &packet);

/**
* \brief Creates a packet with a some info and the SentInfosType going with it
* \param[in] packet Packet to flux the informations to
* \param[in] infos version structure to flux into the packet
* \param[in] type type of info contained in the structure
* \return updated packet
*/

template<typename T>
sf::Packet &createPacket(sf::Packet &packet, const T &infos, SentInfosType type)
{
	if (   (typeid(infos) == typeid(const VersionNumber) && type == VERSION_NUMBER)
	    || (typeid(infos) == typeid(const InteractionInfos) && type == CTS_INTERACTION)
	    || (typeid(infos) == typeid(const std::vector<CombatEntity>) && type == TEAM_DATA)
	    || (typeid(infos) == typeid(const int) && (type == PING || type == PONG))
		|| (typeid(infos) == typeid(const FightAction) && type == STC_ACTION)
	    || (typeid(infos) == typeid(const EOFStruct) && type == END_OF_COMBAT)
		|| (typeid(infos) == typeid(const tm) && type == STC_DEBUT_TIME)
		|| (typeid(infos) == typeid(const FightAction) && type == STC_ACTION))
	{
		emptyPacket(packet);
		return packet << type << infos;
	}
	else
	{
		errorReport("The type of info sent does not match the type of variable");
		return packet;
	}
}

sf::Packet &infoTypeInPacket(sf::Packet &packet, SentInfosType &type);

template<typename T>
sf::Packet &deconstructPacket(sf::Packet &packet, T &infos, SentInfosType type)
{
	if (   (typeid(infos) == typeid(VersionNumber) && type == VERSION_NUMBER)
	    || (typeid(infos) == typeid(InteractionInfos) && type == CTS_INTERACTION)
	    || (typeid(infos) == typeid(std::vector<CombatEntity>) && type == TEAM_DATA)
	    || (typeid(infos) == typeid(int) && (type == PING || type == PONG))
	    || (typeid(infos) == typeid(FightAction) && type == STC_ACTION)
	    || (typeid(infos) == typeid(EOFStruct) && type == END_OF_COMBAT)
        || (typeid(infos) == typeid(tm) && type == STC_DEBUT_TIME)
        || (typeid(infos) == typeid(FightAction) && type == STC_ACTION))
	{
		return packet >> infos;
	}
	else
	{
		errorReport("The type of info sent does not match the type of variable");
		return packet;
	}
}

/// @}

#endif