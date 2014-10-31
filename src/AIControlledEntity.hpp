#ifndef AICONTROLLEDENTITY_HPP_INCLUDED
#define AICONTROLLEDENTITY_HPP_INCLUDED

#include <string>
#include <vector>
#include <SFML/System.hpp>

#include "Skill.hpp"
#include "Equipement.hpp"
#include "Index.hpp"
#include "operators.hpp"

extern IndexesIndex indexes; ///< Indexes of the game

   /**
    *   \file AIControlledEntity.hpp
    *   \brief Contains all the classes and structures concerning entities and AI
    */

/**
* \addtogroup both Shared
* \brief Compounds shared between client and server
* \ingroup server client
* @{
*/

   /**
	*	\brief Informations received from server to create premade entities
	*/

struct EntityInformations
{
	std::string 		name; ///< Name of the entity
	int 				life, ///< Current life of the entity
						mana, ///< Current mana of the entity
						stamina; ///< Current stamina of the entity
	std::vector<Skill*> knownAbilities, ///< Known abilities of the entity
						knownSpells; ///< Known spells of the entity
	CombatEffects 		effects; ///< Current effects of the entity
};

/// @}

/**
* \addtogroup client
* @{
*/

   /**
    *   \brief An entity that fight during the game, either ally or enemy
    */

class EntityModel
{

public:

   /**
    *   \param[in] name Name of the entity
    *   \param[in] level Level of the entity
    *   \param[in] monsterClass Class of the entity
    */

    EntityModel(	const std::string &name,
					int level,
					IndexMember *monsterClass):

						name(name),
						level(level),
						effects{	0,
									0,
									0,
									monsterClass->strengthIncrement.result(level),
									monsterClass->wisdomIncrement.result(level),
									monsterClass->toughnessIncrement.result(level),
									monsterClass->mentalResistanceIncrement.result(level)},
						entityClass(monsterClass),
						knownAbilities(0),
						knownSpells(0)
	{
		effects.life = monsterClass->maxLifeIncrement.result(level);
		effects.life += TOUGHNESS_TO_LIFE.result(effects.toughness);
		effects.life += MENTAL_RESISTANCE_TO_LIFE.result(effects.mentalResistance);
		life = effects.life;

		effects.mana = monsterClass->maxManaIncrement.result(level);
		effects.mana += WISDOM_TO_MANA.result(effects.wisdom);
		mana = effects.mana;

		effects.stamina = monsterClass->maxStaminaIncrement.result(level);
		effects.stamina += STRENGTH_TO_STAMINA.result(effects.strength);
		stamina = effects.stamina;

		getKnownSkillsFromLevel();
	}

   /**
	*	\param[in] entity Entity to copy to the created entity
	*/

	EntityModel(const EntityModel& entity):

					name(entity.name),
					level(entity.level),
					life(entity.life),
					mana(entity.mana),
					stamina(entity.stamina),
					effects(entity.effects),
					entityClass(entity.entityClass),
					knownAbilities(entity.knownAbilities),
					knownSpells(entity.knownSpells)
	{

	}

   /**
	* \param[in] entity Entity to make the class from
	*/

	EntityModel(	EntityInformations entity):

						name(entity.name),
						level(1),
						life(entity.life),
						mana(entity.mana),
						stamina(entity.stamina),
						effects(entity.effects),
						entityClass(indexes.heroClassIndex.searchByName("default")),
						knownAbilities(entity.knownAbilities),
						knownSpells(entity.knownSpells)
	{

	}

   /**
    *   \brief Change the life of the entity
    *   \param[in] changeAmount Number of points to add/substract from the entity
    *   \warning Don't forget to enter a negative number in case of a life loss !
    */

    void changeLife (int changeAmount)
    {
		life += changeAmount;
		if (life < 0)
			life = 0;
		if (life > effects.life)
			life = effects.life;
	}

   /**
    *   \brief Change the mana of the entity
    *   \param[in] changeAmount Number of points to add/substract from the entity
    *   \warning Don't forget to enter a negative number in case of a mana loss !
    */

    void changeMana (int changeAmount)
    {
		mana += changeAmount;
		if (mana < 0)
			mana = 0;
		if (mana > effects.mana)
			mana = effects.mana;
	}

   /**
    *   \brief Change the stamina of the entity
    *   \param[in] changeAmount Number of points to add/substract from the entity
    *   \warning Don't forget to enter a negative number in case of a stamina loss !
    */

    void changeStamina (int changeAmount)
    {
		stamina += changeAmount;
		if (stamina < 0)
			stamina = 0;
		if (stamina > effects.stamina)
			stamina = effects.stamina;
	}

	/// Actualize characteristics of the entity \details Used when an equipement is changed or when a Hero earns a level
    virtual void actualizeCharacteristics()
    {
		int newMaxLife(0),
			newMaxMana(0),
			newMaxStamina(0);

        //Actualizes base characteristics from level
		effects.strength = entityClass->strengthIncrement.result(level);
		effects.wisdom = entityClass->wisdomIncrement.result(level);
		effects.toughness = entityClass->toughnessIncrement.result(level);
		effects.mentalResistance = entityClass->mentalResistanceIncrement.result(level);

        //Calculates the new max life and changes the current life accordingly
		newMaxLife = entityClass->maxLifeIncrement.result(level);
		newMaxLife += TOUGHNESS_TO_LIFE.result(effects.toughness);
		newMaxLife += MENTAL_RESISTANCE_TO_LIFE.result(effects.mentalResistance);
		life += newMaxLife - effects.life;
		if (life < 0)
            life = 0;
		effects.life = newMaxLife;

        //Calculates the new max mana and changes the current mana accordingly
		newMaxMana = entityClass->maxManaIncrement.result(level);
		newMaxMana += WISDOM_TO_MANA.result(effects.wisdom);
		mana += newMaxMana - effects.mana;
		if (mana < 0)
            mana = 0;
		effects.mana = newMaxMana;

        //Calculates the new max stamina and changes the current stamina accordingly
		newMaxStamina = entityClass->maxStaminaIncrement.result(level);
		newMaxStamina += STRENGTH_TO_STAMINA.result(effects.strength);
		stamina += newMaxStamina - effects.stamina;
		if (stamina < 0)
            stamina = 0;
		effects.stamina = newMaxStamina;
	}

	/// \return True if the entity's life is greater than 0
    bool isAlive () const
    {
		return life > 0 ? true : false;
	}

    /// \return Name of the entity
    std::string getName() const
    {
		return name;
	}

    /// \return Current life level of the entity
    int getLife() const
    {
		return life;
	}

    /// \return Current mana level of the entity
    int getMana() const
    {
		return mana;
	}

    /// \return Current stamina level of the entity
	int getStamina() const
	{
		return stamina;
	}

	/// \return Current bonuses of the entity
	Effects getEffects() const
	{
		return effects;
	}

	/// \return Abilities known by the Entity
	std::vector<Skill*> getKnownAbilities() const
	{
		return knownAbilities;
	}

	/// \return Spells known by the Entity
	std::vector<Skill*> getKnownSpells() const
	{
		return knownSpells;
	}

	/// \return Effects dealt by the entity's basic attack
	virtual WeaponEffects basicAttackEffects() const = 0;

protected:

	/// \return An array containing all the skills the entity can use at its level
    void getKnownSkillsFromLevel()
    {
        //Put the skills vectors back to 0 so they can be filled again
    	while (knownAbilities.size() > 0)
		{
			knownAbilities.pop_back();
		}

		while (knownSpells.size() > 0)
		{
			knownSpells.pop_back();
		}

        //Adds every skill that meets level requirement to the appropriate vector
		for(std::vector<LevelingSkill>::iterator it = entityClass->learnableSkills.begin(); it != entityClass->learnableSkills.end(); it++)
		{
			if (level >= it->learnLevel)
			{
				if(it->skill->skillType == ABILITY)
				{
					knownAbilities.push_back(it->skill);
				}
				else
				{
					knownSpells.push_back(it->skill);
				}
			}
		}
	}

    int 					level, ///< Level of the entity
							life, ///< Current life of the entity
							mana, ///< Current mana of the entity
							stamina; ///< Current stamina of the entity

    const std::string 		name; ///< Name of the entity

    Effects 				effects; ///< Bonuses of the entity

	IndexMember				*entityClass; ///< Class of the entity

    std::vector<Skill*> 	knownAbilities, ///< Abilities known by the player
							knownSpells; ///< Skills known by the Entity

};

   /**
	*	\brief Temporary entity, controlled by the AI
	*/

class Entity : public EntityModel
{
public:

   /**
    *   \param[in] name Name of the entity
    *   \param[in] level Level of the entity
    *   \param[in] monsterClass Class of the entity
    */

	Entity(	const std::string &name,
			int level,
			MonsterMember *monsterClass):

				EntityModel(name, level, (IndexMember*)monsterClass),
				weaponEffects(monsterClass->effects)
	{

	}

   /**
	*	\param[in] entity Entity to copy to the created entity
	*/

	Entity(	const Entity& entity):
				EntityModel(entity),
				weaponEffects(entity.weaponEffects)
	{

	}

   /**
	* \param[in] entity Entity to make the class from
	*/

	Entity(	EntityInformations entity):

				EntityModel(entity),
				weaponEffects(entity.effects)
	{

	}

	/// \return Effects dealt by the entity's basic attack
	virtual WeaponEffects basicAttackEffects() const
	{
		return weaponEffects;
	}

protected:

	WeaponEffects weaponEffects; ///< Weapon characteristics of the entity
};

/// @}

#endif // AICONTROLLEDENTITY_HPP_INCLUDED
