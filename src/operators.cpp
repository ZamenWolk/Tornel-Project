#include <vector>
#include <string>

#include <SFML/System.hpp>

#include "operators.hpp"
#include "Combat.hpp"
#include "../communication.hpp"

sf::Packet &operator<<(sf::Packet &packet, const std::vector<Skill *> &source)
{
	packet << source.size();

	for (std::vector<Skill *>::const_iterator it = source.begin(); it != source.end(); it++)
	{
		packet << (*it)->getName();
	}

	return packet;
}

sf::Packet &operator>>(sf::Packet &packet, ActionType &action)
{
	int actionNumber;
	packet >> actionNumber;

	switch (actionNumber)
	{
		case NONE:
			action = NONE;
			break;
		case DEAL_DAMAGE:
			action = DEAL_DAMAGE;
			break;
		case HEAL:
			action = HEAL;
			break;
		case END_OF_FIGHT:
			action = END_OF_FIGHT;
			break;
		default:
			errorReport("Server sent an unknown action", 0);
	}

	return packet;
}

sf::Packet &operator>>(sf::Packet &packet, SpecialAttribute &attribute)
{
	int attributeNumber;
	packet >> attributeNumber;

	switch (attributeNumber)
	{
		case NO_SPECIAL:
			attribute = NO_SPECIAL;
			break;
		case NOT_ENOUGH_CP:
			attribute = NOT_ENOUGH_CP;
			break;
		case MISSED:
			attribute = MISSED;
			break;
		case DODGED:
			attribute = DODGED;
			break;
		case BLOCKED:
			attribute = BLOCKED;
			break;
		case CRITICAL:
			attribute = CRITICAL;
			break;
		default:
			errorReport("Server sent an unknown attribute", 0);
	}

	return packet;
}

sf::Packet &operator>>(sf::Packet &packet, AttackType &attackType)
{
	int typeNumber;
	packet >> typeNumber;

	switch (typeNumber)
	{
		case WEAPON_ATTACK:
			attackType = WEAPON_ATTACK;
			break;
		case SPELL:
			attackType = SPELL;
			break;
		case ABILITY:
			attackType = ABILITY;
			break;
		default:
			errorReport("Unknown action type", 0);
	}

	return packet;
}

sf::Packet &operator<<(sf::Packet &packet, const CombatEffects &source)
{
	return packet << source.life << source.mana << source.stamina << source.strength << source.wisdom << source.toughness << source.mentalResistance << source.baseDamage << source.cooldownTime.asMilliseconds();
}

sf::Packet &operator>>(sf::Packet &packet, CombatEffects &source)
{
	int cooldownTime;

	packet >> source.life >> source.mana >> source.stamina >> source.strength >> source.wisdom >> source.toughness >> source.mentalResistance >> source.baseDamage >> cooldownTime;

	source.cooldownTime = sf::milliseconds(cooldownTime);

	return packet;
}

sf::Packet &operator>>(sf::Packet &packet, EntityInformations &entity)
{
	packet >> entity.name;
	packet >> entity.life;
	packet >> entity.mana;
	packet >> entity.stamina;

	int vectorSize;
	packet >> vectorSize;

	for (int i = 0; i < vectorSize; i++)
	{
		std::string skillName;
		packet >> skillName;

		entity.knownAbilities.push_back(indexes.skillIndex.searchByName(skillName));
	}

	packet >> vectorSize;

	for (int i = 0; i < vectorSize; i++)
	{
		std::string skillName;
		packet >> skillName;

		entity.knownSpells.push_back(indexes.skillIndex.searchByName(skillName));
	}

	packet >> entity.effects;

	return packet;
}

sf::Packet &operator>>(sf::Packet &packet, std::vector<EntityInformations> &teamVector)
{
	int numberOfElements(0);

	packet >> numberOfElements;

	for (int i = 0; i < numberOfElements; i++)
	{
		EntityInformations currentEntity;

		packet >> currentEntity;

		teamVector.push_back(currentEntity);
	}

	return packet;
}

sf::Packet &operator<<(sf::Packet &packet, const CombatEntity &entity)
{
	packet << (sf::Uint32)(entity.getID());
	packet << entity.getEntity()->getName();
	packet << entity.getEntity()->getLife();
	packet << entity.getEntity()->getMana();
	packet << entity.getEntity()->getStamina();
	packet << entity.getEntity()->getKnownAbilities();
	packet << entity.getEntity()->getKnownSpells();
	packet << entity.getEffects();

	return packet;
}

sf::Packet &operator<<(sf::Packet &packet, const InteractionInfos &infos)
{
	return packet << infos.attackerID << infos.targetID << infos.type << infos.spellName;
}

sf::Packet &operator>>(sf::Packet &packet, InteractionInfos &infos)
{
	return packet >> infos.attackerID >> infos.targetID >> infos.type >> infos.spellName;
}

sf::Packet &operator>>(sf::Packet &packet, SentInfosType &infosType)
{
	int infosTypeNumber;
	packet >> infosTypeNumber;

	switch (infosTypeNumber)
	{
		case FIGHT_INTERACTION:
			infosType = FIGHT_INTERACTION;
			break;
		case TEAM_DATA:
			infosType = TEAM_DATA;
			break;
		case VERSION_NUMBER:
			infosType = VERSION_NUMBER;
			break;
		case PING:
			infosType = PING;
			break;
		default:
			errorReport("Server tried to send an unknown information type");
	}

	return packet;
}

sf::Packet &operator<<(sf::Packet &packet, const VersionNumber &version)
{
	return packet << version.status << version.major << version.minor << version.patch;
}

sf::Packet &operator>>(sf::Packet &packet, VersionNumber &version)
{
	return packet >> version.status >> version.major << version.minor << version.patch;
}

sf::Packet &operator<<(sf::Packet &packet, const std::vector<CombatEntity> &team)
{
	packet << team.size();

	for (std::vector<CombatEntity>::const_iterator it = team.begin(); it != team.end(); it++)
	{
		packet << *it;
	}

	return packet;
}

sf::Packet &operator>>(sf::Packet &packet, std::vector<CombatEntity> &team)
{
	int teamSize;
	packet >> teamSize;

	for (int i = 0; i <= teamSize; i++)
	{
		EntityInformations receivedEntity;
		packet >> receivedEntity;

		team.push_back(receivedEntity);
	}

	return packet;
}

sf::Packet &operator<<(sf::Packet &packet, const sf::Time &time)
{
	return packet << time.asMilliseconds();
}

sf::Packet &operator>>(sf::Packet &packet, sf::Time &time)
{
	sf::Int32 timeMilliseconds;

	packet >> timeMilliseconds;
	time = sf::milliseconds(timeMilliseconds);

	return packet;
}