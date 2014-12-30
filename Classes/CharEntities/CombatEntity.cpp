#include "CombatEntity.hpp"
#include "../communication.hpp"

using namespace std;
using namespace sf;

CombatEntity::CombatEntity(EntityModel *entity) :
        entity(entity),
        target(nullptr),
        effects(entity->getEffects(), entity->basicAttackEffects()),
        lastInteractionTime(milliseconds(0)),
        interactionCooldown(milliseconds(0)),
        dynamicallyAllowed(false)
{

}

CombatEntity::CombatEntity(Entity &entity) :
        entity(new Entity(entity)),
        target(nullptr),
        effects(entity.getEffects(), entity.basicAttackEffects()),
        lastInteractionTime(milliseconds(0)),
        interactionCooldown(milliseconds(0)),
        dynamicallyAllowed(true)
{

}

CombatEntity::~CombatEntity()
{
    if (dynamicallyAllowed)
    {
        delete entity;
    }
}

void CombatEntity::changeTarget(CombatEntity *newTarget)
{
    if (newTarget->entity->isAlive())
        target = newTarget;
}

void CombatEntity::changeInteractionTimes(sf::Time lastInteracTime, sf::Time interacCooldown)
{
    lastInteractionTime = lastInteracTime;
    interactionCooldown = interacCooldown;
}

EntityModel *CombatEntity::getEntity() const
{
    return entity;
}

CombatEntity *CombatEntity::getTarget() const
{
    return target;
}

CombatEffects CombatEntity::getEffects() const
{
    return effects;
}

sf::Time CombatEntity::getLastInteractionTime() const
{
    return lastInteractionTime;
}

sf::Time CombatEntity::getInteractionCooldown() const
{
    return interactionCooldown;
}

Packet &operator<<(Packet &packet, const CombatEntity &entity)
{
    packet << (Uint32)(entity.getEntity()->getID());
    packet << entity.getEntity()->getName();
    packet << entity.getEntity()->getLife();
    packet << entity.getEntity()->getKnownAbilities();
    packet << entity.getEntity()->getKnownSpells();
    packet << entity.getEffects();

    return packet;
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