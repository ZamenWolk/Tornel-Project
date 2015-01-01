#ifndef CLASSES_COMMUNICATION_HPP
#define CLASSES_COMMUNICATION_HPP

#include <string>
#include <SFML/Network.hpp>

#include "../Enums/communication.hpp"
#include "Skills/Skill.hpp"
#include "Equipment/Effects.hpp"
#include "CharEntities/CombatEntity.hpp"

struct InteractionInfos
{

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

    sf::Uint32 attackerID,
            targetID,
            baseDamage;
    AttackType  type;
    std::string spellName;
};

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
    std::string          name;
    sf::Int16            life;
    std::vector<Skill *> knownAbilities,
            knownSpells;
    CombatEffects        effects;
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

sf::Packet &operator<<(sf::Packet &packet, const EntityInformations &entity);

sf::Packet &operator>>(sf::Packet &packet, EntityInformations &entity);

sf::Packet &operator>>(sf::Packet &packet, std::vector<EntityInformations> &teamVector);

sf::Packet &operator<<(sf::Packet &packet, const InteractionInfos &infos);

sf::Packet &operator>>(sf::Packet &packet, InteractionInfos &infos);

sf::Packet &operator<<(sf::Packet &packet, const FightAction &action);

sf::Packet &operator>>(sf::Packet &packet, FightAction &action);

sf::Packet &operator<<(sf::Packet &packet, const std::vector<EntityInformations> &team);

#endif