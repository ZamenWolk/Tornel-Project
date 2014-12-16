#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Hero.hpp"
#include "../version.hpp"
#include "Screen.hpp"
#include "Combat.hpp"
#include "Menu.hpp"

using namespace std;
using namespace sf;

extern Clock        mainClock;
extern IndexesIndex indexes;

int main()
{
	RenderWindow          window;
	string                screen("main");
	map<string, Screen *> screens;

	screens["fight"] = new Combat();
	(Combat)(*screens["fight"]).Setup(vector<CombatEntity>(), NO_CONTROL, NO_CONTROL);
	screens["main"]  = new Menu();

	string message("Welcome to Tornel'Fighters v.");
	message += AutoVersion::FULLVERSION_STRING;
	logReport(message, true);
	cout << endl;

	window.create(VideoMode(1067, 800), "Tornel'Fighters");
	window.setFramerateLimit(45);

	while (screen != "stop")
	{
		screen = screens[screen]->Run(window, screens);
	}

	logReport("End of program\n", true);

	return EXIT_SUCCESS;

}
