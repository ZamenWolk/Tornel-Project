#include "Effects.hpp"

using namespace sf;

Effects::Effects(const Effects &equipmentEffects) :
        life(equipmentEffects.life),
        mana(equipmentEffects.mana),
        stamina(equipmentEffects.stamina),
        strength(equipmentEffects.strength),
        wisdom(equipmentEffects.wisdom),
        toughness(equipmentEffects.toughness),
        mentalResistance(equipmentEffects.mentalResistance)
{

}

Effects::Effects(int lifeGain,
                 int manaGain,
                 int staminaGain,
                 int strengthGain,
                 int wisdomGain,
                 int toughnessGain,
                 int mentalResistanceGain) :
        life(lifeGain),
        mana(manaGain),
        stamina(staminaGain),
        strength(strengthGain),
        wisdom(wisdomGain),
        toughness(toughnessGain),
        mentalResistance(mentalResistanceGain)
{

}

void Effects::operator+=(const Effects &a)
{
    life += a.life;
    mana += a.mana;
    stamina += a.stamina;
    strength += strength;
    wisdom += a.wisdom;
    toughness += a.toughness;
    mentalResistance += a.mentalResistance;
}

WeaponEffects::WeaponEffects(const WeaponEffects &weaponEffects) :
        baseDamage(weaponEffects.baseDamage),
        cooldownTime(weaponEffects.cooldownTime)
{

}

WeaponEffects::WeaponEffects(int baseDamage, sf::Time cooldownTime) :
        baseDamage(baseDamage),
        cooldownTime(cooldownTime)
{

}

CombatEffects::CombatEffects(const Effects &equipmentEffects, const WeaponEffects &weaponEffects) :
        Effects(equipmentEffects),
        WeaponEffects(weaponEffects)
{

}

CombatEffects::CombatEffects(int lifeGain,
                             int manaGain,
                             int staminaGain,
                             int strengthGain,
                             int wisdomGain,
                             int toughnessGain,
                             int mentalResistanceGain,
                             int baseDamage,
                             sf::Time cooldownTime) :
                    Effects(lifeGain,
                            manaGain,
                            staminaGain,
                            strengthGain,
                            wisdomGain,
                            toughnessGain,
                            mentalResistanceGain),
                    WeaponEffects(baseDamage, cooldownTime)
{

}

bool operator==(Effects const &a, Effects const &b)
{
    return (a.life == b.life && a.mana == b.mana && a.mentalResistance == b.mentalResistance && a.stamina == b.stamina && a.strength == b.strength && a.toughness == b.toughness && a.wisdom == b.wisdom);
}

bool operator>=(Effects const &a, Effects const &b)
{
    return ((a == b) || (a.life >= b.life && a.mana >= b.mana && a.mentalResistance >= b.mentalResistance && a.stamina >= b.stamina && a.strength >= b.strength && a.toughness >= b.toughness && a.wisdom >= b.wisdom));
}

bool operator>(Effects const &a, Effects const &b)
{
    return (a.life > b.life && a.mana > b.mana && a.mentalResistance > b.mentalResistance && a.stamina > b.stamina && a.strength > b.strength && a.toughness > b.toughness && a.wisdom > b.wisdom);
}

Packet &operator<<(Packet &packet, const CombatEffects &source)
{
    return packet << source.life << source.mana << source.stamina << source.strength << source.wisdom << source.toughness << source.mentalResistance << source.baseDamage << source.cooldownTime.asMilliseconds();
}

Packet &operator>>(Packet &packet, CombatEffects &source)
{
    int cooldownTime;

    packet >> source.life >> source.mana >> source.stamina >> source.strength >> source.wisdom >> source.toughness >> source.mentalResistance >> source.baseDamage >> cooldownTime;

    source.cooldownTime = milliseconds(cooldownTime);

    return packet;
}