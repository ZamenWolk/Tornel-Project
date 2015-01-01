#ifndef CLASSES_EQUIPMENT_EQUIPMENT
#define CLASSES_EQUIPMENT_EQUIPMENT

#include <string>
#include <SFML/System.hpp>

#include "Effects.hpp"

class Equipment
{
public:

    Equipment(std::string name, std::string type, Effects effects, int prerequisiteLevel = 0, Effects prerequisites = Effects(0, 0, 0, 0, 0, 0, 0));

    Equipment(const Equipment *equipment);

    std::string getName() const;

    std::string getType() const;

    Effects getEquipmentEffects() const;

    Effects getPrerequisites() const;

    int getPrerequisiteLevel() const;

protected:

    std::string name,
            type;

    Effects equipmentEffects,
            prerequisites;

    int prerequisiteLevel;

};

class Weapon : public Equipment
{
public:

    Weapon(const std::string &name, std::string type, const Effects &equipmentEffects, const WeaponEffects &weaponEffects);

    Weapon(const Weapon *weapon);

    WeaponEffects getWeaponEffects() const;

protected:

    WeaponEffects weaponEffects;

};

#endif