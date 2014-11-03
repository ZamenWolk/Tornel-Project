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
	Effects() :

			life(0), mana(0), stamina(0), strength(0), wisdom(0), toughness(0), mentalResistance(0)
	{

	}

	/**
	*   \param[in] equipmentEffects Effects instance to copy for new instance
	*/

	Effects(const Effects &equipmentEffects) :

			life(equipmentEffects.life),
			mana(equipmentEffects.mana),
			stamina(equipmentEffects.stamina),
			strength(equipmentEffects.strength),
			wisdom(equipmentEffects.wisdom),
			toughness(equipmentEffects.toughness),
			mentalResistance(equipmentEffects.mentalResistance)
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
	*   \param[in] equipmentEffects Effects part of data for CombatEffects
	*	\param[in] weaponEffects WeaponEffects part of data for CombatEffects
	*/

	CombatEffects(const Effects &equipmentEffects, const WeaponEffects &weaponEffects) :

			Effects(equipmentEffects), WeaponEffects(weaponEffects)
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

	Equipment(std::string name, std::string type, Effects effects) :

			name(name), type(type), equipmentEffects(effects)
	{

	}

	/**
	*	\param[in] equipment Equipment to copy to new instance
	*/

	Equipment(const Equipment *equipment) :

			name(equipment->name), equipmentEffects(equipment->equipmentEffects)
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
	Effects getEquipmentEffects() const
	{
		return equipmentEffects;
	}

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

	/**
	*   \param[in] name Name of the weapon
	*	\param[in] type Type of the weapon
	*	\param[in] equipementEffects Equipment part of the effects given by the weapon
	*	\param[in] weaponEffects Weapon part of the effects given by the weapon
	*/

	Weapon(const std::string &name,
		   std::string type,
		   const Effects &equipementEffects,
		   const WeaponEffects &weaponEffects) :

			Equipment(name, type, equipementEffects), weaponEffects(weaponEffects)
	{

	}

	/**
	*   \param[in] weapon Weapon instance to copy for the new class
	*/

	Weapon(const Weapon *weapon) :
			Equipment(weapon->name, weapon->type, weapon->equipmentEffects), weaponEffects(weapon->weaponEffects)
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
