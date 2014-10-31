#include "constants.hpp"

using namespace std;
using namespace sf;

LevelMap::LevelMap() :      m_mapArray(0),
                            m_mapWidth(0),
                            m_mapHeight(0)
{
    m_solidBlock.push_back(1);
}

LevelMap::~LevelMap()
{
    delete m_mapArray;
}

bool LevelMap::mapWork(const string& filePath, const string& tileset, const Vector2u tileSize)
{
    if (!loadMapArray(filePath))
        return false;

    if (!texturingMap(tileset, tileSize))
        return false;

    return true;

}

bool LevelMap::loadMapArray(const string& filePath)
{
    ifstream    worldMap(LEVEL_FILE_PATH);

    int         actualNumber(0);

    m_mapArray = 0;

    if (!worldMap)
    {
        cout << "[loadMap] SEVERE : didn't manage to open file" << endl;
        return false;
    }

    worldMap >> m_mapWidth;
    worldMap >> m_mapHeight;

    m_mapArray = new int[m_mapWidth*m_mapHeight];

    if (!(m_mapArray))
    {
        cout << "[loadMap] SEVERE : didn't manage to allocate the map array" << endl;
        return false;
    }

    for (int i(0); i < m_mapWidth; i++)
    {
        for (int j(0); j < m_mapHeight; j++)
        {
            worldMap >> actualNumber;
            m_mapArray[i*m_mapHeight + j] = actualNumber;
        }
    }

    return true;
}

bool LevelMap::texturingMap(const string& tileset, const Vector2u tileSize)
{
    if (!m_tileset.loadFromFile(tileset))
    {
        cout << "[TileMap] SEVERE : Didn't managed to load the tileset" << endl;
        return false;
    }

    m_vertices.setPrimitiveType(Quads);
    m_vertices.resize(m_mapWidth * m_mapHeight * 4);

    for (int i = 0; i < m_mapWidth; ++i)
    {
        for (int j = 0; j < m_mapHeight; ++j)
        {
            int tileNumber = m_mapArray[i + j * m_mapWidth];

            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            Vertex* quad = &m_vertices[(i + j * m_mapWidth) * 4];

            quad[0].position = Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            quad[0].texCoords = Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }

    return true;
}

 /* Function adding a solid block number into the solidBlock array.
    First argument is the number of the solid block in the map datas to be added into the solidBlock array */

bool LevelMap::addSolidBlock(int blockNumber)
{
    m_solidBlock.push_back(blockNumber);

    return true;
}

 /* Function to extract the variable inside the class */

int* LevelMap::getMapArray() const
{
    return m_mapArray;
}

int LevelMap::getMapWidth() const
{
    return m_mapWidth;
}

int LevelMap::getMapHeight() const
{
    return m_mapHeight;
}


std::vector<int> LevelMap::getSolidBlock() const
{
    return m_solidBlock;
}
