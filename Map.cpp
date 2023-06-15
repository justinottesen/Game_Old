#include "Map.h"

#include <cmath>
#include <cstring>
#include <cstdlib>

#include <algorithm>

Map::Map(const Parameters& params) : m_Width(params.width), m_Height(params.height), 
                                     m_MaxFood(params.max_food),
                                     m_Tiles(new Tile[params.width*params.height])
{
  memset(m_Tiles, 0, m_Width*m_Height*sizeof(Tile));
  for (unsigned int i = 0; i < params.num_food_colonies; i++) {} {
    //makeFoodColony(rand() % m_Width * m_Height, params.food_colony_radius);
  }
}

Map::~Map()
{
  delete m_Tiles;
}

void Map::printAscii(std::ostream& ostr) const {
  const char* asciiScale = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
  ostr << std::string(m_Width + 2, '-') << std::endl;
  for (unsigned int y = 0; y < m_Height; y++) {
    ostr << "|";
    for (unsigned int x = 0; x < m_Width; x++) {
      ostr << asciiScale[70 - getTile(x, y).fuel];
    }
    ostr << "|" << std::endl;
  }
  ostr << std::string(m_Width + 2, '-') << std::endl;
}

void Map::makeFoodColony(unsigned int x, unsigned int y, unsigned int radius)
{
  for (unsigned int xr = std::max(x - radius, 0u); xr < std::min(xr + radius, m_Width-1); xr++) {
    for (unsigned int yr = std::max(y - radius, 0u); yr < std::min(yr + radius, m_Height-1); yr++) {
      getTile(xr, yr).fuel = (m_MaxFood * radius - static_cast<unsigned int>(std::sqrt((xr-x)*(xr-x) + (yr-y)*(yr-y)))) / radius;
    }
  }
}
