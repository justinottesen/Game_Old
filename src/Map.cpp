#include "Map.h"
#include "PerlinGenerator.h"

#include <cstring>
#include <cstdlib>

Map::Map(const Parameters& params) : m_Width(params.width), m_Height(params.height), 
                                     m_Tiles(new Tile[params.width*params.height])
{

  PerlinGenerator pg(42069);
  for (unsigned int i = 0; i < m_Width * m_Height; i++) {
    unsigned int x = i % m_Width;
    unsigned int y = i / m_Width;

    float noise_x = static_cast<float>(x) / params.zoom + params.shift;
    float noise_y = static_cast<float>(y) / params.zoom + params.shift;

    m_Tiles[i].elevation = pg(noise_x, noise_y)*100 + (50 - params.water_amt);
  }

}

Map::~Map()
{
  delete [] m_Tiles;
}