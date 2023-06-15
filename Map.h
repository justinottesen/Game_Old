#ifndef __MAP_H
#define __MAP_H

#include <iostream>

struct Tile {
  unsigned int food;
  unsigned int rubble;
};

struct MapParameters {
  // Dimensions
  unsigned int width                = 101;
  unsigned int height               = 45;
  // Food Colonies
  unsigned int num_food_colonies    = 10;
  unsigned int food_colony_radius   = 5;
  unsigned int max_food             = 99;
};

class Map {
  public:

    typedef MapParameters Parameters;

    Map(const Parameters& params = Parameters());
    ~Map();

    const Tile& getTile(unsigned int x, unsigned int y) const { return m_Tiles[y * m_Width + x]; }
    Tile& getTile(unsigned int x, unsigned int y)  { return m_Tiles[y * m_Width + x]; }

    unsigned int width() const { return m_Width; }
    unsigned int height() const { return m_Height; }
    unsigned int maxFood() const { return m_MaxFood; }

  private:
    const unsigned int m_Width, m_Height;
    const unsigned int m_MaxFood;
    Tile* m_Tiles;

    void makeFoodColony(unsigned int centerIndex, unsigned int radius)
      { makeFoodColony(centerIndex % m_Width, centerIndex / m_Width, radius); }
    void makeFoodColony(unsigned int x, unsigned int y, unsigned int radius);
};

#endif