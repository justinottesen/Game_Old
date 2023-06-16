#ifndef __MAP_H
#define __MAP_H

#include <iostream>

struct Tile {
  int elevation = 0;
};

struct MapParameters {
  // Dimensions
  unsigned int width                = 200;
  unsigned int height               = 50;
  // Terrain Parameters
  unsigned int zoom                 = 9;
  unsigned int shift                = 0;
  unsigned int water_amt            = 30;
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

  private:
    const unsigned int m_Width, m_Height;
    Tile* m_Tiles;

};

#endif