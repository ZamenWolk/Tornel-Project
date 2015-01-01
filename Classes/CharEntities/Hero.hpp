#ifndef CLASSES_CHARENTITIES_HERO_HPP
#define CLASSES_CHARENTITIES_HERO_HPP

#include "AIEntity.hpp"
#include "../Equipment/Equipment.hpp"
#include "../../Enums/Equipment.hpp"

class Hero : public EntityModel
{
public:

    Hero(const std::string &name, int experiencePoints, EntityClass *heroClass);

    void gainXP(unsigned int xpGained);

    int getExperiencePoints() const;

    virtual WeaponEffects basicAttackEffects() const;

    virtual void actualizeCharacteristics();

    void changeEquipment(EquipmentType type, Equipment *newEquipment = NULL);

    void actualizeLevel();

protected:

    int       experiencePoints;
    Weapon    *weapon;
    Equipment *helmet,
            *chestplate,
            *leggings,
            *boots;
};