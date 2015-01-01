#include "Hero.hpp"
#include "../../global/define.hpp"
#include "../Singleton.hpp"
#include "../Indexes/IndexesIndex.hpp"

using namespace std;
using namespace sf;

Hero::Hero(const string &name, int experiencePoints, EntityClass *heroClass) :
        experiencePoints(experiencePoints),
        EntityModel(name, EXPERIENCE_TO_LEVEL.iresult(experiencePoints), heroClass),
        weapon(singleton<IndexesIndex>().weaponIndex.searchByName("Default")),
        helmet(singleton<IndexesIndex>().helmetIndex.searchByName("Default")),
        chestplate(singleton<IndexesIndex>().chestplateIndex.searchByName("Default")),
        leggings(singleton<IndexesIndex>().leggingsIndex.searchByName("Default")),
        boots(singleton<IndexesIndex>().bootsIndex.searchByName("Default"))
{

}

void Hero::gainXP(unsigned int xpGained)
{
    experiencePoints += xpGained;
}

int Hero::getExperiencePoints() const
{
    return experiencePoints;
}

WeaponEffects Hero::basicAttackEffects() const
{
    return weapon->getWeaponEffects();
}

void Hero::actualizeCharacteristics()
{
    int newMaxLife(0), oldMaxLife(effects.life), newMaxMana(0), oldMaxMana(effects.mana), newMaxStamina(0), oldMaxStamina(effects.stamina);

    effects = Effects();

    effects.strength         = entityClass->strengthIncrement.iresult(level);
    effects.wisdom           = entityClass->wisdomIncrement.iresult(level);
    effects.toughness        = entityClass->toughnessIncrement.iresult(level);
    effects.mentalResistance = entityClass->mentalResistanceIncrement.iresult(level);

    effects += weapon->getEquipmentEffects();
    effects += helmet->getEquipmentEffects();
    effects += chestplate->getEquipmentEffects();
    effects += leggings->getEquipmentEffects();
    effects += boots->getEquipmentEffects();

    newMaxLife = entityClass->maxLifeIncrement.iresult(level);
    newMaxLife += TOUGHNESS_TO_LIFE.result(effects.toughness);
    newMaxLife += MENTAL_RESISTANCE_TO_LIFE.result(effects.mentalResistance);
    effects.life += newMaxLife;
    life += effects.life - oldMaxLife;

    newMaxMana = entityClass->maxManaIncrement.iresult(level);
    newMaxMana += WISDOM_TO_MANA.result(effects.wisdom);
    effects.mana += newMaxMana;
    mana += effects.mana - oldMaxMana;

    newMaxStamina = entityClass->maxStaminaIncrement.iresult(level);
    newMaxStamina += STRENGTH_TO_STAMINA.result(effects.strength);
    effects.stamina += newMaxStamina;
    stamina += effects.stamina - oldMaxStamina;
}

void Hero::changeEquipment(EquipmentType type, Equipment *newEquipment)
{
    if (newEquipment == NULL)
    {
        switch (type)
        {
            case HELMET:
                newEquipment = singleton<IndexesIndex>().helmetIndex.searchByName("Default");
                break;

            case CHESTPLATE:
                newEquipment = singleton<IndexesIndex>().chestplateIndex.searchByName("Default");
                break;

            case LEGGINGS:
                newEquipment = singleton<IndexesIndex>().leggingsIndex.searchByName("Default");
                break;

            case BOOTS:
                newEquipment = singleton<IndexesIndex>().bootsIndex.searchByName("Default");
                break;

            case WEAPON:
                newEquipment = singleton<IndexesIndex>().weaponIndex.searchByName("Default");
                break;
        }
    }


    if (level >= newEquipment->getPrerequisiteLevel() && effects >= newEquipment->getPrerequisites())
    {
        switch (type)
        {
            case HELMET:
                helmet = newEquipment;
                break;

            case CHESTPLATE:
                chestplate = newEquipment;
                break;

            case LEGGINGS:
                leggings = newEquipment;
                break;

            case BOOTS:
                boots = newEquipment;
                break;

            case WEAPON:
                weapon = (Weapon *)newEquipment;
                break;
        }
    }

    actualizeCharacteristics();
}

void Hero::actualizeLevel()
{
    level = EXPERIENCE_TO_LEVEL.iresult(experiencePoints);

    actualizeCharacteristics();
    getKnownSkillsFromLevel();
}