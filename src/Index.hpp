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
*   \file Index.hpp
*   \brief Contains all the classes and structures to form indexes
*/

/**
* \brief Class storing types of equipment for each piece of equipment
*/

class UsableEquipTypes
{
public:
	UsableEquipTypes():
			usableHelmetTypes(1, "Admin"),
			usableChestTypes(1, "Admin"),
			usableLeggingsTypes(1, "Admin"),
			usableBootsTypes(1, "Admin"),
			usableWeaponTypes(1, "Admin")
	{

	}

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

	/**
	* \brief Adds a type to one of the vectors
	* \param[in] typeName name of the type to add
	* \param[in] equipmentType vector to add the entry to
	* \return true if the type was added to the corresponding index
	* \warning The type must be registered in the corresponding index to be added here
	*/

	bool addUsableType(std::string &typeName, EquipmentType equipmentType);

protected:
	std::vector<std::string>	usableHelmetTypes, ///< Types of helmet
								usableChestTypes, ///< Types of chestplate
								usableLeggingsTypes, ///< Types of leggings
								usableBootsTypes, ///< Types of boots
								usableWeaponTypes; ///< Types of weapon
};

/**
* \addtogroup both
* @{
*/

/**
*	\brief Member of characters index
*/

struct EntityClass
{

	/**
	*	\param[in] name Name of the class
	*	\param[in] maxLifeIncrement Evolution followed by the index member's life
	*	\param[in] maxManaIncrement Evolution followed by the index member's mana
	*	\param[in] maxStaminaIncrement Evolution followed by the index member's stamina
	*	\param[in] strengthIncrement Evolution followed by the index member's strength
	*	\param[in] wisdomIncrement Evolution followed by the index member's wisdom
	*	\param[in] toughnessIncrement Evolution followed by the index member's toughness
	*	\param[in] mentalResistanceIncrement Evolution followed by the index member's mental resistance
	*/

	EntityClass(std::string name,
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

	/// \return name of the member
	std::string getName() const
	{
		return name;
	}

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
* \brief Class of a hero
*/

struct HeroClass : public EntityClass
{

	/**
	*	\param[in] name Name of the class
	*	\param[in] maxLifeIncrement Evolution followed by the index member's life
	*	\param[in] maxManaIncrement Evolution followed by the index member's mana
	*	\param[in] maxStaminaIncrement Evolution followed by the index member's stamina
	*	\param[in] strengthIncrement Evolution followed by the index member's strength
	*	\param[in] wisdomIncrement Evolution followed by the index member's wisdom
	*	\param[in] toughnessIncrement Evolution followed by the index member's toughness
	*	\param[in] mentalResistanceIncrement Evolution followed by the index member's mental resistance
	*	\param[in] usableTypes Equipment types the hero can equip and use
	*	\param[in] learnableSkills All the skills the hero can learn throughout the levels
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

	virtual std::vector<LevelingSkill> getSkills()
	{
		return learnableSkills;
	}

	UsableEquipTypes		   usableTypes; ///< Equipment types the hero can equip and use
	std::vector<LevelingSkill> learnableSkills; ///< All the skills the class can learn through the levels
};

/**
*	\brief Member of monsters index
*/

struct MonsterClass : public EntityClass
{

	/**
	*	\param[in] name Name of the class
	*	\param[in] maxLifeIncrement Evolution followed by the index member's life
	*	\param[in] maxManaIncrement Evolution followed by the index member's mana
	*	\param[in] maxStaminaIncrement Evolution followed by the index member's stamina
	*	\param[in] strengthIncrement Evolution followed by the index member's strength
	*	\param[in] wisdomIncrement Evolution followed by the index member's wisdom
	*	\param[in] toughnessIncrement Evolution followed by the index member's toughness
	*	\param[in] mentalResistanceIncrement Evolution followed by the index member's mental resistance
	*	\param[in] skills All the skills the monster has
	*	\param[in] effects Basic attacks' informations
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

	virtual std::vector<LevelingSkill> getSkills()
	{
		std::vector<LevelingSkill> leveledSkills;
		for (std::vector<Skill *>::iterator it = skills.begin(); it != skills.end(); it++)
		{
			leveledSkills.push_back(LevelingSkill(*it));
		}
		return leveledSkills;
	}

	WeaponEffects effects; ///< Basic attacks' informations
	std::vector<Skill *> skills; ///< All the skills the monster has
};

/**
*   \brief Contains the characteristics of a certain kind of thing in the game
*/

template<class T>
class Index
{

public:

	/// \param[in] identifier Name of the index for use in the error reports
	Index(std::string identifier) :
			index(), identifier(identifier)
	{

	}

	/**
	* 	\brief Checks if the name searched for exists in the index
	* 	\param[in] searchName Name to check
	* 	\return true if the name exists
	*/

	T *searchByName(std::string searchName)
	{
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
	*	\param[in] searchEntry name of the name to search for
	*	\return true if the entry given exists in the index
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
	*	\return True if the entry is in the index after the function
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
*   \brief Index class with more functions, most notably handling types (i.e. for weapons)
*/

template<class T>
class EquipmentIndex : public Index<T>
{

public:

	/// \param[in] identifier Name of the index for use in the error reports
	EquipmentIndex(std::string identifier) :
			Index<T>(identifier), typeIndex()
	{

	}

	/**
	*	\param[in] searchType name of the type to search for
	*	\return true if the type given exists in the index
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
	*	\brief Adds the type given in argument to the index
	*	\param[in] typeToAdd type to add to the index
	*	\return true if type exists in the index after the function
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

/**
* \brief Class grouping all the indexes of the game with all the data of equipements, classes and skills
*/

struct IndexesIndex
{
	IndexesIndex() :
			heroClassIndex("Hero classes"),
			monsterIndex("Monsters"),
			skillIndex("Skill"),
			weaponIndex("Weapon"),
			helmetIndex("Helmet"),
			chestplateIndex("Chestplate"),
			leggingsIndex("Leggings"),
			bootsIndex("Boots")
	{
		helmetInit();
		chestplateInit();
		leggingsInit();
		bootsInit();
		weaponInit();
		spellInit();
		abilityInit();
		heroClassInit();
		monsterInit();
	}

	Index<HeroClass> heroClassIndex; ///< Index of hero classes

	Index<MonsterClass> monsterIndex; ///< Index of monsters

	Index<Skill> skillIndex; ///< Index of skills

	EquipmentIndex<Weapon> weaponIndex; ///< Index of weapons

	EquipmentIndex<Equipment> helmetIndex, ///< Index of helmets
								chestplateIndex, ///< Index of chestplates
								leggingsIndex, ///< Index of leggings
								bootsIndex; ///< Index of boots

	thor::ActionMap<std::string> keyboardMap; ///< Map of all the controls in-game

private:
	/**
	* \brief Initializer of the index of hero classes
	*/
	void heroClassInit()
	{
		heroClassIndex.addEntry(HeroClass("default",
										  ThirdPowerFunction(1),
										  ThirdPowerFunction(1),
										  ThirdPowerFunction(1),
										  ThirdPowerFunction(1),
										  ThirdPowerFunction(1),
										  ThirdPowerFunction(1),
										  ThirdPowerFunction(1),
										  UsableEquipTypes(),
										  std::vector<LevelingSkill>()));
		heroClassIndex.addEntry(HeroClass("Arcanist",
										  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
										  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
										  ThirdPowerFunction(7.3f, 0.66f, -0.0024f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  UsableEquipTypes(),
										  std::vector<LevelingSkill>()));
		heroClassIndex.addEntry(HeroClass("Arnegon",
										  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
										  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
										  ThirdPowerFunction(7.3f, 0.66f, -0.0024f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  UsableEquipTypes(),
										  std::vector<LevelingSkill>()));
		heroClassIndex.addEntry(HeroClass("Barrkian",
										  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
										  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
										  ThirdPowerFunction(7.3f, 0.66f, -0.0024f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  UsableEquipTypes(),
										  std::vector<LevelingSkill>()));
		heroClassIndex.addEntry(HeroClass("Knight",
										  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
										  ThirdPowerFunction(5.8302f, 0.1689f, 0.000844531f),
										  ThirdPowerFunction(7.3f, 0.66f, -0.0024f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  UsableEquipTypes(),
										  std::vector<LevelingSkill>()));
		heroClassIndex.addEntry(HeroClass("White mage",
										  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
										  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
										  ThirdPowerFunction(7.3f, 0.66f, -0.0024f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  UsableEquipTypes(),
										  std::vector<LevelingSkill>()));
		heroClassIndex.addEntry(HeroClass("Black mage",
										  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
										  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
										  ThirdPowerFunction(7.3f, 0.66f, -0.0024f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  UsableEquipTypes(),
										  std::vector<LevelingSkill>()));
		heroClassIndex.addEntry(HeroClass("Shalian",
										  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
										  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
										  ThirdPowerFunction(7.3f, 0.66f, -0.0024f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  UsableEquipTypes(),
										  std::vector<LevelingSkill>()));
		heroClassIndex.addEntry(HeroClass("Assassin",
										  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
										  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
										  ThirdPowerFunction(7.3f, 0.66f, -0.0024f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
										  UsableEquipTypes(),
										  std::vector<LevelingSkill>()));
	}

	/**
	* \brief Initializer of the index of monsters
	*/
	void monsterInit()
	{
		monsterIndex.addEntry(MonsterClass("Slime",
										   ThirdPowerFunction(10, 10),
										   ThirdPowerFunction(10, 10),
										   ThirdPowerFunction(2.5, 2.5),
										   ThirdPowerFunction(3, 2),
										   ThirdPowerFunction(3, 2),
										   ThirdPowerFunction(3, 2),
										   ThirdPowerFunction(3, 2),
										   std::vector<Skill *>(0),
										   WeaponEffects(3, sf::milliseconds(1500))));
	}

	/**
	* \brief Initializer of the index of spells
	*/
	void spellInit()
	{

	}

	/**
	* \brief Initializer of the index of abilities
	*/
	void abilityInit()
	{

	}

	/**
	* \brief Initializer of the index of weapons
	*/
	void weaponInit()
	{
		weaponIndex.addType("Admin");
		weaponIndex.addEntry(Weapon("Default", "Admin", Effects(), WeaponEffects()));
	}

	/**
	* \brief Initializer of the index of helmets
	*/
	void helmetInit()
	{
		helmetIndex.addType("Admin");
		helmetIndex.addEntry(Equipment("Default", "Admin", Effects()));
	}

	/**
	* \brief Initializer of the index of chestplates
	*/
	void chestplateInit()
	{
		chestplateIndex.addType("Admin");
		chestplateIndex.addEntry(Equipment("Default", "Admin", Effects()));
	}

	/**
	* \brief Initializer of the index of leggings
	*/
	void leggingsInit()
	{
		leggingsIndex.addType("Admin");
		leggingsIndex.addEntry(Equipment("Default", "Admin", Effects()));
	}

	/**
	* \brief Initializer of the index of boots
	*/
	void bootsInit()
	{
		bootsIndex.addType("Admin");
		bootsIndex.addEntry(Equipment("Default", "Admin", Effects()));
	}

	/**
	* \brief Initializer of the different control maps
	*/
	void mapsInit()
	{
		keyboardMap["characterMenu"] = thor::Action(sf::Keyboard::A, thor::Action::PressOnce);
		keyboardMap["targetMenu"]    = thor::Action(sf::Keyboard::Z, thor::Action::PressOnce);
		keyboardMap["abilityMenu"]   = thor::Action(sf::Keyboard::E, thor::Action::PressOnce);
		keyboardMap["spellMenu"]     = thor::Action(sf::Keyboard::R, thor::Action::PressOnce);
		keyboardMap["weaponAttack"]  = thor::Action(sf::Keyboard::D, thor::Action::PressOnce);
		keyboardMap["mainMenu"]      = thor::Action(sf::Keyboard::Numpad8, thor::Action::PressOnce);
		keyboardMap["precPage"]      = thor::Action(sf::Keyboard::Numpad7, thor::Action::PressOnce);
		keyboardMap["nextPage"]      = thor::Action(sf::Keyboard::Numpad9, thor::Action::PressOnce);
		keyboardMap["selector1"]     = thor::Action(sf::Keyboard::Numpad4, thor::Action::PressOnce);
		keyboardMap["selector2"]     = thor::Action(sf::Keyboard::Numpad5, thor::Action::PressOnce);
		keyboardMap["selector3"]     = thor::Action(sf::Keyboard::Numpad6, thor::Action::PressOnce);
		keyboardMap["selector4"]     = thor::Action(sf::Keyboard::Numpad1, thor::Action::PressOnce);
		keyboardMap["selector5"]     = thor::Action(sf::Keyboard::Numpad2, thor::Action::PressOnce);
		keyboardMap["selector6"]     = thor::Action(sf::Keyboard::Numpad3, thor::Action::PressOnce);
		keyboardMap["charSelector"]  = keyboardMap["selector1"] || keyboardMap["selector2"] || keyboardMap["selector3"] || keyboardMap["selector4"] || keyboardMap["selector5"];
		keyboardMap["selector"]      = keyboardMap["selector6"] || keyboardMap["charSelector"];
	}

};

/// @}

#endif // INDEX_HPP_INCLUDED
