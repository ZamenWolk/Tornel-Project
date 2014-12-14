#ifndef EFFECTS_HPP_INCLUDED
#define EFFECTS_HPP_INCLUDED

/**
* \brief All effects of an equipment on the person who wears it
*
*   Here are all the components of the Effect :
*
*   Life : Pretty straight forward, boosts the life of the subject of the effect
*
*   Mana : Pretty straight forward as well, boosts the stamina of the subject
*
*   Stamina : Do I really have to explain it again ?
*
*   Strength : Strength makes basic attacks and abilities more powerful, and gives the subject more stamina
*
*   Wisdom : Wisdom strengthen the power of spells, and boosts the amount of mana available
*
*   Toughness : Gives the subject more life, and reduces the damages taken from basic attacks and abilities
*
*   Mental resistance : Also gives life to the subject (not as much as Toughness tho), and reduces the damages taken from skills
*/

struct Effects
{
    Effects();

    /**
    * \param[in] equipmentEffects Effects instance to copy for new instance
    */

    Effects(const Effects &equipmentEffects);

    /**
    * \param[in] lifeGain Life boost effect
    * \param[in] manaGain Mana boost effect
    * \param[in] staminaGain Stamina boost effect
    * \param[in] strengthGain Strength boost effect
    * \param[in] wisdomGain Wisdom boost effect
    * \param[in] toughnessGain Toughness boost effect
    * \param[in] mentalResistanceGain Mental resistance boost effect
    */

    Effects(int lifeGain, int manaGain, int staminaGain, int strengthGain, int wisdomGain, int toughnessGain, int mentalResistanceGain);

    /**
    * \brief Addition of 2 Effects instances
    */

    void operator+=(const Effects &a);

    int life, ///< Life boost effect
            mana, ///< Mana boost effect
            stamina, ///< Stamina boost effect
            strength, ///< Strength boost effect
            wisdom, ///< Wisdom boost effect
            toughness, ///< Toughness boost effect
            mentalResistance; ///< Mental resistance boost effect
};

bool operator==(Effects const &a, Effects const &b);

bool operator>=(Effects const &a, Effects const &b);

bool operator>(Effects const &a, Effects const &b);

/**
* \brief Additional effects specific to weapons
*/

struct WeaponEffects
{
    WeaponEffects();

    /**
    * \param[in] weaponEffects WeaponEffects instance to copy for new instance
    */

    WeaponEffects(const WeaponEffects &weaponEffects);

    /**
    * \param[in] baseDamage Base damage of the weapon
    * \param[in] cooldownTime Cooldown time of the weapon
    */

    WeaponEffects(int baseDamage, sf::Time cooldownTime);

    int      baseDamage; ///< Base damage of the weapon
    sf::Time cooldownTime; ///< Cooldown time of the weapon
};

/**
* \brief Fusion of Effects and WeaponEffects for combat purposes
*/

struct CombatEffects : public Effects, public WeaponEffects
{
    CombatEffects();

    /**
    * \param[in] equipmentEffects Effects part of data for CombatEffects
    * \param[in] weaponEffects WeaponEffects part of data for CombatEffects
    */

    CombatEffects(const Effects &equipmentEffects, const WeaponEffects &weaponEffects);

    /**
    * \param[in] lifeGain Life boost effect
    * \param[in] manaGain Mana boost effect
    * \param[in] staminaGain Stamina boost effect
    * \param[in] strengthGain Strength boost effect
    * \param[in] wisdomGain Wisdom boost effect
    * \param[in] toughnessGain Toughness boost effect
    * \param[in] mentalResistanceGain Mental resistance boost effect
    * \param[in] baseDamage base damage of the weapon
    * \param[in] cooldownTime Cooldown time of the weapon
    */

    CombatEffects(int lifeGain,
            int manaGain,
            int staminaGain,
            int strengthGain,
            int wisdomGain,
            int toughnessGain,
            int mentalResistanceGain,
            int baseDamage,
            sf::Time cooldownTime);
};

#endif