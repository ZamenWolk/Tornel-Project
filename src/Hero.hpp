#ifndef HERO_HPP_INCLUDED
#define HERO_HPP_INCLUDED

#include <string>
#include <vector>
#include <SFML/System.hpp>

#include "Index.hpp"
#include "AIControlledEntity.hpp"
#include "Skill.hpp"
#include "Equipment.hpp"
#include "mathfuncs.hpp"

extern IndexesIndex indexes; ///< Indexes of the game

/**
* \file Hero.hpp
* \brief Contains the Hero class
*/

/**
* \addtogroup client
* @{
*/

/**
* \brief A character controlled by the player
* \details Is part of the main team
*/

class Hero : public EntityModel
{
public:

	/**
	* \param[in] name Nave given to the hero
	* \param[in] experiencePoints Experience points the hero has
	* \param[in] heroClass Class of the hero
	*/

	Hero(const std::string &name, int experiencePoints, EntityClass *heroClass);

	/**
	* \brief Add experience to the character
	* \param[in] xpGained Number of experience point to give to the hero
	*/

	void gainXP(unsigned int xpGained);

	/// \return Number of experience points the hero have
	int getExperiencePoints() const;

	virtual WeaponEffects basicAttackEffects() const;

	virtual void actualizeCharacteristics();

	/**
	* \brief Change the equipment the hero wears
	* \param[in] type type of the equipment
	* \param[in] newEquipment New equipment the hero has to wear
	*/

	void changeEquipment(EquipmentType type, Equipment *newEquipment = NULL);

	/**
	* \brief Actualizes the level of the hero according to its experience points
	*/

	void actualizeLevel();

protected:

	int       experiencePoints; ///< Number of experience points the hero have
	Weapon    *weapon; ///< Weapon the hero is wearing
	Equipment *helmet, ///< Helmet the hero is wearing
	          *chestplate, ///< Chestplate the hero is wearing
	          *leggings, ///< Leggings the hero is wearing
	          *boots; ///< Boots the hero is wearing
};

/// @}

#endif // HERO_HPP_INCLUDED
