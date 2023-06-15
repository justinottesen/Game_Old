#ifndef __MAP_H
#define __MAP_H

#include <iostream>

struct Tile {
  unsigned int fuel;                        // Value [0-100] 
  unsigned int rubble;                      // Value [0-100]
};

class Map {
  public:
    struct Parameters {
      // Dimensions
      unsigned int width                    = 50;
      unsigned int height                   = 20;
      // Food Colonies
      unsigned int num_food_colonies        = 10;
      unsigned int food_colony_radius       = 10;
      unsigned int max_food                 = 100;
    };

    Map(const Parameters& params);
    ~Map();

    const Tile& getTile(unsigned int x, unsigned int y) const { return m_Tiles[y * m_Width + x]; }
    Tile& getTile(unsigned int x, unsigned int y)  { return m_Tiles[y * m_Width + x]; }

    void printAscii(std::ostream& ostr) const;

  private:
    const unsigned int m_Width, m_Height;
    const unsigned int m_MaxFood;
    Tile* m_Tiles;

    void makeFoodColony(unsigned int centerIndex, unsigned int radius)
      { makeFoodColony(centerIndex % m_Width, centerIndex / m_Height, radius); }
    void makeFoodColony(unsigned int x, unsigned int y, unsigned int radius);
};

#endif