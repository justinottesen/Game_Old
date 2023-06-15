#include "Map.h"

#include <cstring>
#include <cstdlib>

Map::Map(const Parameters& params) : m_Width(params.width), m_Height(params.height), 
                                     m_MaxFood(params.max_food),
                                     m_Tiles(new Tile[params.width*params.height])
{
  memset(m_Tiles, 0, m_Width*m_Height*sizeof(Tile));
  for (unsigned int i = 0; i < params.num_food_colonies; i++) {
    makeFoodColony(std::rand() % (m_Width * m_Height), params.food_colony_radius);
  }
}

Map::~Map()
{
  delete [] m_Tiles;
}

void Map::makeFoodColony(unsigned int x, unsigned int y, unsigned int r)
{
  for (unsigned int yr = (y < r) ? 0 : y - r; yr < y + r && yr < m_Height; yr++) {
    for (unsigned int xr = (x < r) ? 0 : x - r; xr < x + r && xr < m_Width; xr++) {
      unsigned int dx = (xr > x) ? xr - x : x - xr;
      unsigned int dy = (yr > y) ? yr - y : y - yr;
      if (dx*dx + dy*dy < r*r) {
        getTile(xr, yr).food = std::max(getTile(xr, yr).food, (m_MaxFood * (r*r - (dx*dx + dy*dy))) / (r*r));
      }
    }
  }
}