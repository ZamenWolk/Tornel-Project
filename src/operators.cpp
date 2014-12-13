#include <vector>
#include <string>

#include <SFML/System.hpp>

#include "operators.hpp"
#include "Combat.hpp"

using namespace std;
using namespace sf;

Packet &operator<<(Packet &packet, const vector<Skill *> &source)
{
	packet << source.size();

	for (vector<Skill *>::const_iterator it = source.begin(); it != source.end(); it++)
	{
		packet << (*it)->getName();
	}

	return packet;
}

Packet &operator>>(Packet &packet, ActionType &action)
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
		default:
			errorReport("Server sent an unknown action", false);
	}

	return packet;
}

Packet &operator>>(Packet &packet, SpecialAttribute &attribute)
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

Packet &operator>>(Packet &packet, AttackType &attackType)
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

Packet &operator<<(Packet &packet, const CombatEffects &source)
{
	return packet << source.life << source.mana << source.stamina << source.strength << source.wisdom << source.toughness << source.mentalResistance << source.baseDamage << source.cooldownTime.asMilliseconds();
}

Packet &operator>>(Packet &packet, CombatEffects &source)
{
	int cooldownTime;

	packet >> source.life >> source.mana >> source.stamina >> source.strength >> source.wisdom >> source.toughness >> source.mentalResistance >> source.baseDamage >> cooldownTime;

	source.cooldownTime = milliseconds(cooldownTime);

	return packet;
}

Packet &operator>>(Packet &packet, EntityInformations &entity)
{
	packet >> entity.ID;
	packet >> entity.name;
	packet >> entity.life;
	packet >> entity.mana;
	packet >> entity.stamina;

	int vectorSize;
	packet >> vectorSize;

	for (int i = 0; i < vectorSize; i++)
	{
		string skillName;
		packet >> skillName;

		entity.knownAbilities.push_back(indexes.skillIndex.searchByName(skillName));
	}

	packet >> vectorSize;

	for (int i = 0; i < vectorSize; i++)
	{
		string skillName;
		packet >> skillName;

		entity.knownSpells.push_back(indexes.skillIndex.searchByName(skillName));
	}

	packet >> entity.effects;

	return packet;
}

Packet &operator>>(Packet &packet, vector<EntityInformations> &teamVector)
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

Packet &operator<<(Packet &packet, const CombatEntity &entity)
{
	packet << (Uint32)(entity.getEntity()->getID());
	packet << entity.getEntity()->getName();
	packet << entity.getEntity()->getLife();
	packet << entity.getEntity()->getMana();
	packet << entity.getEntity()->getStamina();
	packet << entity.getEntity()->getKnownAbilities();
	packet << entity.getEntity()->getKnownSpells();
	packet << entity.getEffects();

	return packet;
}

Packet &operator<<(Packet &packet, const EntityInformations &entity)
{
	packet << entity.ID;
	packet << entity.name;
	packet << entity.life;
	packet << entity.mana;
	packet << entity.stamina;
	packet << entity.knownAbilities;
	packet << entity.knownSpells;
	packet << entity.effects;

	return packet;
}

Packet &operator<<(Packet &packet, const InteractionInfos &infos)
{
	return packet << infos.attackerID << infos.targetID << infos.type << infos.spellName;
}

Packet &operator>>(Packet &packet, InteractionInfos &infos)
{
	return packet >> infos.attackerID >> infos.targetID >> infos.type >> infos.spellName;
}

Packet &operator>>(Packet &packet, SentInfosType &infosType)
{
	int infosTypeNumber;
	packet >> infosTypeNumber;

	switch (infosTypeNumber)
	{
		case CTS_INTERACTION:
			infosType = CTS_INTERACTION;
	        break;
		case CTS_TEAM_DATA:
			infosType = CTS_TEAM_DATA;
	        break;
		case VERSION_NUMBER:
			infosType = VERSION_NUMBER;
	        break;
		case PING:
			infosType = PING;
	        break;
		case PONG:
			infosType = PONG;
	        break;
		case TIME:
			infosType = TIME;
	        break;
		case STC_ACTION:
			infosType = STC_ACTION;
			break;
		case END_OF_COMBAT:
			infosType = END_OF_COMBAT;
			break;
		default:
			errorReport("Server tried to send an unknown information type");
	}

	return packet;
}

Packet &operator<<(Packet &packet, const VersionNumber &version)
{
	return packet << version.status << version.major << version.minor << version.patch;
}

Packet &operator>>(Packet &packet, VersionNumber &version)
{
	return packet >> version.status >> version.major >> version.minor >> version.patch;
}

Packet &operator<<(Packet &packet, const vector<CombatEntity> &team)
{
	packet << team.size();

	for (vector<CombatEntity>::const_iterator it = team.begin(); it != team.end(); it++)
	{
		packet << *it;
	}

	return packet;
}

Packet &operator<<(Packet &packet, const vector<EntityInformations> &team)
{
	packet << team.size();

	for (vector<EntityInformations>::const_iterator it = team.begin(); it != team.end(); it++)
	{
		packet << *it;
	}

	return packet;
}

Packet &operator>>(Packet &packet, vector<CombatEntity> &team)
{
	int teamSize;
	packet >> teamSize;

	for (int i = 0; i < teamSize; i++)
	{
		EntityInformations receivedEntity;
		packet >> receivedEntity;

		Entity receivedCombatEntity(receivedEntity);

		team.push_back(CombatEntity(receivedCombatEntity));
	}

	return packet;
}

Packet &operator<<(Packet &packet, const Time &time)
{
	return packet << time.asMilliseconds();
}

Packet &operator>>(Packet &packet, Time &time)
{
	Int32 timeMilliseconds;

	packet >> timeMilliseconds;
	time = milliseconds(timeMilliseconds);

	return packet;
}

Packet &operator<<(Packet &packet, const tm &time)
{
	return packet << time.tm_sec << time.tm_min << time.tm_hour << time.tm_mday << time.tm_mon << time.tm_year << time.tm_isdst;
}

Packet &operator>>(Packet &packet, tm &time)
{
	return packet >> time.tm_sec >> time.tm_min >> time.tm_hour >> time.tm_mday >> time.tm_mon >> time.tm_year >> time.tm_isdst;
}


Packet &operator<<(Packet &packet, const FightAction &action)
{
	return packet << action.actionType << action.specialAttribute << action.subjectID << action.targetID << action.skillName << action.attackType << action.attackDamage;
}

Packet &operator>>(Packet &packet, FightAction &action)
{
	return packet >> action.actionType >> action.specialAttribute >> action.subjectID >> action.targetID >> action.skillName >> action.attackType >> action.attackDamage;
}