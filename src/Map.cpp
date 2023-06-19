#include "Map.h"
#include "PerlinGenerator.h"

#include <cstring>
#include <cstdlib>

Map::Map(unsigned int seed) : m_Seed(seed)
{

}

const Map::Tile& Map::getTile(int x, int y) const {
  int chunkX = x / static_cast<int>(MapParams::chunkSize);
  if (x < 0 && x % MapParams::chunkSize != 0) { chunkX--; }
  int chunkY = y / static_cast<int>(MapParams::chunkSize);
  if (y < 0 && y % MapParams::chunkSize != 0) { chunkY--; }

  int xInChunk = x % static_cast<int>(MapParams::chunkSize);
  int yInChunk = y % static_cast<int>(MapParams::chunkSize);
  // Mod with negative is not defined by C++ standard, sanity check
  if (xInChunk < 0) { xInChunk += MapParams::chunkSize; }
  if (yInChunk < 0) { yInChunk += MapParams::chunkSize; }
  if (m_Chunks.count(std::make_pair(chunkX, chunkY)) == 0) {
    m_Chunks[std::make_pair(chunkX, chunkY)] 
      = std::make_unique<Chunk>(chunkX, chunkY, m_Seed);
  }
  return m_Chunks[std::make_pair(chunkX, chunkY)]->getTile(xInChunk, yInChunk);
}

Map::Chunk::Chunk(int chunkX, int chunkY, unsigned int seed) {
  PerlinGenerator waterGen(seed);
  std::srand((chunkX + seed) * (chunkY + seed));
  for (unsigned int i = 0; i < MapParams::chunkSize * MapParams::chunkSize; i++) {
    int xInChunk = i % MapParams::chunkSize;
    int yInChunk = i / MapParams::chunkSize;

    int x = xInChunk + chunkX * MapParams::chunkSize;
    int y = yInChunk + chunkY * MapParams::chunkSize;

    float lakeNoise_x = static_cast<float>(x) / MapParams::perlinZoomWater;
    float lakeNoise_y = static_cast<float>(y) / MapParams::perlinZoomWater;

    if (waterGen.sample(lakeNoise_x, lakeNoise_y) < -0.2) {
      m_Tiles[i].type = Tile::WATER;
    } else {
      m_Tiles[i].type = Tile::LAND;
    }
  }
}