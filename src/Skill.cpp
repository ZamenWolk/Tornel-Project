#include "Skill.hpp"

Skill::Skill(std::string name, int baseDamage, int manaCost, int staminaCost, sf::Time cooldown, AttackType skillType) :
		name(name),
		baseDamage(baseDamage),
		manaCost(manaCost),
		staminaCost(staminaCost),
		cooldown(cooldown),
		skillType(skillType)
{

}

std::string Skill::getName() const
{
	return name;
}

LevelingSkill::LevelingSkill(Skill *skill, int learnLevel) :
		skill(skill),
		learnLevel(learnLevel)
{

}