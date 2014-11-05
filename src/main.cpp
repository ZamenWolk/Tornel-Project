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

	cout << "Welcome to Tornel'Fighters v." << AutoVersion::FULLVERSION_STRING << endl << endl;

	window.create(VideoMode(1067, 800), "Tornel'Fighters");
	window.setFramerateLimit(45);

	cout << "The fight begins !" << endl << endl;

	while (screen != "stop")
	{
		screen = screens[screen]->Run(window, screens);
	}

	return EXIT_SUCCESS;

}
