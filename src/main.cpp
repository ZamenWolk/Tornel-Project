#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Index.hpp"
#include "operators.hpp"
#include "Combat.hpp"
#include "Hero.hpp"

using namespace std;
using namespace sf;

extern Clock mainClock;
extern IndexesIndex indexes;

int main()
{
	cout << "Welcome to Tornel'Fighters v." << AutoVersion::FULLVERSION_STRING << endl << endl;

    RenderWindow window;

    window.create(VideoMode(1067, 800), "Tornel'Fighters");
    window.setFramerateLimit(30);

    cout << "The fight begins !" << endl << endl;

    Hero					ZamenEntity("ZamenWolk", 0, indexes.heroClassIndex.searchByName("Knight")),
							SblurbEntity("Sblurb", 0, indexes.heroClassIndex.searchByName("Knight")),
							GrymsEntity("Gryms", 0, indexes.heroClassIndex.searchByName("Knight"));

	Entity					enemy1Entity("Slime 1", 1, indexes.monsterIndex.searchByName("Slime")),
							enemy2Entity("Slime 2", 2, indexes.monsterIndex.searchByName("Slime"));

    CombatEntity	 		Zamen(&ZamenEntity),
							Gryms(&GrymsEntity),
							Sblurb(&SblurbEntity);
	CombatEntity			enemy1(&enemy1Entity),
							enemy2(&enemy2Entity);

	vector<CombatEntity> 	heroTeam(1, Zamen),
							enemyTeam(1, enemy1);

	heroTeam.push_back(Gryms);
	heroTeam.push_back(Sblurb);

	enemyTeam.push_back(enemy2);

    Combat *testCombat = new Combat(heroTeam, enemyTeam, KEYBOARD, AI);

    int combatResult = testCombat->combatRunning(window);

    if (combatResult == 1)
	{
		cout << "You win !" << endl;
	}
	else
	{
		cout << "You lost !" << endl;
	}

    return EXIT_SUCCESS;

}
