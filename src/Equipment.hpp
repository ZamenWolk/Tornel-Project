#ifndef EQUIPEMENT_HPP_INCLUDED
#define EQUIPEMENT_HPP_INCLUDED

#include <string>
#include <SFML/System.hpp>

/**
*   \file Equipment.hpp
*   \brief Contains all the classes and structures of Equipment
*/

/**
*	\brief Lists all possible types of equipment
*	\ingroup client
*/

enum EquipmentType
{
	HELMET, ///< Head equipment
	CHESTPLATE, ///< Torso equipment
	LEGGINGS, ///< Legs equipment
	BOOTS, ///< Feet equipment
	WEAPON, ///< Weapon equipment
};

/**
* \addtogroup both
* @{
*/

/**
*   \brief All effects of an equipment on the person who wears it
*
*   Here are all the components of the Effect :
*
*   Life : Pretty straight forward, boosts the life of the subject of the effect
*
*   Mana : Pretty straight forward as well, boosts the stamina of the subject
*
*   Stamina : Do I really have to explain it again ?
*
*   Strength : Strength makes basic attacks and abilities more powerful, and gives the subject more stamina
*
*   Wisdom : Wisdom strengthen the power of spells, and boosts the amount of mana available
*
*   Toughness : Gives the subject more life, and reduces the damages taken from basic attacks and abilities
*
*   Mental resistance : Also gives life to the subject (not as much as Toughness tho), and reduces the damages taken from skills
*/

struct Effects
{
	Effects();

	Effects(const Effects &equipmentEffects);

	Effects(int lifeGain,
			int manaGain,
			int staminaGain,
			int strengthGain,
			int wisdomGain,
			int toughnessGain,
			int mentalResistanceGain);

	void operator+=(const Effects &a);

	int life, ///< Life boost effect
		mana, ///< Mana boost effect
		stamina, ///< Stamina boost effect
		strength, ///< Strength boost effect
		wisdom, ///< Wisdom boost effect
		toughness, ///< Toughness boost effect
		mentalResistance; ///< Mental resistance boost effect
};

/**
*   \brief Additional effects specific to weapons
*/

struct WeaponEffects
{
	WeaponEffects();

	WeaponEffects(const WeaponEffects &weaponEffects);

	WeaponEffects(int baseDamage, sf::Time cooldownTime);

	int      baseDamage; ///< Base damage of the weapon
	sf::Time cooldownTime; ///< Cooldown time of the weapon
};

/**
*   \brief Fusion of Effects and WeaponEffects for combat purposes
*/

struct CombatEffects : public Effects, public WeaponEffects
{
	CombatEffects();

	CombatEffects(const Effects &equipmentEffects, const WeaponEffects &weaponEffects);

	CombatEffects(int lifeGain,
					  int manaGain,
					  int staminaGain,
					  int strengthGain,
					  int wisdomGain,
					  int toughnessGain,
					  int mentalResistanceGain,
					  int baseDamage,
					  sf::Time cooldownTime);
};

/// @}

/**
* \addtogroup both
* @{
*/

/**
*	\brief An equipment
*	\details Can be worn by a hero to have characteristics boosts
*	\todo Add prerequisites to the equipments
*/

class Equipment
{
public:

	/**
	*   \param[in] name Name of the equipement
	*	\param[in] type Type of the equipement
	*	\param[in] effects Effects given by the equipement
	*/

	Equipment(std::string name, std::string type, Effects effects);

	Equipment(const Equipment *equipment);

	std::string getName() const;

	std::string getType() const;

	Effects getEquipmentEffects() const;

protected:

	std::string name, ///< Name of the equipement
				type; ///< Type of the equipement

	Effects equipmentEffects; ///< Effects given by the equipment

};

/**
*   \brief A weapon a fighter can use
*/

class Weapon : public Equipment
{
public:

	Weapon(const std::string &name,
		   std::string type,
		   const Effects &equipementEffects,
		   const WeaponEffects &weaponEffects);

	Weapon(const Weapon *weapon);

	WeaponEffects getWeaponEffects() const;

protected:

	WeaponEffects weaponEffects; ///< Weapon part of the effects given by the weapon

};

/// @}

#endif // EQUIPEMENT_HPP_INCLUDED
