#include "IndexesIndex.hpp"

using namespace std;
using namespace sf;

extern IndexesIndex indexes;

EntityClass::EntityClass(string name,
                         ThirdPowerFunction maxLifeIncrement,
                         ThirdPowerFunction maxManaIncrement,
                         ThirdPowerFunction maxStaminaIncrement,
                         ThirdPowerFunction strengthIncrement,
                         ThirdPowerFunction wisdomIncrement,
                         ThirdPowerFunction toughnessIncrement,
                         ThirdPowerFunction mentalResistanceIncrement) :
		name(name),
		maxLifeIncrement(maxLifeIncrement),
		maxManaIncrement(maxManaIncrement),
		maxStaminaIncrement(maxStaminaIncrement),
		strengthIncrement(strengthIncrement),
		wisdomIncrement(wisdomIncrement),
		toughnessIncrement(toughnessIncrement),
		mentalResistanceIncrement(mentalResistanceIncrement)
{

}

string EntityClass::getName() const
{
	return name;
}

bool UsableEquipTypes::addUsableType(string &typeName, EquipmentType equipmentType)
{
	bool isAdded(false);
	switch (equipmentType)
	{
		case HELMET:
			if (indexes.helmetIndex.doesTypeExist(typeName))
			{
				usableHelmetTypes.push_back(typeName);
				isAdded = true;
			}
	        break;
		case CHESTPLATE:
			if (indexes.chestplateIndex.doesTypeExist(typeName))
			{
				usableChestTypes.push_back(typeName);
				isAdded = true;
			}
	        break;
		case LEGGINGS:
			if (indexes.leggingsIndex.doesTypeExist(typeName))
			{
				usableLeggingsTypes.push_back(typeName);
				isAdded = true;
			}
	        break;
		case BOOTS:
			if (indexes.bootsIndex.doesTypeExist(typeName))
			{
				usableBootsTypes.push_back(typeName);
				isAdded = true;
			}
	        break;
		case WEAPON:
			if (indexes.weaponIndex.doesTypeExist(typeName))
			{
				usableWeaponTypes.push_back(typeName);
				isAdded = true;
			}
	        break;
	}

	if (!isAdded)
	{
		errorReport("The type " + typeName + " doesn't exist in the selected index");
	}

	return isAdded;
}

UsableEquipTypes::UsableEquipTypes(vector<string> helmetTypes,
                                   vector<string> chestTypes,
                                   vector<string> leggingsTypes,
                                   vector<string> bootsTypes,
                                   vector<string> weaponTypes)
{
	for (vector<string>::iterator it = helmetTypes.begin(); it != helmetTypes.end(); it++)
	{
		addUsableType(*it, HELMET);
	}

	for (vector<string>::iterator it = chestTypes.begin(); it != chestTypes.end(); it++)
	{
		addUsableType(*it, CHESTPLATE);
	}

	for (vector<string>::iterator it = leggingsTypes.begin(); it != leggingsTypes.end(); it++)
	{
		addUsableType(*it, LEGGINGS);
	}

	for (vector<string>::iterator it = bootsTypes.begin(); it != bootsTypes.end(); it++)
	{
		addUsableType(*it, BOOTS);
	}

	for (vector<string>::iterator it = weaponTypes.begin(); it != weaponTypes.end(); it++)
	{
		addUsableType(*it, WEAPON);
	}
}

HeroClass::HeroClass(string name,
                     ThirdPowerFunction maxLifeIncrement,
                     ThirdPowerFunction maxManaIncrement,
                     ThirdPowerFunction maxStaminaIncrement,
                     ThirdPowerFunction strengthIncrement,
                     ThirdPowerFunction wisdomIncrement,
                     ThirdPowerFunction toughnessIncrement,
                     ThirdPowerFunction mentalResistanceIncrement,
                     UsableEquipTypes usableTypes,
                     vector<LevelingSkill> learnableSkills) :
		EntityClass(name,
		            maxLifeIncrement,
		            maxManaIncrement,
		            maxStaminaIncrement,
		            strengthIncrement,
		            wisdomIncrement,
		            toughnessIncrement,
		            mentalResistanceIncrement),
		learnableSkills(learnableSkills),
		usableTypes(usableTypes)
{

}

vector<LevelingSkill> HeroClass::getSkills()
{
	return learnableSkills;
}

MonsterClass::MonsterClass(string name,
                           ThirdPowerFunction maxLifeIncrement,
                           ThirdPowerFunction maxManaIncrement,
                           ThirdPowerFunction maxStaminaIncrement,
                           ThirdPowerFunction strengthIncrement,
                           ThirdPowerFunction wisdomIncrement,
                           ThirdPowerFunction toughnessIncrement,
                           ThirdPowerFunction mentalResistanceIncrement,
                           vector<Skill *> skills,
                           WeaponEffects effects) :
		EntityClass(name,
		            maxLifeIncrement,
		            maxManaIncrement,
		            maxStaminaIncrement,
		            strengthIncrement,
		            wisdomIncrement,
		            toughnessIncrement,
		            mentalResistanceIncrement),
		effects(effects),
		skills(skills)
{

}

vector<LevelingSkill> MonsterClass::getSkills()
{
	vector<LevelingSkill>          leveledSkills;
	for (vector<Skill *>::iterator it = skills.begin(); it != skills.end(); it++)
	{
		leveledSkills.push_back(LevelingSkill(*it));
	}
	return leveledSkills;
}