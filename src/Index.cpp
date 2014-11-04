#include "IndexesIndex.hpp"

extern IndexesIndex indexes;

EntityClass::EntityClass(std::string name,
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

std::string EntityClass::getName() const
{
	return name;
}

bool UsableEquipTypes::addUsableType(std::string &typeName, EquipmentType equipmentType)
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

	if(!isAdded)
	{
		errorReport("The type " + typeName + " doesn't exist in the selected index");
	}

	return isAdded;
}

UsableEquipTypes::UsableEquipTypes(std::vector<std::string> helmetTypes,
								   std::vector<std::string> chestTypes,
								   std::vector<std::string> leggingsTypes,
								   std::vector<std::string> bootsTypes,
								   std::vector<std::string> weaponTypes)
{
	for(std::vector<std::string>::iterator it = helmetTypes.begin(); it != helmetTypes.end(); it++)
	{
		addUsableType(*it, HELMET);
	}

	for(std::vector<std::string>::iterator it = chestTypes.begin(); it != chestTypes.end(); it++)
	{
		addUsableType(*it, CHESTPLATE);
	}

	for(std::vector<std::string>::iterator it = leggingsTypes.begin(); it != leggingsTypes.end(); it++)
	{
		addUsableType(*it, LEGGINGS);
	}

	for(std::vector<std::string>::iterator it = bootsTypes.begin(); it != bootsTypes.end(); it++)
	{
		addUsableType(*it, BOOTS);
	}

	for(std::vector<std::string>::iterator it = weaponTypes.begin(); it != weaponTypes.end(); it++)
	{
		addUsableType(*it, WEAPON);
	}
}

HeroClass::HeroClass(std::string name,
					 ThirdPowerFunction maxLifeIncrement,
				   	 ThirdPowerFunction maxManaIncrement,
					 ThirdPowerFunction maxStaminaIncrement,
				   	 ThirdPowerFunction strengthIncrement,
				   	 ThirdPowerFunction wisdomIncrement,
				   	 ThirdPowerFunction toughnessIncrement,
				   	 ThirdPowerFunction mentalResistanceIncrement,
				   	 UsableEquipTypes usableTypes,
				   	 std::vector<LevelingSkill> learnableSkills):
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

std::vector<LevelingSkill> HeroClass::getSkills()
{
	return learnableSkills;
}

MonsterClass::MonsterClass(std::string name,
						   ThirdPowerFunction maxLifeIncrement,
						   ThirdPowerFunction maxManaIncrement,
						   ThirdPowerFunction maxStaminaIncrement,
						   ThirdPowerFunction strengthIncrement,
						   ThirdPowerFunction wisdomIncrement,
						   ThirdPowerFunction toughnessIncrement,
						   ThirdPowerFunction mentalResistanceIncrement,
						   std::vector<Skill *> skills,
						   WeaponEffects effects):
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

std::vector<LevelingSkill> MonsterClass::getSkills()
{
	std::vector<LevelingSkill> leveledSkills;
	for (std::vector<Skill *>::iterator it = skills.begin(); it != skills.end(); it++)
	{
		leveledSkills.push_back(LevelingSkill(*it));
	}
	return leveledSkills;
}