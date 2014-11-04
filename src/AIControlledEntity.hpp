#ifndef AICONTROLLEDENTITY_HPP_INCLUDED
#define AICONTROLLEDENTITY_HPP_INCLUDED

#include <string>
#include <vector>
#include <SFML/System.hpp>

#include "Skill.hpp"
#include "Equipment.hpp"
#include "IndexesIndex.hpp"
#include "../communication.hpp"

extern IndexesIndex indexes; ///< Indexes of the game

/**
*   \file AIControlledEntity.hpp
*   \brief Contains all the classes and structures concerning entities and AI
*/

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

	EntityModel(const std::string &name, int level, EntityClass *monsterClass);

	/**
	*	\param[in] entity Entity to copy to the created entity
	*/

	EntityModel(const EntityModel &entity);

	/**
	* \param[in] entity Entity to make the class from
	*/

	EntityModel(EntityInformations &entity);

	/**
	*   \brief Change the life of the entity
	*   \param[in] changeAmount Number of points to add/substract from the entity
	*   \warning Don't forget to enter a negative number in case of a life loss !
	*/

	void changeLife(int changeAmount);

	/**
	*   \brief Change the mana of the entity
	*   \param[in] changeAmount Number of points to add/substract from the entity
	*   \warning Don't forget to enter a negative number in case of a mana loss !
	*/

	void changeMana(int changeAmount);

	/**
	*   \brief Change the stamina of the entity
	*   \param[in] changeAmount Number of points to add/substract from the entity
	*   \warning Don't forget to enter a negative number in case of a stamina loss !
	*/

	void changeStamina(int changeAmount);

	/// Actualize characteristics of the entity \details Used when an equipment is changed or when a Hero earns a level
	virtual void actualizeCharacteristics();

	/// \return True if the entity's life is greater than 0
	bool isAlive() const;

	/// \return Name of the entity
	std::string getName() const;

	/// \return Current life level of the entity
	int getLife() const;

	/// \return Current mana level of the entity
	int getMana() const;

	/// \return Current stamina level of the entity
	int getStamina() const;

	/// \return Current bonuses of the entity
	Effects getEffects() const;

	/// \return Abilities known by the Entity
	std::vector<Skill *> getKnownAbilities() const;

	/// \return Spells known by the Entity
	std::vector<Skill *> getKnownSpells() const;

	/// \return Effects dealt by the entity's basic attack
	virtual WeaponEffects basicAttackEffects() const = 0;

protected:

	/// \return An array containing all the skills the entity can use at its level
	virtual void getKnownSkillsFromLevel();

	int level, ///< Level of the entity
		life, ///< Current life of the entity
		mana, ///< Current mana of the entity
		stamina; ///< Current stamina of the entity

	const std::string name; ///< Name of the entity

	Effects effects; ///< Bonuses of the entity

	EntityClass *entityClass; ///< Class of the entity

	std::vector<Skill *> knownAbilities, ///< Abilities known by the player
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

	Entity(const std::string &name, int level, MonsterClass *monsterClass);

	/**
	*	\param[in] entity Entity to copy to the created entity
	*/

	Entity(const Entity &entity);

	/**
	* \param[in] entity Entity to make the class from
	*/

	Entity(EntityInformations &entity);

	/// \return Effects dealt by the entity's basic attack
	virtual WeaponEffects basicAttackEffects() const;

protected:

	WeaponEffects weaponEffects; ///< Weapon characteristics of the entity
};

/// @}

#endif // AICONTROLLEDENTITY_HPP_INCLUDED
