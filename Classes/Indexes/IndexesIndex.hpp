#ifndef CLASSES_INDEXES_INDEXESINDEX_HPP
#define CLASSES_INDEXES_INDEXESINDEX_HPP

#include "../Skills/Skill.hpp"
#include "Index.hpp"
#include "IndexClasses.hpp"
#include "../Equipment/Equipment.hpp"

struct IndexesIndex
{
    IndexesIndex();

    Index<HeroClass> heroClassIndex;

    Index<MonsterClass> monsterIndex;

    Index<Skill> skillIndex;

    EquipmentIndex<Weapon> weaponIndex;

    EquipmentIndex<Equipment> helmetIndex,
            chestplateIndex,
            leggingsIndex,
            bootsIndex;

private:

    void heroClassInit();

    void monsterInit();

    void spellInit();

    void abilityInit();

    void weaponInit();

    void helmetInit();

    void chestplateInit();

    void leggingsInit();

    void bootsInit();

    void mapsInit();

};

#endif