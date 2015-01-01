#ifndef CLASSES_INDEX_INDEXCLASSES
#define CLASSES_INDEX_INDEXCLASSES

#include <string>
#include <vector>

#include "../Skills/Skill.hpp"
#include "../Equipment/Effects.hpp"
#include "../../Enums/Equipment.hpp"
#include "../Math/math.hpp"

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

    bool addUsableType(std::string &typeName, EquipmentType equipmentType);

    UsableEquipTypes(std::vector<std::string> helmetTypes,
            std::vector<std::string> chestTypes,
            std::vector<std::string> leggingsTypes,
            std::vector<std::string> bootsTypes,
            std::vector<std::string> weaponTypes);

protected:
    std::vector<std::string> usableHelmetTypes,
            usableChestTypes,
            usableLeggingsTypes,
            usableBootsTypes,
            usableWeaponTypes;
};

struct EntityClass
{

    EntityClass(std::string name,
            ThirdPowerFunction maxLifeIncrement,
            ThirdPowerFunction maxManaIncrement,
            ThirdPowerFunction maxStaminaIncrement,
            ThirdPowerFunction strengthIncrement,
            ThirdPowerFunction wisdomIncrement,
            ThirdPowerFunction toughnessIncrement,
            ThirdPowerFunction mentalResistanceIncrement);

    std::string getName() const;

    virtual std::vector<LevelingSkill> getSkills() = 0;

    std::string        name;
    ThirdPowerFunction maxLifeIncrement,
            maxManaIncrement,
            maxStaminaIncrement,
            strengthIncrement,
            wisdomIncrement,
            toughnessIncrement,
            mentalResistanceIncrement;
};

struct HeroClass : public EntityClass
{

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

    UsableEquipTypes           usableTypes;
    std::vector<LevelingSkill> learnableSkills;
};

struct MonsterClass : public EntityClass
{

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

    WeaponEffects        effects;
    std::vector<Skill *> skills;
};

#endif