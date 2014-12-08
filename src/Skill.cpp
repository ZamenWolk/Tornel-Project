#include "Skill.hpp"

using namespace std;
using namespace sf;

Skill::Skill(string name, int baseDamage, int manaCost, int staminaCost, Time cooldown, AttackType skillType) :
		name(name),
		baseDamage(baseDamage),
		manaCost(manaCost),
		staminaCost(staminaCost),
		cooldown(cooldown),
		skillType(skillType)
{

}

string Skill::getName() const
{
	return name;
}

LevelingSkill::LevelingSkill(Skill *skill, int learnLevel) :
		skill(skill),
		learnLevel(learnLevel)
{

}