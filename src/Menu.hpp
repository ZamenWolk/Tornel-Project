#include <iostream>

#include "Screen.hpp"
#include "constants.hpp"

class Menu : public Screen
{
public:

	Menu();

	virtual std::string Run(sf::RenderWindow &app, std::map<std::string, Screen *> &screens);

	virtual void Reset();

protected:

};