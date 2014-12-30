#include "../Skills/Skill.hpp"
#include "Index.hpp"
#include "IndexClasses.hpp"
#include "../Equipment/Equipment.hpp"

struct IndexesIndex
{
    IndexesIndex();

    Index<HeroClass> heroClassIndex; ///< Index of hero classes

    Index<MonsterClass> monsterIndex; ///< Index of monsters

    Index<Skill> skillIndex; ///< Index of skills

    EquipmentIndex<Weapon> weaponIndex; ///< Index of weapons

    EquipmentIndex<Equipment> helmetIndex, ///< Index of helmets
            chestplateIndex, ///< Index of chestplates
            leggingsIndex, ///< Index of leggings
            bootsIndex; ///< Index of boots

private:
    /**
    * \brief Initializer of the index of hero classes
    */
    void heroClassInit();

    /**
    * \brief Initializer of the index of monsters
    */
    void monsterInit();

    /**
    * \brief Initializer of the index of spells
    */
    void spellInit();

    /**
    * \brief Initializer of the index of abilities
    */
    void abilityInit();

    /**
    * \brief Initializer of the index of weapons
    */
    void weaponInit();

    /**
    * \brief Initializer of the index of helmets
    */
    void helmetInit();

    /**
    * \brief Initializer of the index of chestplates
    */
    void chestplateInit();

    /**
    * \brief Initializer of the index of leggings
    */
    void leggingsInit();

    /**
    * \brief Initializer of the index of boots
    */
    void bootsInit();

    /**
    * \brief Initializer of the different control maps
    */
    void mapsInit();

};