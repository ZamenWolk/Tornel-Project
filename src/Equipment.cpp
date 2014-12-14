#include "Equipment.hpp"

using namespace std;
using namespace sf;

Equipment::Equipment(string name, string type, Effects effects, int prerequisiteLevel, Effects prerequisites) :
		name(name),
		type(type),
		equipmentEffects(effects),
		prerequisites(prerequisites),
		prerequisiteLevel(prerequisiteLevel)
{

}

Equipment::Equipment(const Equipment *equipment) :
		name(equipment->name),
		type(equipment->type),
		equipmentEffects(equipment->equipmentEffects),
		prerequisites(equipment->prerequisites),
		prerequisiteLevel(equipment->prerequisiteLevel)
{

}

string Equipment::getName() const
{
	return name;
}

string Equipment::getType() const
{
	return type;
}

Effects Equipment::getEquipmentEffects() const
{
	return equipmentEffects;
}

Effects Equipment::getPrerequisites() const
{
	return prerequisites;
}

int Equipment::getPrerequisiteLevel() const
{
	return prerequisiteLevel;
}

Weapon::Weapon(const string &name, string type, const Effects &equipmentEffects, const WeaponEffects &weaponEffects) :
		Equipment(name, type, equipmentEffects),
		weaponEffects(weaponEffects)
{

}

Weapon::Weapon(const Weapon *weapon) :
		Equipment(weapon->name, weapon->type, weapon->equipmentEffects),
		weaponEffects(weapon->weaponEffects)
{

}

WeaponEffects Weapon::getWeaponEffects() const
{
	return weaponEffects;
}
