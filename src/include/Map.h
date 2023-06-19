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

namespace MapParams {
  const unsigned int    chunkSize          = 256;
  const unsigned int    perlinZoomWater    = 100;
};

class Map {
  class Chunk;    // Forward declaration for friend declaration in Tile

  public:
    struct Tile {   // TODO: FIND WAY TO MAKE THIS SAFER
      public:
        enum Type { LAND, WATER };
        Type          type;
    };

  private:
    // Internal class for chunking
    class Chunk {
      public:
        Chunk(int chunkX, int chunkY, unsigned int seed);

        const Tile& getTile(int x, int y) const { return m_Tiles[y*MapParams::chunkSize + x]; }
      
      private:
        std::array<Tile, MapParams::chunkSize * MapParams::chunkSize> m_Tiles;
    };
  
  public:

    Map(unsigned int seed = 690240);

    // ONLY OUTSIDE ACCESS TO TILES, ensures READ ONLY access
    const Tile& getTile(int x, int y) const;

  private:
    typedef std::unordered_map<std::pair<int, int>, std::unique_ptr<Chunk>, PairHash<int>> ChunkHashTable;

    unsigned int m_Seed;
    mutable ChunkHashTable m_Chunks;          // Allows new chunks to load in even in const context
};

#endif