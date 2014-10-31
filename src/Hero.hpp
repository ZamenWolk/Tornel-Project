#ifndef HERO_HPP_INCLUDED
#define HERO_HPP_INCLUDED

#include <string>
#include <vector>
#include <SFML/System.hpp>

#include "Index.hpp"
#include "AIControlledEntity.hpp"
#include "Skill.hpp"
#include "Equipement.hpp"
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

   /**
    *   \param[in] name Nave given to the hero
    *	\param[in] experiencePoints Experience points the hero has
    *   \param[in] heroClass Class of the hero
    */

    Hero(	const std::string &name,
			int experiencePoints,
			IndexMember *heroClass):


                experiencePoints(experiencePoints),
                EntityModel(	name,
								EXPERIENCE_TO_LEVEL.result(experiencePoints),
								heroClass),
                weapon(indexes.weaponIndex.searchByName("Default")),
                helmet(indexes.helmetIndex.searchByName("Default")),
                chestplate(indexes.chestplateIndex.searchByName("Default")),
                leggings(indexes.leggingsIndex.searchByName("Default")),
                boots(indexes.bootsIndex.searchByName("Default"))
{

}

   /**
    *   \brief Add experience to the character
    *   \param[in] xpGained Number of experience point to give to the hero
    */

    void gainXP (unsigned int xpGained)
    {
		experiencePoints += xpGained;
	}

   /**
    *   \brief Add a skill to the character's usable skills
    *   \param[in] skillToLearn Pointer to the skill to allow usage for the character
    */

    void learnNewSkill (Skill* skillToLearn)
    {
		if(skillToLearn->skillType == ABILITY)
		{
			knownAbilities.push_back(skillToLearn);
		}
		else
		{
			knownSpells.push_back(skillToLearn);
		}
	}

	/// \return Number of experience points the hero have
    int getExperiencePoints() const
    {
		return experiencePoints;
	}

    /// \return Equipped weapon's effects
	virtual WeaponEffects basicAttackEffects() const
	{
		return weapon->getWeaponEffects();
	}

	virtual void actualizeCharacteristics()
	{
		int newMaxLife(0),
			oldMaxLife(effects.life),
			newMaxMana(0),
			oldMaxMana(effects.mana),
			newMaxStamina(0),
			oldMaxStamina(effects.stamina);

        //Resets the effects
		effects = Effects();

        //Counts the 4 basic effects back from the base level
		effects.strength = entityClass->strengthIncrement.result(level);
		effects.wisdom = entityClass->wisdomIncrement.result(level);
		effects.toughness = entityClass->toughnessIncrement.result(level);
		effects.mentalResistance = entityClass->mentalResistanceIncrement.result(level);

        //Adds the effects of the equipements
		effects += weapon->getEquipementEffects();
		effects += helmet->getEquipementEffects();
		effects += chestplate->getEquipementEffects();
		effects += leggings->getEquipementEffects();
		effects += boots->getEquipementEffects();

        //Changes the max life
		newMaxLife = entityClass->maxLifeIncrement.result(level);
		newMaxLife += TOUGHNESS_TO_LIFE.result(effects.toughness);
		newMaxLife += MENTAL_RESISTANCE_TO_LIFE.result(effects.mentalResistance);
		effects.life += newMaxLife;
		life += effects.life - oldMaxLife;

        //Changes the max mana
		newMaxMana = entityClass->maxManaIncrement.result(level);
		newMaxMana += WISDOM_TO_MANA.result(effects.wisdom);
		effects.mana += newMaxMana;
		mana += effects.mana - oldMaxMana;

        //Changes the max stamina
		newMaxStamina = entityClass->maxStaminaIncrement.result(level);
		newMaxStamina += STRENGTH_TO_STAMINA.result(effects.strength);
		effects.stamina += newMaxStamina;
		stamina += effects.stamina - oldMaxStamina;
	}

   /**
    *   \brief Change the equipement the hero wears
    *	\param[in] type type of the equipement
    *   \param[in] newEquipement New equipement the hero has to wear
    */

	void changeEquipement(EquipementType type, Equipement* newEquipement = NULL)
	{
	    //Resets the equipement if set to NULL
		if (newEquipement == NULL)
		{
			switch (type)
			{
			case HELMET:
				newEquipement = indexes.helmetIndex.searchByName("Default");
				break;

			case CHESTPLATE:
				newEquipement = indexes.chestplateIndex.searchByName("Default");
				break;

			case LEGGINGS:
				newEquipement = indexes.leggingsIndex.searchByName("Default");
				break;

			case BOOTS:
				newEquipement = indexes.bootsIndex.searchByName("Default");
				break;

			case WEAPON:
				newEquipement = indexes.weaponIndex.searchByName("Default");
				break;
			}
		}

		switch (type)
		{
		case HELMET:
			helmet = newEquipement;
			break;

		case CHESTPLATE:
			chestplate = newEquipement;
			break;

		case LEGGINGS:
			leggings = newEquipement;
			break;

		case BOOTS:
			boots = newEquipement;
			break;

		case WEAPON:
			weapon = (Weapon*)newEquipement;
			break;
		}

		actualizeCharacteristics();
	}

   /**
	*	\brief Actualizes the level of the hero according to its experience points
	*/

	void actualizeLevel()
	{
		level = EXPERIENCE_TO_LEVEL.result(experiencePoints);

		actualizeCharacteristics();
		getKnownSkillsFromLevel();
	}


protected:

    int 		experiencePoints; ///< Number of experience points the hero have

	Weapon      *weapon; ///< Weapon the hero is wearing

    Equipement	*helmet, ///< Helmet the hero is wearing
				*chestplate, ///< Chestplate the hero is wearing
				*leggings, ///< Leggings the hero is wearing
				*boots; ///< Boots the hero is wearing
};

/// @}

#endif // HERO_HPP_INCLUDED
