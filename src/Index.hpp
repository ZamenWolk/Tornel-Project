#ifndef INDEX_HPP_INCLUDED
#define INDEX_HPP_INCLUDED

#include <string>
#include <SFML/Window.hpp>
#include <vector>
#include <Thor/Input.hpp>

#include "Skill.hpp"
#include "Equipement.hpp"
#include "mathfuncs.hpp"

   /**
    *   \file Index.hpp
    *   \brief Contains all the classes and structures to form indexes
    */

/**
* \addtogroup both
* @{
*/

   /**
	*	\brief Member of characters index
	*/

struct IndexMember
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
	*	\param[in] learnableSkills All the skills the class can learn
	*/

	IndexMember(	std::string name,
					ThirdPowerFunction maxLifeIncrement,
					ThirdPowerFunction maxManaIncrement,
					ThirdPowerFunction maxStaminaIncrement,
					ThirdPowerFunction strengthIncrement,
					ThirdPowerFunction wisdomIncrement,
					ThirdPowerFunction toughnessIncrement,
					ThirdPowerFunction mentalResistanceIncrement,
					std::vector<LevelingSkill> learnableSkills):
						name(name),
						maxLifeIncrement(maxLifeIncrement),
						maxManaIncrement(maxManaIncrement),
						maxStaminaIncrement(maxStaminaIncrement),
						strengthIncrement(strengthIncrement),
						wisdomIncrement(wisdomIncrement),
						toughnessIncrement(toughnessIncrement),
						mentalResistanceIncrement(mentalResistanceIncrement),
						learnableSkills(learnableSkills)
	{

	}

    /// \return name of the member
    std::string getName() const
    {
    	return name;
    }

    std::string 				name; ///< Name of the class
    ThirdPowerFunction 			maxLifeIncrement, ///< Evolution followed by the index member's life
								maxManaIncrement, ///< Evolution followed by the index member's mana
								maxStaminaIncrement, ///< Evolution followed by the index member's stamina
								strengthIncrement, ///< Evolution followed by the index member's strength
								wisdomIncrement, ///< Evolution followed by the index member's wisdom
								toughnessIncrement, ///< Evolution followed by the index member's toughness
								mentalResistanceIncrement; ///< Evolution followed by the index member's mental resistance
    std::vector<LevelingSkill> learnableSkills; ///< All the skills the class can learn through the levels
};

   /**
	*	\brief Member of monsters index
	*/

struct MonsterMember : public IndexMember
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
	*	\param[in] learnableSkills All the skills the class can learn
	*	\param[in] effects Basic attacks' informations
	*/

	MonsterMember(	std::string name,
					ThirdPowerFunction maxLifeIncrement,
					ThirdPowerFunction maxManaIncrement,
					ThirdPowerFunction maxStaminaIncrement,
					ThirdPowerFunction strengthIncrement,
					ThirdPowerFunction wisdomIncrement,
					ThirdPowerFunction toughnessIncrement,
					ThirdPowerFunction mentalResistanceIncrement,
					std::vector<LevelingSkill> learnableSkills,
					WeaponEffects effects):

						IndexMember(name,
									maxLifeIncrement,
									maxManaIncrement,
									maxStaminaIncrement,
									strengthIncrement,
									wisdomIncrement,
									toughnessIncrement,
									mentalResistanceIncrement,
									learnableSkills),
						effects(effects)
	{

	}

	WeaponEffects effects; ///< Basic attacks' informations
};

   /**
    *   \brief Contains the characteristics of a certain kind of thing in the game
    */

template<class T> class Index
{

public:

    /// \param[in] identifier Name of the index for use in the error reports
	Index(std::string identifier):
		index(),
		identifier(identifier)
	{

	}

   /**
    * 	\brief Checks if the name searched for exists in the index
    * 	\param[in] searchName Name to check
    * 	\return true if the name exists
    */

    T* searchByName(std::string searchName)
    {
		for (typename std::vector<T>::iterator it= index.begin(); it != index.end(); it++)
		{
			if (it->name() == searchName)
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
		for (typename std::vector<T>::iterator it= index.begin(); it != index.end(); it++)
		{
			if (it->name() == searchEntry)
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

    bool addEntry(T entryToAdd)
    {
		if (!doesEntryExist(entryToAdd.name()))
		{
			index.push_back(entryToAdd);
		}

		return true;
	}

protected:

    std::vector<T> 		index; ///< Index of all the entries
    const std::string identifier; ///< Name of the index
};

   /**
    *   \brief Index class with more functions, most notably handling types (i.e. for weapons)
    */

template<class T> class EquipementIndex : public Index<T>
{

public:

    /// \param[in] identifier Name of the index for use in the error reports
	EquipementIndex(std::string identifier):
				Index<T>(identifier),
				typeIndex()
	{

	}

   /**
	*	\param[in] searchType name of the type to search for
	*	\return true if the type given exists in the index
	*/

	bool doesTypeExist(std::string searchType)
	{
		for (std::vector<std::string>::iterator it= typeIndex.begin(); it != typeIndex.end(); it++)
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


protected:

	std::vector<std::string> typeIndex; ///< Index of all the types of entries
};

   /**
    * \brief Class grouping all the indexes of the game with all the data of equipements, classes and skills
    */

struct IndexesIndex
{
    IndexesIndex():
                heroClassIndex("Hero classes"),
                monsterIndex("Monsters"),
                skillIndex("Skill"),
                weaponIndex("Weapon"),
                helmetIndex("Helmet"),
                chestplateIndex("Chestplate"),
                leggingsIndex("Leggings"),
                bootsIndex("Boots")

    {
		heroClassInit();
		monsterInit();
		spellInit();
		abilityInit();
		weaponInit();
		helmetInit();
		chestplateInit();
		leggingsInit();
		bootsInit();
    }

    Index<IndexMember> 			    heroClassIndex; ///< Index of hero classes

    Index<MonsterMember>		    monsterIndex; ///< Index of monsters

    Index<Skill>                    skillIndex; ///< Index of skills

    EquipementIndex<Weapon>		    weaponIndex; ///< Index of weapons

    EquipementIndex<Equipement>		helmetIndex, ///< Index of helmets
                                    chestplateIndex, ///< Index of chestplates
									leggingsIndex, ///< Index of leggings
									bootsIndex; ///< Index of boots

    thor::ActionMap<std::string>	keyboardMap; ///< Map of all the controls in-game

private:
   /**
   	* \brief Initializer of the index of hero classes
   	*/
	void heroClassInit()
	{
		heroClassIndex.addEntry(IndexMember("default",
											ThirdPowerFunction(1),
											ThirdPowerFunction(1),
											ThirdPowerFunction(1),
											ThirdPowerFunction(1),
											ThirdPowerFunction(1),
											ThirdPowerFunction(1),
											ThirdPowerFunction(1),
											std::vector<LevelingSkill>(0)));
		heroClassIndex.addEntry(IndexMember("Arcanist",
											ThirdPowerFunction(22.6f, 2.47f, -0.007f),
											ThirdPowerFunction(22.6f, 2.47f, -0.007f),
											ThirdPowerFunction(7.3f, 0.66f, -0.0024f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											std::vector<LevelingSkill>(0)));
		heroClassIndex.addEntry(IndexMember("Arnegon",
											ThirdPowerFunction(22.6f, 2.47f, -0.007f),
											ThirdPowerFunction(22.6f, 2.47f, -0.007f),
											ThirdPowerFunction(7.3f, 0.66f, -0.0024f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											std::vector<LevelingSkill>(0)));
		heroClassIndex.addEntry(IndexMember("Barrkian",
											ThirdPowerFunction(22.6f, 2.47f, -0.007f),
											ThirdPowerFunction(22.6f, 2.47f, -0.007f),
											ThirdPowerFunction(7.3f, 0.66f, -0.0024f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											std::vector<LevelingSkill>(0)));
		heroClassIndex.addEntry(IndexMember("Knight",
											ThirdPowerFunction(22.6f, 2.47f, -0.007f),
											ThirdPowerFunction(5.8302f, 0.1689f, 0.000844531f),
											ThirdPowerFunction(7.3f, 0.66f, -0.0024f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											std::vector<LevelingSkill>(0)));
		heroClassIndex.addEntry(IndexMember("White mage",
											ThirdPowerFunction(22.6f, 2.47f, -0.007f),
											ThirdPowerFunction(22.6f, 2.47f, -0.007f),
											ThirdPowerFunction(7.3f, 0.66f, -0.0024f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											std::vector<LevelingSkill>(0)));
		heroClassIndex.addEntry(IndexMember("Black mage",
											ThirdPowerFunction(22.6f, 2.47f, -0.007f),
											ThirdPowerFunction(22.6f, 2.47f, -0.007f),
											ThirdPowerFunction(7.3f, 0.66f, -0.0024f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											std::vector<LevelingSkill>(0)));
		heroClassIndex.addEntry(IndexMember("Shalian",
											ThirdPowerFunction(22.6f, 2.47f, -0.007f),
											ThirdPowerFunction(22.6f, 2.47f, -0.007f),
											ThirdPowerFunction(7.3f, 0.66f, -0.0024f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											std::vector<LevelingSkill>(0)));
		heroClassIndex.addEntry(IndexMember("Assassin",
											ThirdPowerFunction(22.6f, 2.47f, -0.007f),
											ThirdPowerFunction(22.6f, 2.47f, -0.007f),
											ThirdPowerFunction(7.3f, 0.66f, -0.0024f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											ThirdPowerFunction(7.7f, 2.3f, -0.007f),
											std::vector<LevelingSkill>(0)));
	}

	/**
	* \brief Initializer of the index of monsters
	*/
	void monsterInit()
	{
		monsterIndex.addEntry(MonsterMember("Slime",
											ThirdPowerFunction(10, 10),
											ThirdPowerFunction(10, 10),
											ThirdPowerFunction(2.5, 2.5),
											ThirdPowerFunction(3, 2),
											ThirdPowerFunction(3, 2),
											ThirdPowerFunction(3, 2),
											ThirdPowerFunction(3, 2),
											std::vector<LevelingSkill>(0),
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
		helmetIndex.addEntry(Equipement("Default", "Admin", Effects()));
	}

	/**
	* \brief Initializer of the index of chestplates
	*/
	void chestplateInit()
	{
		chestplateIndex.addType("Admin");
		chestplateIndex.addEntry(Equipement("Default", "Admin", Effects()));
	}

	/**
	* \brief Initializer of the index of leggings
	*/
	void leggingsInit()
	{
		leggingsIndex.addType("Admin");
		leggingsIndex.addEntry(Equipement("Default", "Admin", Effects()));
	}

	/**
	* \brief Initializer of the index of boots
	*/
	void bootsInit()
	{
		bootsIndex.addType("Admin");
		bootsIndex.addEntry(Equipement("Default", "Admin", Effects()));
	}

	/**
	* \brief Initializer of the different control maps
	*/
	void mapsInit()
	{
		keyboardMap["characterMenu"] = thor::Action(sf::Keyboard::A, thor::Action::PressOnce);
		keyboardMap["targetMenu"] = thor::Action(sf::Keyboard::Z, thor::Action::PressOnce);
		keyboardMap["abilityMenu"] = thor::Action(sf::Keyboard::E, thor::Action::PressOnce);
		keyboardMap["spellMenu"] = thor::Action(sf::Keyboard::R, thor::Action::PressOnce);
		keyboardMap["weaponAttack"] = thor::Action(sf::Keyboard::D, thor::Action::PressOnce);
		keyboardMap["mainMenu"] = thor::Action(sf::Keyboard::Numpad8, thor::Action::PressOnce);
		keyboardMap["precPage"] = thor::Action(sf::Keyboard::Numpad7, thor::Action::PressOnce);
		keyboardMap["nextPage"] = thor::Action(sf::Keyboard::Numpad9, thor::Action::PressOnce);
		keyboardMap["selector1"] = thor::Action(sf::Keyboard::Numpad4, thor::Action::PressOnce);
		keyboardMap["selector2"] = thor::Action(sf::Keyboard::Numpad5, thor::Action::PressOnce);
		keyboardMap["selector3"] = thor::Action(sf::Keyboard::Numpad6, thor::Action::PressOnce);
		keyboardMap["selector4"] = thor::Action(sf::Keyboard::Numpad1, thor::Action::PressOnce);
		keyboardMap["selector5"] = thor::Action(sf::Keyboard::Numpad2, thor::Action::PressOnce);
		keyboardMap["selector6"] = thor::Action(sf::Keyboard::Numpad3, thor::Action::PressOnce);
		keyboardMap["charSelector"] = keyboardMap["selector1"] || keyboardMap["selector2"] || keyboardMap["selector3"] || keyboardMap["selector4"] || keyboardMap["selector5"];
		keyboardMap["selector"] = keyboardMap["selector6"] || keyboardMap["charSelector"];
	}

};

/// @}

#endif // INDEX_HPP_INCLUDED
