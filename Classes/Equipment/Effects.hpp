#include <SFML/Network.hpp>

struct Effects
{
    Effects();

    Effects(const Effects &equipmentEffects);

    Effects(int lifeGain = 0,
            int manaGain = 0,
            int staminaGain = 0,
            int strengthGain = 0,
            int wisdomGain = 0,
            int toughnessGain = 0,
            int mentalResistanceGain = 0);

    void operator+=(const Effects &a);

    int life,
        mana,
        stamina,
        strength,
        wisdom,
        toughness,
        mentalResistance;
};

bool operator==(Effects const &a, Effects const &b);

bool operator>=(Effects const &a, Effects const &b);

bool operator>(Effects const &a, Effects const &b);

struct WeaponEffects
{
    WeaponEffects();

    WeaponEffects(const WeaponEffects &weaponEffects);

    WeaponEffects(int baseDamage = 0, sf::Time cooldownTime = sf::seconds(1));

    int      baseDamage;
    sf::Time cooldownTime;
};

struct CombatEffects : public Effects, public WeaponEffects
{
    CombatEffects();

    CombatEffects(const Effects &equipmentEffects, const WeaponEffects &weaponEffects);

    CombatEffects(int lifeGain = 0,
                  int manaGain = 0,
                  int staminaGain = 0,
                  int strengthGain = 0,
                  int wisdomGain = 0,
                  int toughnessGain = 0,
                  int mentalResistanceGain = 0,
                  int baseDamage = 0,
                  sf::Time cooldownTime = sf::seconds(1));
};

sf::Packet &operator<<(sf::Packet &packet, const CombatEffects &source);

sf::Packet &operator>>(sf::Packet &packet, CombatEffects &source);