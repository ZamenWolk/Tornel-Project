#include "AIEntity.hpp"
#include "../../global/define.hpp"
#include "../Indexes/IndexesIndex.hpp"
#include "../Singleton.hpp"

using namespace std;
using namespace sf;

EntityModel::EntityModel(const string &name, int level, EntityClass *monsterClass) :
        name(name),
        level(level),
        effects{0, 0, 0, monsterClass->strengthIncrement.iresult(level), monsterClass->wisdomIncrement.iresult(level), monsterClass->toughnessIncrement.iresult(
                level), monsterClass->mentalResistanceIncrement.iresult(level)},
        entityClass(monsterClass),
        knownAbilities(0),
        knownSpells(0)
{
    ID = ((Uint32)((long long int)this%4200000000));

    effects.life = monsterClass->maxLifeIncrement.iresult(level);
    effects.life += TOUGHNESS_TO_LIFE.result(effects.toughness);
    effects.life += MENTAL_RESISTANCE_TO_LIFE.result(effects.mentalResistance);
    life = effects.life;

    effects.mana = monsterClass->maxManaIncrement.iresult(level);
    effects.mana += WISDOM_TO_MANA.result(effects.wisdom);
    mana = effects.mana;

    effects.stamina = monsterClass->maxStaminaIncrement.iresult(level);
    effects.stamina += STRENGTH_TO_STAMINA.result(effects.strength);
    stamina = effects.stamina;

    getKnownSkillsFromLevel();
}

EntityModel::EntityModel(const EntityModel &entity) :
        name(entity.name),
        level(entity.level),
        life(entity.life),
        mana(entity.mana),
        stamina(entity.stamina),
        effects(entity.effects),
        entityClass(entity.entityClass),
        knownAbilities(entity.knownAbilities),
        knownSpells(entity.knownSpells),
        ID(entity.ID)
{

}

EntityModel::EntityModel(EntityInformations &entity) :
        name(entity.name),
        level(1),
        life(entity.life),
        mana(0),
        stamina(0),
        effects(entity.effects),
        entityClass(singleton<IndexesIndex>().heroClassIndex.searchByName("default")),
        knownAbilities(entity.knownAbilities),
        knownSpells(entity.knownSpells),
        ID(entity.ID)
{

}

void EntityModel::changeLife(int changeAmount)
{
    life += changeAmount;
    if (life < 0)
        life = 0;
    if (life > effects.life)
        life = effects.life;
}

void EntityModel::changeMana(int changeAmount)
{
    mana += changeAmount;
    if (mana < 0)
        mana = 0;
    if (mana > effects.mana)
        mana = effects.mana;
}

void EntityModel::changeStamina(int changeAmount)
{
    stamina += changeAmount;
    if (stamina < 0)
        stamina = 0;
    if (stamina > effects.stamina)
        stamina = effects.stamina;
}

void EntityModel::actualizeCharacteristics()
{
    int newMaxLife(0), newMaxMana(0), newMaxStamina(0);

    //Actualizes base characteristics from level
    effects.strength         = entityClass->strengthIncrement.iresult(level);
    effects.wisdom           = entityClass->wisdomIncrement.iresult(level);
    effects.toughness        = entityClass->toughnessIncrement.iresult(level);
    effects.mentalResistance = entityClass->mentalResistanceIncrement.iresult(level);

    //Calculates the new max life and changes the current life accordingly
    newMaxLife = entityClass->maxLifeIncrement.iresult(level);
    newMaxLife += TOUGHNESS_TO_LIFE.result(effects.toughness);
    newMaxLife += MENTAL_RESISTANCE_TO_LIFE.result(effects.mentalResistance);
    life += newMaxLife - effects.life;
    if (life < 0)
        life   = 0;
    effects.life = newMaxLife;

    //Calculates the new max mana and changes the current mana accordingly
    newMaxMana = entityClass->maxManaIncrement.iresult(level);
    newMaxMana += WISDOM_TO_MANA.result(effects.wisdom);
    mana += newMaxMana - effects.mana;
    if (mana < 0)
        mana   = 0;
    effects.mana = newMaxMana;

    //Calculates the new max stamina and changes the current stamina accordingly
    newMaxStamina = entityClass->maxStaminaIncrement.iresult(level);
    newMaxStamina += STRENGTH_TO_STAMINA.result(effects.strength);
    stamina += newMaxStamina - effects.stamina;
    if (stamina < 0)
        stamina   = 0;
    effects.stamina = newMaxStamina;
}

bool EntityModel::isAlive() const
{
    return life > 0;
}

string EntityModel::getName() const
{
    return name;
}

int EntityModel::getLevel() const
{
    return level;
}

int EntityModel::getLife() const
{
    return life;
}

int EntityModel::getMana() const
{
    return mana;
}

int EntityModel::getStamina() const
{
    return stamina;
}

Effects EntityModel::getEffects() const
{
    return effects;
}

vector<Skill *> EntityModel::getKnownAbilities() const
{
    return knownAbilities;
}

vector<Skill *> EntityModel::getKnownSpells() const
{
    return knownSpells;
}

void EntityModel::getKnownSkillsFromLevel()
{
    //Put the skills vectors back to 0 so they can be filled again
    while (knownAbilities.size() > 0)
    {
        knownAbilities.pop_back();
    }

    while (knownSpells.size() > 0)
    {
        knownSpells.pop_back();
    }

    //Adds every skill that meets level requirement to the appropriate vector
    for (vector<LevelingSkill>::iterator it = entityClass->getSkills().begin(); it != entityClass->getSkills().end(); it++)
    {
        if (level >= it->learnLevel)
        {
            if (it->skill->skillType == ABILITY)
            {
                knownAbilities.push_back(it->skill);
            }
            else
            {
                knownSpells.push_back(it->skill);
            }
        }
    }
}

Entity::Entity(const string &name, int level, MonsterClass *monsterClass) :
        EntityModel(name, level, (EntityClass *)monsterClass),
        weaponEffects(monsterClass->effects)
{

}

Entity::Entity(const Entity &entity) :
        EntityModel(entity),
        weaponEffects(entity.weaponEffects)
{

}

Entity::Entity(EntityInformations &entity) :
        EntityModel(entity),
        weaponEffects(entity.effects)
{

}

WeaponEffects Entity::basicAttackEffects() const
{
    return weaponEffects;
}

Uint32 EntityModel::getID() const
{
    return ID;
}
