#ifndef CLASSES_HPP_INCLUDED
#define CLASSES_HPP_INCLUDED

#include <vector>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/**
*   \file LevelMap.hpp
*   \brief Contains the LevelMap class
*/

/**
*   \brief Map in the game, without any moving element
*/

class LevelMap : public sf::Drawable, public sf::Transformable
{
public:

	LevelMap();

	~LevelMap();

	/**
	*   \brief Load and texturisation of the static map
	*   \details Combination of loadMapArray and texturingMap
	*   \param filePath Path to the file containing the map datas.
	*   \param tileset Path to the tileset used for the map.
	*   \param tileSize Size of one tile on the map and on tne tileset, often declared as a constant in the appropriate file
	*/

	bool mapWork(const std::string &filePath, const std::string &tileset, const sf::Vector2u tileSize);

	/**
	*   \brief Extraction of the array of data for the static map. Declaration of the dynamic 1D array containing the map datas.
	*   \warning Utilisation of this function alone is not recommended. Use mapWork instead.
	*   \param filePath Path to the file containing the datas
	*/

	bool loadMapArray(const std::string &filePath);

	/**
	*   \brief Transformation of the map datas in the dynamic array into a real texture.
	*   \warning Utilisation of this function alone is not recommended. Use mapWork instead.
	*   \param tileset Path to the tileset used for the datas.
	*   \param tilesize Size of a tile in the map and in the tileset. Constant defined in the constant.hpp file often used
	*/

	bool texturingMap(const std::string &tileset, const sf::Vector2u tileSize);

	/**
	*   \brief Addition of a solid block number into the solidBlock array.
	*   \param blocknumber Number of the solid block in the map datas to be added into the solidBlock array
	*/

	bool addSolidBlock(const int blockNumber);

	/**
	*   \return Array containig the static map datas
	*/

	int *getMapArray() const;

	/**
	*   \return Map width
	*/

	int getMapWidth() const;

	/**
	*   \return Map height
	*/

	int getMapHeight() const;

	/**
	*   \return Index of all the block types considered solid
	*/

	std::vector<int> getSolidBlock() const;

private:

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		states.texture = &m_tileset;

		target.draw(m_vertices, states);
	}

	sf::VertexArray m_vertices;
	sf::Texture     m_tileset;
	int             *m_mapArray, m_mapWidth, m_mapHeight;

	std::vector<int> m_solidBlock;
};

#endif // CLASSES_HPP_INCLUDED
