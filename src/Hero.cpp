#include "Hero.hpp"

Hero::Hero(const std::string &name, int experiencePoints, EntityClass *heroClass) :
		experiencePoints(experiencePoints),
		EntityModel(name, EXPERIENCE_TO_LEVEL.iresult(experiencePoints), heroClass),
		weapon(indexes.weaponIndex.searchByName("Default")),
		helmet(indexes.helmetIndex.searchByName("Default")),
		chestplate(indexes.chestplateIndex.searchByName("Default")),
		leggings(indexes.leggingsIndex.searchByName("Default")),
		boots(indexes.bootsIndex.searchByName("Default"))
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
	int newMaxLife(0), oldMaxLife(effects.life), newMaxMana(0), oldMaxMana(effects.mana), newMaxStamina(0), oldMaxStamina(
			effects.stamina);

	//Resets the effects
	effects = Effects();

	//Counts the 4 basic effects back from the base level
	effects.strength         = entityClass->strengthIncrement.iresult(level);
	effects.wisdom           = entityClass->wisdomIncrement.iresult(level);
	effects.toughness        = entityClass->toughnessIncrement.iresult(level);
	effects.mentalResistance = entityClass->mentalResistanceIncrement.iresult(level);

	//Adds the effects of the equipments
	effects += weapon->getEquipmentEffects();
	effects += helmet->getEquipmentEffects();
	effects += chestplate->getEquipmentEffects();
	effects += leggings->getEquipmentEffects();
	effects += boots->getEquipmentEffects();

	//Changes the max life
	newMaxLife = entityClass->maxLifeIncrement.iresult(level);
	newMaxLife += TOUGHNESS_TO_LIFE.result(effects.toughness);
	newMaxLife += MENTAL_RESISTANCE_TO_LIFE.result(effects.mentalResistance);
	effects.life += newMaxLife;
	life += effects.life - oldMaxLife;

	//Changes the max mana
	newMaxMana = entityClass->maxManaIncrement.iresult(level);
	newMaxMana += WISDOM_TO_MANA.result(effects.wisdom);
	effects.mana += newMaxMana;
	mana += effects.mana - oldMaxMana;

	//Changes the max stamina
	newMaxStamina = entityClass->maxStaminaIncrement.iresult(level);
	newMaxStamina += STRENGTH_TO_STAMINA.result(effects.strength);
	effects.stamina += newMaxStamina;
	stamina += effects.stamina - oldMaxStamina;
}

void Hero::changeEquipment(EquipmentType type, Equipment *newEquipment = NULL)
{
	//Resets the equipment if set to NULL
	if (newEquipment == NULL)
	{
		switch (type)
		{
			case HELMET:
				newEquipment = indexes.helmetIndex.searchByName("Default");
				break;

			case CHESTPLATE:
				newEquipment = indexes.chestplateIndex.searchByName("Default");
				break;

			case LEGGINGS:
				newEquipment = indexes.leggingsIndex.searchByName("Default");
				break;

			case BOOTS:
				newEquipment = indexes.bootsIndex.searchByName("Default");
				break;

			case WEAPON:
				newEquipment = indexes.weaponIndex.searchByName("Default");
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