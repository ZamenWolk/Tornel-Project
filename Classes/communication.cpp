#include "communication.hpp"
#include "Singleton.hpp"
#include "Indexes/IndexesIndex.hpp"

using namespace sf;
using namespace std;

Packet &operator<<(Packet &packet, const EntityInformations &entity)
{
    packet << entity.ID;
    packet << entity.name;
    packet << entity.life;
    packet << entity.knownAbilities;
    packet << entity.knownSpells;
    packet << entity.effects;

    return packet;
}

Packet &operator>>(Packet &packet, EntityInformations &entity)
{
    packet >> entity.ID;
    packet >> entity.name;
    packet >> entity.life;

    int vectorSize;
    packet >> vectorSize;

    for (int i = 0; i < vectorSize; i++)
    {
        string skillName;
        packet >> skillName;

        entity.knownAbilities.push_back(singleton<IndexesIndex>().skillIndex.searchByName(skillName));
    }

    packet >> vectorSize;

    for (int i = 0; i < vectorSize; i++)
    {
        string skillName;
        packet >> skillName;

        entity.knownSpells.push_back(singleton<IndexesIndex>().skillIndex.searchByName(skillName));
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

Packet &operator<<(Packet &packet, const InteractionInfos &infos)
{
    return packet << infos.attackerID << infos.targetID << infos.type << infos.baseDamage << infos.spellName;
}

Packet &operator>>(Packet &packet, InteractionInfos &infos)
{
    return packet >> infos.attackerID >> infos.targetID >> infos.type >> infos.baseDamage >> infos.spellName;
}

Packet &operator<<(Packet &packet, const FightAction &action)
{
    return packet << action.actionType << action.specialAttribute << action.subjectID << action.targetID << action.skillName << action.attackType << action.attackDamage;
}

Packet &operator>>(Packet &packet, FightAction &action)
{
    return packet >> action.actionType >> action.specialAttribute >> action.subjectID >> action.targetID >> action.skillName >> action.attackType >> action.attackDamage;
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