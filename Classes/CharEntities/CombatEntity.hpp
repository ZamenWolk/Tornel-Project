#include "AIEntity.hpp"

class CombatEntity
{

public:

    CombatEntity(EntityModel *entity);

    CombatEntity(Entity &entity);

    ~CombatEntity();

    void changeTarget(CombatEntity *newTarget = NULL);

    void changeInteractionTimes(sf::Time lastInteracTime, sf::Time interacCooldown);

    EntityModel *getEntity() const;

    CombatEntity *getTarget() const;

    CombatEffects getEffects() const;

    sf::Time getLastInteractionTime() const;

    sf::Time getInteractionCooldown() const;

protected:

    EntityModel   *entity;
    CombatEntity  *target;
    CombatEffects effects;
    sf::Time      lastInteractionTime,
            interactionCooldown;
    bool          dynamicallyAllowed;
};

sf::Packet &operator<<(sf::Packet &packet, const CombatEntity &entity);

sf::Packet &operator<<(sf::Packet &packet, const std::vector<CombatEntity> &team);

sf::Packet &operator>>(sf::Packet &packet, std::vector<CombatEntity> &team);