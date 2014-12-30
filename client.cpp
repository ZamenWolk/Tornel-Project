#include <iostream>
#include <SFML/Graphics.hpp>

#include "version.hpp"
#include "global/functions.hpp"
#include "Enums/Combat.hpp"
#include "Apps/Combat.hpp"

using namespace std;
using namespace sf;

int main()
{
    RenderWindow          window;
    string                screen("main");
    map<string, App *> screens;

    screens["fight"] = new Combat();
    ((Combat*)(screens["fight"]))->setupServer(vector<CombatEntity>(), NO_CONTROL, NO_CONTROL);

    string message("Welcome to Tornel'Fighters v.");
    message += Version::FULLVERSION_STRING;
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