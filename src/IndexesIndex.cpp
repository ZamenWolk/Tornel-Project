#include "IndexesIndex.hpp"

using namespace std;
using namespace sf;

IndexesIndex::IndexesIndex() :
		heroClassIndex("Hero classes"),
		monsterIndex("Monsters"),
		skillIndex("Skill"),
		weaponIndex("Weapon"),
		helmetIndex("Helmet"),
		chestplateIndex("Chestplate"),
		leggingsIndex("Leggings"),
		bootsIndex("Boots")
{
	helmetInit();
	chestplateInit();
	leggingsInit();
	bootsInit();
	weaponInit();
	spellInit();
	abilityInit();
	heroClassInit();
	monsterInit();
	mapsInit();
}

void IndexesIndex::heroClassInit()
{
	heroClassIndex.addEntry(HeroClass("default",
	                                  ThirdPowerFunction(1),
	                                  ThirdPowerFunction(1),
	                                  ThirdPowerFunction(1),
	                                  ThirdPowerFunction(1),
	                                  ThirdPowerFunction(1),
	                                  ThirdPowerFunction(1),
	                                  ThirdPowerFunction(1),
	                                  UsableEquipTypes(),
	                                  vector<LevelingSkill>()));
	heroClassIndex.addEntry(HeroClass("Arcanist",
	                                  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
	                                  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
	                                  ThirdPowerFunction(7.3f, 0.66f, -0.0024f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  UsableEquipTypes(),
	                                  vector<LevelingSkill>()));
	heroClassIndex.addEntry(HeroClass("Arnegon",
	                                  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
	                                  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
	                                  ThirdPowerFunction(7.3f, 0.66f, -0.0024f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  UsableEquipTypes(),
	                                  vector<LevelingSkill>()));
	heroClassIndex.addEntry(HeroClass("Barrkian",
	                                  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
	                                  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
	                                  ThirdPowerFunction(7.3f, 0.66f, -0.0024f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  UsableEquipTypes(),
	                                  vector<LevelingSkill>()));
	heroClassIndex.addEntry(HeroClass("Knight",
	                                  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
	                                  ThirdPowerFunction(5.8302f, 0.1689f, 0.000844531f),
	                                  ThirdPowerFunction(7.3f, 0.66f, -0.0024f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  UsableEquipTypes(),
	                                  vector<LevelingSkill>()));
	heroClassIndex.addEntry(HeroClass("White mage",
	                                  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
	                                  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
	                                  ThirdPowerFunction(7.3f, 0.66f, -0.0024f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  UsableEquipTypes(),
	                                  vector<LevelingSkill>()));
	heroClassIndex.addEntry(HeroClass("Black mage",
	                                  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
	                                  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
	                                  ThirdPowerFunction(7.3f, 0.66f, -0.0024f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  UsableEquipTypes(),
	                                  vector<LevelingSkill>()));
	heroClassIndex.addEntry(HeroClass("Shalian",
	                                  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
	                                  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
	                                  ThirdPowerFunction(7.3f, 0.66f, -0.0024f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  UsableEquipTypes(),
	                                  vector<LevelingSkill>()));
	heroClassIndex.addEntry(HeroClass("Assassin",
	                                  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
	                                  ThirdPowerFunction(22.6f, 2.47f, -0.007f),
	                                  ThirdPowerFunction(7.3f, 0.66f, -0.0024f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  ThirdPowerFunction(7.7f, 2.3f, -0.007f),
	                                  UsableEquipTypes(),
	                                  vector<LevelingSkill>()));
}

void IndexesIndex::monsterInit()
{
	monsterIndex.addEntry(MonsterClass("Slime",
	                                   ThirdPowerFunction(10, 10),
	                                   ThirdPowerFunction(10, 10),
	                                   ThirdPowerFunction(2.5, 2.5),
	                                   ThirdPowerFunction(3, 2),
	                                   ThirdPowerFunction(3, 2),
	                                   ThirdPowerFunction(3, 2),
	                                   ThirdPowerFunction(3, 2),
	                                   vector<Skill *>(0),
	                                   WeaponEffects(3, milliseconds(1500))));
}

void IndexesIndex::spellInit()
{

}

void IndexesIndex::abilityInit()
{

}

void IndexesIndex::weaponInit()
{
	weaponIndex.addType("Admin");
	weaponIndex.addEntry(Weapon("Default", "Admin", Effects(), WeaponEffects()));
}

void IndexesIndex::helmetInit()
{
	helmetIndex.addType("Admin");
	helmetIndex.addEntry(Equipment("Default", "Admin", Effects()));
}

void IndexesIndex::chestplateInit()
{
	chestplateIndex.addType("Admin");
	chestplateIndex.addEntry(Equipment("Default", "Admin", Effects()));
}

void IndexesIndex::leggingsInit()
{
	leggingsIndex.addType("Admin");
	leggingsIndex.addEntry(Equipment("Default", "Admin", Effects()));
}

void IndexesIndex::bootsInit()
{
	bootsIndex.addType("Admin");
	bootsIndex.addEntry(Equipment("Default", "Admin", Effects()));
}

void IndexesIndex::mapsInit()
{
	keyboardMap["characterMenu"] = thor::Action(Keyboard::A, thor::Action::PressOnce);
	keyboardMap["targetMenu"]    = thor::Action(Keyboard::Z, thor::Action::PressOnce);
	keyboardMap["abilityMenu"]   = thor::Action(Keyboard::E, thor::Action::PressOnce);
	keyboardMap["spellMenu"]     = thor::Action(Keyboard::R, thor::Action::PressOnce);
	keyboardMap["weaponAttack"]  = thor::Action(Keyboard::D, thor::Action::PressOnce);
	keyboardMap["mainMenu"]      = thor::Action(Keyboard::Numpad8, thor::Action::PressOnce);
	keyboardMap["precPage"]      = thor::Action(Keyboard::Numpad7, thor::Action::PressOnce);
	keyboardMap["nextPage"]      = thor::Action(Keyboard::Numpad9, thor::Action::PressOnce);
	keyboardMap["selector1"]     = thor::Action(Keyboard::Numpad4, thor::Action::PressOnce);
	keyboardMap["selector2"]     = thor::Action(Keyboard::Numpad5, thor::Action::PressOnce);
	keyboardMap["selector3"]     = thor::Action(Keyboard::Numpad6, thor::Action::PressOnce);
	keyboardMap["selector4"]     = thor::Action(Keyboard::Numpad1, thor::Action::PressOnce);
	keyboardMap["selector5"]     = thor::Action(Keyboard::Numpad2, thor::Action::PressOnce);
	keyboardMap["selector6"]     = thor::Action(Keyboard::Numpad3, thor::Action::PressOnce);
	keyboardMap["charSelector"]  = keyboardMap["selector1"] || keyboardMap["selector2"] || keyboardMap["selector3"] || keyboardMap["selector4"] || keyboardMap["selector5"];
	keyboardMap["selector"]      = keyboardMap["selector6"] || keyboardMap["charSelector"];
}