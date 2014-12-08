#ifndef INDEXESINDEX_HPP_INCLUDED
#define INDEXESINDEX_HPP_INCLUDED

#include <iostream>
#include <Thor/Input.hpp>

#include "Index.hpp"

#define K_CHARMENU indexes.keyboardMap.isActive("characterMenu")
#define K_TARGMENU indexes.keyboardMap.isActive("targetMenu")
#define K_ABILMENU indexes.keyboardMap.isActive("abilityMenu")
#define K_SPELLMENU indexes.keyboardMap.isActive("spellMenu")
#define K_WEAPATK indexes.keyboardMap.isActive("weaponAttack")
#define K_MAINMENU indexes.keyboardMap.isActive("mainMenu")
#define K_PREVPAGE indexes.keyboardMap.isActive("prevPage")
#define K_NEXTPAGE indexes.keyboardMap.isActive("nextPage")
#define K_SELEC1 indexes.keyboardMap.isActive("selector1")
#define K_SELEC2 indexes.keyboardMap.isActive("selector2")
#define K_SELEC3 indexes.keyboardMap.isActive("selector3")
#define K_SELEC4 indexes.keyboardMap.isActive("selector4")
#define K_SELEC5 indexes.keyboardMap.isActive("selector5")
#define K_SELEC6 indexes.keyboardMap.isActive("selector6")
#define K_CHARSELEC indexes.keyboardMap.isActive("charSelector")
#define K_SELEC indexes.keyboardMap.isActive("selector")

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