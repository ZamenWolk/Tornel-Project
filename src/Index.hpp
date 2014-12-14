#ifndef INDEX_HPP_INCLUDED
#define INDEX_HPP_INCLUDED

#include <string>
#include <SFML/Window.hpp>
#include <vector>
#include <Thor/Input.hpp>

#include "Skill.hpp"
#include "Equipment.hpp"
#include "mathfuncs.hpp"

/**
* \file Index.hpp
* \brief Contains all the classes and structures to form indexes
*/

/**
* \addtogroup both
* @{
*/

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

/**
* \brief Contains the characteristics of a certain kind of thing in the game
*/

template<class T>
class Index
{

public:

	/// \param[in] identifier Name of the index for use in the error reports
	Index(std::string identifier) :
			index(),
			identifier(identifier)
	{

	}

	/**
	* 	\brief Checks if the name searched for exists in the index
	* 	\param[in] searchName Name to check
	* 	\return true if the name exists
	*/

	T *searchByName(std::string searchName = "")
	{
		if (searchName == "")
		{
			return &index[0];
		}

		for (typename std::vector<T>::iterator it = index.begin(); it != index.end(); it++)
		{
			if (it->getName() == searchName)
			{
				return &*it;
			}
		}

		std::string errorMessage(searchName + " doesn't exist in the " + identifier + " index");

		errorReport(errorMessage);
		return &index[0];
	}

	/**
	* \param[in] searchEntry name of the name to search for
	* \return true if the entry given exists in the index
	*/

	bool doesEntryExist(std::string searchEntry)
	{
		for (typename std::vector<T>::iterator it = index.begin(); it != index.end(); it++)
		{
			if (it->getName() == searchEntry)
			{
				return true;
			}
		}

		return false;
	}

	/**
	* 	\brief Add an entry into the index
	* 	\param[in] entryToAdd Entry to add to the index
	* \return True if the entry is in the index after the function
	*/

	virtual bool addEntry(T entryToAdd)
	{
		if (!doesEntryExist(entryToAdd.getName()))
		{
			index.push_back(entryToAdd);
		}

		return true;
	}

	/// \return Identifier of the index
	std::string getIdentifier() const
	{
		return identifier;
	}

protected:

	std::vector<T>    index; ///< Index of all the entries
	const std::string identifier; ///< Name of the index
};

/**
* \brief Index class with more functions, most notably handling types (i.e. for weapons)
*/

template<class T>
class EquipmentIndex : public Index<T>
{

public:

	/// \param[in] identifier Name of the index for use in the error reports
	EquipmentIndex(std::string identifier) :
			Index<T>(identifier),
			typeIndex()
	{

	}

	/**
	* \param[in] searchType name of the type to search for
	* \return true if the type given exists in the index
	*/

	bool doesTypeExist(std::string searchType)
	{
		for (std::vector<std::string>::iterator it = typeIndex.begin(); it != typeIndex.end(); it++)
		{
			if (*it == searchType)
			{
				return true;
			}
		}

		return false;
	}

	/**
	* \brief Adds the type given in argument to the index
	* \param[in] typeToAdd type to add to the index
	* \return true if type exists in the index after the function
	*/

	bool addType(std::string typeToAdd)
	{
		if (!doesTypeExist(typeToAdd))
		{
			typeIndex.push_back(typeToAdd);
		}

		return true;
	}

	virtual bool addEntry(T entryToAdd)
	{
		if (!this->doesEntryExist(entryToAdd.getName()) && doesTypeExist(entryToAdd.getType()))
		{
			this->index.push_back(entryToAdd);
		}

		return true;
	}

protected:

	std::vector<std::string> typeIndex; ///< Index of all the types of entries
};

/// @}

#endif // INDEX_HPP_INCLUDED
