#ifndef EQUIPEMENT_HPP_INCLUDED
#define EQUIPEMENT_HPP_INCLUDED

#include <string>
#include <SFML/System.hpp>

#include "Effects.hpp"

/**
* \file Equipment.hpp
* \brief Contains all the classes and structures of Equipment
*/

/**
* \brief Lists all possible types of equipment
* \ingroup client
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

/// @}

/**
* \addtogroup both
* @{
*/

/**
* \brief An equipment
* \details Can be worn by a hero to have characteristics boosts
*/

class Equipment
{
public:

	/**
	* \param[in] name Name of the equipement
	* \param[in] type Type of the equipement
	* \param[in] effects Effects given by the equipement
	*/

	Equipment(std::string name, std::string type, Effects effects, int prerequisiteLevel = 0, Effects prerequisites = Effects(0, 0, 0, 0, 0, 0, 0));

	/**
	* \param[in] equipment Equipment to copy to new instance
	*/

	Equipment(const Equipment *equipment);

	/// \return Name of the equipement
	std::string getName() const;

	/// \return Type of the equipement
	std::string getType() const;

	/// \return Effects given by the equipement
	Effects getEquipmentEffects() const;

	Effects getPrerequisites() const;

	int getPrerequisiteLevel() const;

protected:

	std::string name, ///< Name of the equipement
	            type; ///< Type of the equipement

	Effects equipmentEffects, ///< Effects given by the equipment
	        prerequisites;

	int prerequisiteLevel;

};

/**
* \brief A weapon a fighter can use
*/

class Weapon : public Equipment
{
public:

	/**
	* \param[in] name Name of the weapon
	* \param[in] type Type of the weapon
	* \param[in] equipmentEffects Equipment part of the effects given by the weapon
	* \param[in] weaponEffects Weapon part of the effects given by the weapon
	*/

	Weapon(const std::string &name, std::string type, const Effects &equipmentEffects, const WeaponEffects &weaponEffects);

	/**
	* \param[in] weapon Weapon instance to copy for the new class
	*/

	Weapon(const Weapon *weapon);

	/// \return Weapon part of the effects given by the weapon
	WeaponEffects getWeaponEffects() const;

protected:

	WeaponEffects weaponEffects; ///< Weapon part of the effects given by the weapon

};

/// @}

#endif // EQUIPEMENT_HPP_INCLUDED
