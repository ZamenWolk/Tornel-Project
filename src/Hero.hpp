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
*   \file Hero.hpp
*   \brief Contains the Hero class
*/

/**
* \addtogroup client
* @{
*/

/**
*   \brief A character controlled by the player
*   \details Is part of the main team
*/

class Hero : public EntityModel
{
public:

	Hero(const std::string &name, int experiencePoints, EntityClass *heroClass);

	void gainXP(unsigned int xpGained);

	int getExperiencePoints() const;

	virtual WeaponEffects basicAttackEffects() const;

	virtual void actualizeCharacteristics();

	void changeEquipment(EquipmentType type, Equipment *newEquipment = NULL);

	void actualizeLevel();

protected:

	int experiencePoints; ///< Number of experience points the hero have

	Weapon 			 *weapon; ///< Weapon the hero is wearing

	Equipment 		 *helmet, ///< Helmet the hero is wearing
			   		 *chestplate, ///< Chestplate the hero is wearing
			   		 *leggings, ///< Leggings the hero is wearing
			   		 *boots; ///< Boots the hero is wearing
};

/// @}

#endif // HERO_HPP_INCLUDED
