#ifndef __MAP_H
#define __MAP_H

#include <iostream>


struct Tile {
  enum Type { WATER, LAND };

  unsigned int  elevation;      // Value 0 - Max Elevation
  Type          type;           // Dependant on Elevation
};

struct MapParameters {
  // Dimensions
  unsigned int width                = 200;
  unsigned int height               = 50;
  // Terrain Generation Parameters
  unsigned int seed                 = 42069; //= std::time(NULL);
  unsigned int zoom                 = 10;
  unsigned int max_elevation        = 100;
  unsigned int water_level          = 45;
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
    unsigned int maxElevation() const { return m_MaxElevation; }
    unsigned int waterLevel() const { return m_WaterLevel; }

  private:
    // Map Info
    const unsigned int m_Width;
    const unsigned int m_Height;
    // Terrain Info
    const unsigned int m_MaxElevation;
    const unsigned int m_WaterLevel;

    // Map Data
    Tile* m_Tiles;
};

#endif