#ifndef SCREEN_HPP_INCLUDED
#define SCREEN_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class Screen
{
public :
	virtual std::string Run (sf::RenderWindow &app) = 0;
};

#endif