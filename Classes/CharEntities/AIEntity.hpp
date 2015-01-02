#ifndef CLASSES_CHARENTITIES_AIENTITY_HPP
#define CLASSES_CHARENTITIES_AIENTITY_HPP

#include <string>
#include <SFML/System.hpp>

#include "../Indexes/IndexClasses.hpp"
#include "../communication.hpp"

class EntityModel
{

public:

    EntityModel(const std::string &name, int level, EntityClass *monsterClass);

    EntityModel(const EntityModel &entity);

    EntityModel(EntityInformations &entity);

    void changeLife(int changeAmount);

    void changeMana(int changeAmount);

    void changeStamina(int changeAmount);

    virtual void actualizeCharacteristics();

    bool isAlive() const;

    std::string getName() const;

    int getLevel() const;

    int getLife() const;

    int getMana() const;

    int getStamina() const;

    Effects getEffects() const;

    std::vector<Skill *> getKnownAbilities() const;

    std::vector<Skill *> getKnownSpells() const;

    sf::Uint32 getID() const;

    virtual WeaponEffects basicAttackEffects() const = 0;

protected:

    virtual void getKnownSkillsFromLevel();

    sf::Uint32 ID;
    int        level,
            life,
            mana,
            stamina;
    const std::string    name;
    Effects              effects;
    EntityClass          *entityClass;
    std::vector<Skill *> knownAbilities,
            knownSpells;

};

class Entity : public EntityModel
{
public:

    Entity(const std::string &name, int level, MonsterClass *monsterClass);

    Entity(const Entity &entity);

    Entity(EntityInformations &entity);

    virtual WeaponEffects basicAttackEffects() const;

protected:

    WeaponEffects weaponEffects;
};

#endif