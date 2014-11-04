#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Hero.hpp"
#include "../version.hpp"

using namespace std;
using namespace sf;

extern Clock        mainClock;
extern IndexesIndex indexes;

int main()
{
	cout << "Welcome to Tornel'Fighters v." << AutoVersion::FULLVERSION_STRING << endl << endl;

	RenderWindow window;

	window.create(VideoMode(1067, 800), "Tornel'Fighters");
	window.setFramerateLimit(30);

	cout << "The fight begins !" << endl << endl;

	Hero ZamenEntity("ZamenWolk",
					 0,
					 indexes.heroClassIndex.searchByName("Knight")),
	     SblurbEntity("Sblurb",
					  0,
					  indexes.heroClassIndex.searchByName("Knight")),
		 GrymsEntity("Gryms",
					 0,
					 indexes.heroClassIndex.searchByName("Knight"));

	Entity enemy1Entity("Slime 1", 1, indexes.monsterIndex.searchByName("Slime")), enemy2Entity("Slime 2",
																								2,
																								indexes.monsterIndex.searchByName(
																								"Slime"));

	return EXIT_SUCCESS;

}
