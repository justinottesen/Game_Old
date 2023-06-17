#ifndef __MAP_H
#define __MAP_H

#include "PerlinGenerator.h"

#include <iostream>
#include <unordered_map>
#include <cassert>
#include <vector>

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
    class Tile {
      public:
        Tile(const Tile&) = delete;       // Tiles can ONLY be created by chunks
        Tile& operator=(const Tile&) = delete;

        enum Type { WATER, LAND };

        unsigned int  elevation;      // Value 0 - Max Elevation
        Type          type;           // Dependant on Elevation
      private:
        Tile() {} friend Map::Chunk;  // Tiles can ONLY be created by chunks
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
        ~Chunk() { delete [] m_Tiles; }

        const Tile& getTile(unsigned int x, unsigned int y) const { assert(x < m_Size); assert(y < m_Size); return m_Tiles[y*m_Size + x]; }
      
      private:
        unsigned int m_Size;
        Tile* m_Tiles;
    };
  
  public:
    typedef MapParameters Parameters;

    Map(const Parameters& params = Parameters());
    ~Map() { for (unsigned int i = 0; i < m_Chunks.size(); i++) { delete m_Chunks[i]; } }

    // ONLY OUTSIDE ACCESS TO TILES, ensures READ ONLY access
    const Tile& getTile(int x, int y) const;

    unsigned int maxElevation() const { return m_MaxElevation; }
    unsigned int waterLevel() const { return m_WaterLevel; }

  private:
    typedef std::unordered_map<std::pair<int, int>, Chunk*, PairHash<int>> ChunkHashTable;

    // Map Info
    unsigned int m_ChunkSize;
    // Allows new chunks to load in even in const context
    mutable ChunkHashTable m_ChunkMap;
    mutable std::vector<Chunk*> m_Chunks; // OWNER OF CHUNKS
    PerlinGenerator m_ElevationGenerator;
    unsigned int m_PerlinZoom;

    // Terrain Info
    const unsigned int m_MaxElevation;
    const unsigned int m_WaterLevel;
};

#endif