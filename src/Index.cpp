#include "Index.hpp"

extern IndexesIndex indexes;

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