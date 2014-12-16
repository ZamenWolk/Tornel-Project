#ifndef SCREEN_HPP_INCLUDED
#define SCREEN_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class Screen
{
public :
	virtual std::string Run(sf::RenderWindow &app, std::map<std::string, Screen *> &screens) = 0;
	virtual void Reset() = 0;
};

#endif