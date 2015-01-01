#ifndef CLASSES_SKILL_SKILL
#define CLASSES_SKILL_SKILL

#include <string>
#include <SFML/Network.hpp>
#include "../../Enums/communication.hpp"

struct Skill
{
    Skill(std::string name, int baseDamage, int manaCost, int staminaCost, sf::Time cooldown, AttackType skillType);

    std::string getName() const;

    std::string name;
    int         baseDamage,
                manaCost,
                staminaCost;
    sf::Time    cooldown;
    AttackType  skillType;

};

struct LevelingSkill
{
    LevelingSkill(Skill *skill, int learnLevel = 0);

    Skill *skill;
    int   learnLevel;
};

sf::Packet &operator<<(sf::Packet &packet, const Skill &source);

sf::Packet &operator<<(sf::Packet &packet, const std::vector<Skill *> &source);

#endif