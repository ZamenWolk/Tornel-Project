#include "constants.hpp"

using namespace std;
using namespace sf;

MovingEntity::MovingEntity() :
		m_levelMap(0)
{

}

MovingEntity::MovingEntity(LevelMap *levelMap, int xPos, int yPos) :
		m_levelMap(levelMap)
{
	setPosition(xPos, yPos);
}

bool MovingEntity::loadSprite(const std::string &file, int xSpritePos, int ySpritePos)
{
	if (!loadFromFile(file))
	{
		cout << "[MovingEntity.loadFromFile] SEVERE : Didn't manage to load texture from file" << endl;
		return false;
	}

	setTexture(*this);
	setTextureRect(IntRect(xSpritePos, ySpritePos, BLOCK_SIZE, BLOCK_SIZE));

	return true;
}

bool MovingEntity::movement(Direction direction)
{
	switch (direction)
	{
		case TOP:
			setTextureRect(IntRect(0, 0, BLOCK_SIZE, BLOCK_SIZE));

			if (canMove(direction))
				move(0, -BLOCK_SIZE);
			break;

		case LEFT:
			setTextureRect(IntRect(BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE));

			if (canMove(direction))
				move(-BLOCK_SIZE, 0);
			break;

		case BOTTOM:
			setTextureRect(IntRect(0, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));

			if (canMove(direction))
				move(0, BLOCK_SIZE);
			break;

		case RIGHT:
			setTextureRect(IntRect(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));

			if (canMove(direction))
				move(BLOCK_SIZE, 0);
			break;
	}

	return true;
}

bool MovingEntity::canMove(Direction direction) const
{
	Vector2f position  = getPosition();
	int      *mapArray = m_levelMap->getMapArray(), mapHeight = m_levelMap->getMapHeight(), mapWidth = m_levelMap->getMapWidth();

	vector<int> solidBlock(m_levelMap->getSolidBlock());

	for (int i = 0; i < solidBlock.size(); i++)
	{
		switch (direction)
		{
			case TOP:
				if (position.y == 0 || mapArray[(int)(((position.y/BLOCK_SIZE) - 1)*mapWidth + (position.x)/BLOCK_SIZE)] == solidBlock[i])
				{
					return false;
				}
				else
					return true;
				break;

			case LEFT:
				if (position.x == 0 || mapArray[(int)(((position.y/BLOCK_SIZE))*mapWidth + (position.x/BLOCK_SIZE) - 1)] == solidBlock[i])
				{
					return false;
				}
				else
					return true;
				break;

			case BOTTOM:
				if (position.y == mapHeight || mapArray[(int)(((position.y/BLOCK_SIZE) + 1)*mapWidth + (position.x/BLOCK_SIZE))] == solidBlock[i])
				{
					return false;
				}
				else
					return true;
				break;

			case RIGHT:
				if (position.x == mapWidth || mapArray[(int)(((position.y/BLOCK_SIZE))*mapWidth + (position.x/BLOCK_SIZE) + 1)] == solidBlock[i])
				{
					return false;
				}
				else
					return true;
				break;
		}
	}
}
