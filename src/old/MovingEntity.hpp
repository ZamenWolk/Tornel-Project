#ifndef MOVINGENTITY_HPP_INCLUDED
#define MOVINGENTITY_HPP_INCLUDED

#include "LevelMap.hpp"
#include "constants.hpp"

/**
*   \file MovingEntity.hpp
*   \brief Contains the MovingEntity class
*/

/**
*   \brief Any moving entity on a map. Is a Sprite and a Texture
*   \warning Prefer a more specific class
*/

class MovingEntity : public sf::Texture, public sf::Sprite
{
public:

	MovingEntity();

	/**
	*   \brief Initialization with predetermined coordinates
	*   \param levelMap Pointer to the map the entity belongs to
	*   \param xPos X coordinate of the entity on the map
	*   \param yPos Y coordinate of the entity on the map
	*/

	MovingEntity(LevelMap *levelMap, int xPos = 0, int yPos = 0);

	/**
	*   \brief Load the sprite and set the texture for the entity
	*   \param file Path to the sprite
	*   \param xSpritePos X coordinate of the sprite in the sprite file
	*   \param ySpritePos Y coordinate of the sprite in the sprite file
	*/

	bool loadSprite(const std::string &file, int xSpritePos = 0, int ySpritePos = 0);

	/**
	* \brief Make the sprite move on the map.
	* \param direction Direction where the entity have to go
	*/

	bool movement(Direction direction);

	/**
	*   \brief Tell if the entity can move is the direction given
	*   \warning Utilisation of this function alone is not recommended
	*   \param direction Direction in which the test have to take place
	*   \return true if the entity can move into this direction
	*/

	bool canMove(Direction direction) const;

private:

	LevelMap *m_levelMap;
};

#endif // HERO_HPP_INCLUDED
