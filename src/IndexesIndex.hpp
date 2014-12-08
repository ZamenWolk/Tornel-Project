#ifndef INDEXESINDEX_HPP_INCLUDED
#define INDEXESINDEX_HPP_INCLUDED

#include <iostream>
#include <Thor/Input.hpp>

#include "Index.hpp"

/**
* \brief Class grouping all the indexes of the game with all the data of equipements, classes and skills
*/

struct IndexesIndex
{
	IndexesIndex();

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
	void heroClassInit();

	/**
	* \brief Initializer of the index of monsters
	*/
	void monsterInit();

	/**
	* \brief Initializer of the index of spells
	*/
	void spellInit();

	/**
	* \brief Initializer of the index of abilities
	*/
	void abilityInit();

	/**
	* \brief Initializer of the index of weapons
	*/
	void weaponInit();

	/**
	* \brief Initializer of the index of helmets
	*/
	void helmetInit();

	/**
	* \brief Initializer of the index of chestplates
	*/
	void chestplateInit();

	/**
	* \brief Initializer of the index of leggings
	*/
	void leggingsInit();

	/**
	* \brief Initializer of the index of boots
	*/
	void bootsInit();

	/**
	* \brief Initializer of the different control maps
	*/
	void mapsInit();

};

#endif