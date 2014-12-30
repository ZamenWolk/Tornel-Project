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
}

void App::Exit()
{
    isRunning = false;
}

App::~App()
{

}