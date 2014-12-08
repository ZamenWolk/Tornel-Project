#ifndef SKILL_HPP_INCLUDED
#define SKILL_HPP_INCLUDED

#include <string>
#include <SFML/System.hpp>

#include "constants.hpp"
#include "../communication.hpp"

/**
* \file Skill.hpp
* \brief Contains the struct Skill and the LevellingSkill structure
*/

/**
* \addtogroup both
* @{
*/

/**
* \brief A skill usable by fighters
* \details Defined by an animation and a base damage
*/

struct Skill
{
	/**
	* \param[in] name Name of the skill
	* \param[in] baseDamage Base damage of the skill
	* \param[in] manaCost Mana cost for using the skill
	* \param[in] staminaCost Stamina cost for using the skill
	* \param[in] cooldown Cooldown after the skill
	* \param[in] skillType Type of the skill
	*/

	Skill(std::string name, int baseDamage, int manaCost, int staminaCost, sf::Time cooldown, AttackType skillType);

	/// \return name of the Skill
	std::string getName() const;

	std::string name; ///< Name of the Skill
	int         baseDamage, ///< Base damage of the skill
	            manaCost, ///< Mana cost for using the skill
	            staminaCost; ///< Stamina cost for using the skill
	sf::Time    cooldown; ///< Cooldown after the skill
	AttackType  skillType; ///< Type of the skill

};

/**
* \brief A conponent of the arrays defining when a hero type can learn a Skill
*/

struct LevelingSkill
{

	/**
	* \param[in] skill Skill the class is built around
	* \param[in] learnLevel Level at which the skill is nearnt
	*/

	LevelingSkill(Skill *skill, int learnLevel = 0);

	Skill *skill; ///< Skill the class is built around
	int   learnLevel; ///< Level at which the skill is learnt
};

/// @}

#endif // SKILL_HPP_INCLUDED
