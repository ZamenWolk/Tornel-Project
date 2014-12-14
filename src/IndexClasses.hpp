#ifndef INDEXCLASSES_HPP_INCLUDED
#define INDEXCLASSES_HPP_INCLUDED

#include <string>

#include "mathfuncs.hpp"
#include "Skill.hpp"

/**
* \brief Class storing types of equipment for each piece of equipment
*/

class UsableEquipTypes
{
public:
    UsableEquipTypes() :
            usableHelmetTypes(1, "Admin"),
            usableChestTypes(1, "Admin"),
            usableLeggingsTypes(1, "Admin"),
            usableBootsTypes(1, "Admin"),
            usableWeaponTypes(1, "Admin")
    {

    }

    /**
    * \brief Adds a type to one of the vectors
    * \param[in] typeName name of the type to add
    * \param[in] equipmentType vector to add the entry to
    * \return true if the type was added to the corresponding index
    * \warning The type must be registered in the corresponding index to be added here
    */

    bool addUsableType(std::string &typeName, EquipmentType equipmentType);

    /**
    * \param[in] helmetTypes Types to add to the helmet vector
    * \param[in] chestTypes Types to add to the chestplate vector
    * \param[in] leggingsTypes Types to add to the leggings vector
    * \param[in] bootsTypes Types to add to the boots vector
    * \param[in] weaponTypes Types to add to the weapon vector
    */

    UsableEquipTypes(std::vector<std::string> helmetTypes,
            std::vector<std::string> chestTypes,
            std::vector<std::string> leggingsTypes,
            std::vector<std::string> bootsTypes,
            std::vector<std::string> weaponTypes);

protected:
    std::vector<std::string> usableHelmetTypes, ///< Types of helmet
            usableChestTypes, ///< Types of chestplate
            usableLeggingsTypes, ///< Types of leggings
            usableBootsTypes, ///< Types of boots
            usableWeaponTypes; ///< Types of weapon
};

/**
* \brief Member of characters index
*/

struct EntityClass
{

    /**
    * \param[in] name Name of the class
    * \param[in] maxLifeIncrement Evolution followed by the index member's life
    * \param[in] maxManaIncrement Evolution followed by the index member's mana
    * \param[in] maxStaminaIncrement Evolution followed by the index member's stamina
    * \param[in] strengthIncrement Evolution followed by the index member's strength
    * \param[in] wisdomIncrement Evolution followed by the index member's wisdom
    * \param[in] toughnessIncrement Evolution followed by the index member's toughness
    * \param[in] mentalResistanceIncrement Evolution followed by the index member's mental resistance
    */

    EntityClass(std::string name,
            ThirdPowerFunction maxLifeIncrement,
            ThirdPowerFunction maxManaIncrement,
            ThirdPowerFunction maxStaminaIncrement,
            ThirdPowerFunction strengthIncrement,
            ThirdPowerFunction wisdomIncrement,
            ThirdPowerFunction toughnessIncrement,
            ThirdPowerFunction mentalResistanceIncrement);

    /// \return name of the member
    std::string getName() const;

    /// \return Skills of the class
    virtual std::vector<LevelingSkill> getSkills() = 0;

    std::string        name; ///< Name of the class
    ThirdPowerFunction maxLifeIncrement, ///< Evolution followed by the index member's life
            maxManaIncrement, ///< Evolution followed by the index member's mana
            maxStaminaIncrement, ///< Evolution followed by the index member's stamina
            strengthIncrement, ///< Evolution followed by the index member's strength
            wisdomIncrement, ///< Evolution followed by the index member's wisdom
            toughnessIncrement, ///< Evolution followed by the index member's toughness
            mentalResistanceIncrement; ///< Evolution followed by the index member's mental resistance
};

/**
* \brief Class of a hero
*/

struct HeroClass : public EntityClass
{

    /**
    * \param[in] name Name of the class
    * \param[in] maxLifeIncrement Evolution followed by the index member's life
    * \param[in] maxManaIncrement Evolution followed by the index member's mana
    * \param[in] maxStaminaIncrement Evolution followed by the index member's stamina
    * \param[in] strengthIncrement Evolution followed by the index member's strength
    * \param[in] wisdomIncrement Evolution followed by the index member's wisdom
    * \param[in] toughnessIncrement Evolution followed by the index member's toughness
    * \param[in] mentalResistanceIncrement Evolution followed by the index member's mental resistance
    * \param[in] usableTypes Equipment types the hero can equip and use
    * \param[in] learnableSkills All the skills the hero can learn throughout the levels
    */

    HeroClass(std::string name,
            ThirdPowerFunction maxLifeIncrement,
            ThirdPowerFunction maxManaIncrement,
            ThirdPowerFunction maxStaminaIncrement,
            ThirdPowerFunction strengthIncrement,
            ThirdPowerFunction wisdomIncrement,
            ThirdPowerFunction toughnessIncrement,
            ThirdPowerFunction mentalResistanceIncrement,
            UsableEquipTypes usableTypes,
            std::vector<LevelingSkill> learnableSkills);

    virtual std::vector<LevelingSkill> getSkills();

    UsableEquipTypes           usableTypes; ///< Equipment types the hero can equip and use
    std::vector<LevelingSkill> learnableSkills; ///< All the skills the class can learn through the levels
};

/**
* \brief Member of monsters index
*/

struct MonsterClass : public EntityClass
{

    /**
    * \param[in] name Name of the class
    * \param[in] maxLifeIncrement Evolution followed by the index member's life
    * \param[in] maxManaIncrement Evolution followed by the index member's mana
    * \param[in] maxStaminaIncrement Evolution followed by the index member's stamina
    * \param[in] strengthIncrement Evolution followed by the index member's strength
    * \param[in] wisdomIncrement Evolution followed by the index member's wisdom
    * \param[in] toughnessIncrement Evolution followed by the index member's toughness
    * \param[in] mentalResistanceIncrement Evolution followed by the index member's mental resistance
    * \param[in] skills All the skills the monster has
    * \param[in] effects Basic attacks' informations
    */

    MonsterClass(std::string name,
            ThirdPowerFunction maxLifeIncrement,
            ThirdPowerFunction maxManaIncrement,
            ThirdPowerFunction maxStaminaIncrement,
            ThirdPowerFunction strengthIncrement,
            ThirdPowerFunction wisdomIncrement,
            ThirdPowerFunction toughnessIncrement,
            ThirdPowerFunction mentalResistanceIncrement,
            std::vector<Skill *> skills,
            WeaponEffects effects);

    virtual std::vector<LevelingSkill> getSkills();

    WeaponEffects        effects; ///< Basic attacks' informations
    std::vector<Skill *> skills; ///< All the skills the monster has
};

#endif