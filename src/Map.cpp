#include "Map.h"
#include "PerlinGenerator.h"

#include <cstring>
#include <cstdlib>

Map::Map(const Parameters& params) : m_Width(params.width), m_Height(params.height), 
                                     m_MaxElevation(params.max_elevation),
                                     m_WaterLevel(params.water_level),
                                     m_Tiles(new Tile[params.width*params.height])
{

  PerlinGenerator map_generator(params.seed);
  for (unsigned int i = 0; i < m_Width * m_Height; i++) {
    unsigned int x = i % m_Width;
    unsigned int y = i / m_Width;

    float noise_x = static_cast<float>(x) / params.zoom;
    float noise_y = static_cast<float>(y) / params.zoom;

    m_Tiles[i].elevation = (map_generator(noise_x, noise_y) + 1) * (m_MaxElevation/2);
    m_Tiles[i].type = (m_Tiles[i].elevation < m_WaterLevel) ? Tile::WATER : Tile::LAND;
  }

}

Map::~Map()
{
  delete [] m_Tiles;
}