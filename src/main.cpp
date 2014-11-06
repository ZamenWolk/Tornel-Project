#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <map>

#include "Hero.hpp"
#include "../version.hpp"
#include "Screen.hpp"

using namespace std;
using namespace sf;

extern Clock        mainClock;
extern IndexesIndex indexes;

int main()
{
	RenderWindow window;
	string screen("");
	map<string, Screen*> screens;

	string message("Welcome to Tornel'Fighters v.");
	message += AutoVersion::FULLVERSION_STRING;
	logReport(message); cout << endl;

	window.create(VideoMode(1067, 800), "Tornel'Fighters");
	window.setFramerateLimit(45);

	logReport("The fight begins !");

	while (screen != "stop")
	{
		screen = screens[screen]->Run(window, screens);
	}

	logReport("End of program\n", true);

	return EXIT_SUCCESS;

}
