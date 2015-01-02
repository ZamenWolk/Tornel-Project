#include "App.hpp"

App::App():
        isRunning(false),
        eventsMap(),
        clock()
{

}

void App::Start()
{
    isRunning = true;
    clock.restart();
}

void App::Exit()
{
    isRunning = false;
}

App::~App()
{

}