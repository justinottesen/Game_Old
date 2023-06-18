#ifndef __MAP_H
#define __MAP_H

#include "PerlinGenerator.h"

#include <iostream>
#include <unordered_map>
#include <cassert>
#include <vector>
#include <memory>

// Pair requires hash function
template <class T>
struct PairHash
{
    std::size_t operator()(std::pair<T, T> const& p) const noexcept
    {
        std::size_t h1 = std::hash<T>{}(p.first);
        std::size_t h2 = std::hash<T>{}(p.second);
        return h1 ^ (h2 << 1); // or use boost::hash_combine
    }
};

struct MapParameters {
  // Terrain Generation Parameters
  unsigned int seed                 = 42069; //= std::time(NULL);
  unsigned int perlinZoom           = 10;
  unsigned int maxElevation         = 100;
  unsigned int waterLevel           = 45;
  // Internals
  unsigned int chunkSize            = 256;
};

class Map {
  class Chunk;    // Forward declaration for friend declaration in Tile

  public:
    struct Tile {   // TODO: FIND WAY TO MAKE THIS SAFER
      public:
        enum Type { WATER, LAND };

        unsigned int  elevation;      // Value 0 - Max Elevation
        Type          type;           // Dependant on Elevation
      private:
    };

  private:
    // Internal class for chunking
    class Chunk {
      public:
        // Chunks cannot be copied (destructor breaks tile array)
        Chunk(const Chunk&) = delete;
        Chunk& operator=(const Chunk&) = delete;

        Chunk(unsigned int chunkX,
              unsigned int chunkY,
              const PerlinGenerator& perlinGenerator,
              unsigned int perlinZoom,
              unsigned int chunkSize,
              unsigned int maxElevation,
              unsigned int waterLevel);

        const Tile& getTile(unsigned int x, unsigned int y) const { assert(x < m_Size); assert(y < m_Size); return m_Tiles[y*m_Size + x]; }
      
      private:
        unsigned int m_Size;
        std::unique_ptr<Tile[]> m_Tiles;
    };
  
  public:
    typedef MapParameters Parameters;

    Map(const Parameters& params = Parameters());

    // ONLY OUTSIDE ACCESS TO TILES, ensures READ ONLY access
    const Tile& getTile(int x, int y) const;

    unsigned int maxElevation() const { return m_MaxElevation; }
    unsigned int waterLevel() const { return m_WaterLevel; }

  private:
    typedef std::unordered_map<std::pair<int, int>, std::unique_ptr<Chunk>, PairHash<int>> ChunkHashTable;

    // Map Info
    unsigned int m_ChunkSize;
    // Allows new chunks to load in even in const context
    mutable ChunkHashTable m_Chunks;
    PerlinGenerator m_ElevationGenerator;
    unsigned int m_PerlinZoom;

    // Terrain Info
    const unsigned int m_MaxElevation;
    const unsigned int m_WaterLevel;
};

#endif