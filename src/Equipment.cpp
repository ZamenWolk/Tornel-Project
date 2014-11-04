#include "Equipment.hpp"

Effects::Effects():
		life(0), mana(0), stamina(0), strength(0), wisdom(0), toughness(0), mentalResistance(0)
{

}

Effects::Effects(const Effects &equipmentEffects):
		life(equipmentEffects.life),
		mana(equipmentEffects.mana),
		stamina(equipmentEffects.stamina),
		strength(equipmentEffects.strength),
		wisdom(equipmentEffects.wisdom),
		toughness(equipmentEffects.toughness),
		mentalResistance(equipmentEffects.mentalResistance)
{

}

Effects::Effects(int lifeGain,
				 int manaGain,
				 int staminaGain,
				 int strengthGain,
				 int wisdomGain,
				 int toughnessGain,
				 int mentalResistanceGain) :
		life(lifeGain),
		mana(manaGain),
		stamina(staminaGain),
		strength(strengthGain),
		wisdom(wisdomGain),
		toughness(toughnessGain),
		mentalResistance(mentalResistanceGain)
{

}

void Effects::operator+=(const Effects &a)
{
	life += a.life;
	mana += a.mana;
	stamina += a.stamina;
	strength += strength;
	wisdom += a.wisdom;
	toughness += a.toughness;
	mentalResistance += a.mentalResistance;
}

WeaponEffects::WeaponEffects():
		baseDamage(3), cooldownTime(sf::milliseconds(1500))
{

}

WeaponEffects::WeaponEffects(const WeaponEffects &weaponEffects):
		baseDamage(weaponEffects.baseDamage), cooldownTime(weaponEffects.cooldownTime)
{

}

WeaponEffects::WeaponEffects(int baseDamage, sf::Time cooldownTime):
		baseDamage(baseDamage), cooldownTime(cooldownTime)
{

}

CombatEffects::CombatEffects() :
		Effects(), WeaponEffects()
{

}

CombatEffects::CombatEffects(const Effects &equipmentEffects, const WeaponEffects &weaponEffects) :
		Effects(equipmentEffects), WeaponEffects(weaponEffects)
{

}

CombatEffects::CombatEffects(int lifeGain,
							 int manaGain,
							 int staminaGain,
							 int strengthGain,
							 int wisdomGain,
							 int toughnessGain,
							 int mentalResistanceGain,
							 int baseDamage,
							 sf::Time cooldownTime) :
		Effects(lifeGain, manaGain, staminaGain, strengthGain, wisdomGain, toughnessGain, mentalResistanceGain),
		WeaponEffects(baseDamage, cooldownTime)
{

}

Equipment::Equipment(std::string name, std::string type, Effects effects) :
		name(name), type(type), equipmentEffects(effects)
{

}

Equipment::Equipment(const Equipment *equipment) :
		name(equipment->name), equipmentEffects(equipment->equipmentEffects)
{

}

std::string Equipment::getName() const
{
	return name;
}

std::string Equipment::getType() const
{
	return type;
}

Effects Equipment::getEquipmentEffects() const
{
	return equipmentEffects;
}

Weapon::Weapon(const std::string &name,
			   std::string type,
			   const Effects &equipementEffects,
			   const WeaponEffects &weaponEffects) :
		Equipment(name, type, equipementEffects), weaponEffects(weaponEffects)
{

}

Weapon::Weapon(const Weapon *weapon) :
		Equipment(weapon->name, weapon->type, weapon->equipmentEffects), weaponEffects(weapon->weaponEffects)
{

}

WeaponEffects Weapon::getWeaponEffects() const
{
	return weaponEffects;
}