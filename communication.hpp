#ifndef COMMUNICATION_HPP_INCLUDED
#define COMMUNICATION_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <string>
#include <vector>
#include <SFML/System.hpp>

#include "src/Equipment.hpp"
#include "src/operators.hpp"

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
* \brief Informations received from server to create premade entities
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
	if ((typeid(infos) == typeid(VersionNumber const) && type == VERSION_NUMBER) || (typeid(infos) == typeid(const sf::Time) && type == PING) || (typeid(infos) == typeid(const std::vector<CombatEntity>) && type == TEAM_DATA))
	{
		return packet << type << infos;
	}
	else
	{
		errorReport("The type of info sent does not match the type of variable");
		return packet;
	}
}

sf::Packet & infoTypeInPacket(sf::Packet &packet, SentInfosType &type);

template<typename T>
sf::Packet &deconstructPacket(sf::Packet &packet, T &infos, SentInfosType type)
{
	if ((typeid(infos) == typeid(VersionNumber const) && type == VERSION_NUMBER)
		|| (typeid(infos) == typeid(const sf::Time) && type == PING)
		|| (typeid(infos) == typeid(const std::vector<CombatEntity>) && type == TEAM_DATA))
	{
		return packet >> infos;
	}
	else
	{
		errorReport("The type of info sent does not match the type of variable");
		return packet;
	}
}

sf::Packet & emptyPacket(sf::Packet &packet);

/// @}

#endif