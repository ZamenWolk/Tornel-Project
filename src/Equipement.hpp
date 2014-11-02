#ifndef EQUIPEMENT_HPP_INCLUDED
#define EQUIPEMENT_HPP_INCLUDED

#include <string>
#include <SFML/System.hpp>

#include "constants.hpp"

/**
*   \file Equipement.hpp
*   \brief Contains all the classes and structures of Equipement
*/

/**
* \addtogroup client
* @{
*/

/**
*   \brief All effects of an equipement on the person who wears it
*
*   Here are all the components of the Effect :
*
*   Life : Pretty straight forward, boosts the life of the subject of the effect
*
*   Mana : Pretty straight forward as well, boosts the stamina of the sibject
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
	Effects() :

			life(0), mana(0), stamina(0), strength(0), wisdom(0), toughness(0), mentalResistance(0)
	{

	}

	/**
	*   \param[in] equipementEffects Effects instance to copy for new instance
	*/

	Effects(const Effects &equipementEffects) :

			life(equipementEffects.life),
			mana(equipementEffects.mana),
			stamina(equipementEffects.stamina),
			strength(equipementEffects.strength),
			wisdom(equipementEffects.wisdom),
			toughness(equipementEffects.toughness),
			mentalResistance(equipementEffects.mentalResistance)
	{

	}

	/**
	*   \param[in] lifeGain Life boost effect
	*	\param[in] manaGain Mana boost effect
	*	\param[in] staminaGain Stamina boost effect
	*	\param[in] strengthGain Strength boost effect
	*	\param[in] wisdomGain Wisdom boost effect
	*	\param[in] toughnessGain Toughness boost effect
	*	\param[in] mentalResistanceGain Mental resistance boost effect
	*/

	Effects(int lifeGain,
			int manaGain,
			int staminaGain,
			int strengthGain,
			int wisdomGain,
			int toughnessGain,
			int mentalResistanceGain) :

			life(lifeGain),
			mana(manaGain),
			stamina(staminaGain),
			strength(strengthGain),
			wisdom(wisdomGain),
			toughness(toughnessGain),
			mentalResistance(mentalResistanceGain)
	{

	}

	/**
	*	\brief Addition of 2 Effects instances
	*/

	void operator+=(const Effects &a)
	{
		life += a.life;
		mana += a.mana;
		stamina += a.stamina;
		strength += strength;
		wisdom += a.wisdom;
		toughness += a.toughness;
		mentalResistance += a.mentalResistance;
	}

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
	WeaponEffects() :

			baseDamage(3), cooldownTime(sf::milliseconds(1500))
	{

	}

	/**
	*   \param[in] weaponEffects WeaponEffects instance to copy for new instance
	*/

	WeaponEffects(const WeaponEffects &weaponEffects) :

			baseDamage(weaponEffects.baseDamage), cooldownTime(weaponEffects.cooldownTime)
	{

	}

	/**
	*	\param[in] baseDamage Base damage of the weapon
	*	\param[in] cooldownTime Cooldown time of the weapon
	*/

	WeaponEffects(int baseDamage, sf::Time cooldownTime) :

			baseDamage(baseDamage), cooldownTime(cooldownTime)
	{

	}

	int      baseDamage; ///< Base damage of the weapon
	sf::Time cooldownTime; ///< Cooldown time of the weapon
};

/// @}

/**
* \addtogroup both
* @{
*/

/**
*   \brief Fusion of Effects and WeaponEffects for combat purposes
*/

struct CombatEffects : public Effects, public WeaponEffects
{
	CombatEffects() :

			Effects(), WeaponEffects()
	{

	}

	/**
	*   \param[in] equipementEffects Effects part of data for CombatEffects
	*	\param[in] weaponEffects WeaponEffects part of data for CombatEffects
	*/

	CombatEffects(const Effects &equipementEffects, const WeaponEffects &weaponEffects) :

			Effects(equipementEffects), WeaponEffects(weaponEffects)
	{

	}

	/**
	*   \param[in] lifeGain Life boost effect
	*	\param[in] manaGain Mana boost effect
	*	\param[in] staminaGain Stamina boost effect
	*	\param[in] strengthGain Strength boost effect
	*	\param[in] wisdomGain Wisdom boost effect
	*	\param[in] toughnessGain Toughness boost effect
	*	\param[in] mentalResistanceGain Mental resistance boost effect
	*	\param[in] baseDamage base damage of the weapon
	*	\param[in] cooldownTime Cooldown time of the weapon
	*/

	CombatEffects(int lifeGain,
				  int manaGain,
				  int staminaGain,
				  int strengthGain,
				  int wisdomGain,
				  int toughnessGain,
				  int mentalResistanceGain,
				  int baseDamage,
				  sf::Time cooldownTime) :

			Effects(lifeGain, manaGain, staminaGain, strengthGain, wisdomGain, toughnessGain, mentalResistanceGain),
			WeaponEffects(baseDamage, cooldownTime)
	{

	}
};

/// @}

/**
* \addtogroup both
* @{
*/

/**
*	\brief An equipement
*	\details Can be worn by a hero to have characteristics boosts
*/

class Equipement
{
public:

	/**
	*   \param[in] name Name of the equipement
	*	\param[in] type Type of the equipement
	*	\param[in] effects Effects given by the equipement
	*/

	Equipement(std::string name, std::string type, Effects effects) :

			name(name), type(type), equipementEffects(effects)
	{

	}

	/**
	*	\param[in] equipement Equipement to copy to new instance
	*/

	Equipement(const Equipement *equipement) :

			name(equipement->name), equipementEffects(equipement->equipementEffects)
	{

	}

	/// \return Name of the equipement
	std::string getName() const
	{
		return name;
	}

	/// \return Type of the equipement
	std::string getType() const
	{
		return type;
	}

	/// \return Effects given by the equipement
	Effects getEquipementEffects() const
	{
		return equipementEffects;
	}

protected:

	std::string name, ///< Name of the equipement
				type; ///< Type of the equipement

	Effects equipementEffects; ///< Effects given by the equipement

};

/**
*   \brief A weapon a fighter can use
*/

class Weapon : public Equipement
{
public:

	/**
	*   \param[in] name Name of the weapon
	*	\param[in] type Type of the weapon
	*	\param[in] equipementEffects Equipement part of the effects given by the weapon
	*	\param[in] weaponEffects Weapon part of the effects given by the weapon
	*/

	Weapon(const std::string &name,
		   std::string type,
		   const Effects &equipementEffects,
		   const WeaponEffects &weaponEffects) :

			Equipement(name, type, equipementEffects), weaponEffects(weaponEffects)
	{

	}

	/**
	*   \param[in] weapon Weapon instance to copy for the new class
	*/

	Weapon(const Weapon *weapon) :
			Equipement(weapon->name, weapon->type, weapon->equipementEffects), weaponEffects(weapon->weaponEffects)
	{

	}

	/// \return Weapon part of the effects given by the weapon
	WeaponEffects getWeaponEffects() const
	{
		return weaponEffects;
	}

protected:

	WeaponEffects weaponEffects; ///< Weapon part of the effects given by the weapon

};

/// @}

#endif // EQUIPEMENT_HPP_INCLUDED
