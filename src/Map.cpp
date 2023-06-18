#include "Map.h"
#include "PerlinGenerator.h"

#include <cstring>
#include <cstdlib>

Map::Map(const Parameters& params) : m_ChunkSize(params.chunkSize),
                                     m_ElevationGenerator(params.seed),
                                     m_PerlinZoom(params.perlinZoom),
                                     m_MaxElevation(params.maxElevation),
                                     m_WaterLevel(params.waterLevel)
{

}

const Map::Tile& Map::getTile(int x, int y) const {
  int chunkX = x / static_cast<int>(m_ChunkSize);
  if (x < 0) { chunkX--; }
  int chunkY = y / static_cast<int>(m_ChunkSize);
  if (y < 0) { chunkY--; }

  int xInChunk = x % static_cast<int>(m_ChunkSize);
  int yInChunk = y % static_cast<int>(m_ChunkSize);
  // Mod with negative is not defined by C++ standard, sanity check
  if (xInChunk < 0) { xInChunk += m_ChunkSize; }
  if (yInChunk < 0) { yInChunk += m_ChunkSize; }
  if (m_Chunks.count(std::make_pair(chunkX, chunkY)) == 0) {
    m_Chunks[std::make_pair(chunkX, chunkY)] 
      = std::make_unique<Chunk>(chunkX, chunkY, m_ElevationGenerator, m_PerlinZoom, 
                                m_ChunkSize, m_MaxElevation, m_WaterLevel);
  }
  return m_Chunks[std::make_pair(chunkX, chunkY)]->getTile(xInChunk, yInChunk);
}

Map::Chunk::Chunk(unsigned int chunkX,
                  unsigned int chunkY,
                  const PerlinGenerator& perlinGenerator,
                  unsigned int perlinZoom,
                  unsigned int chunkSize,
                  unsigned int maxElevation,
                  unsigned int waterLevel) : m_Size(chunkSize),
                                             m_Tiles(std::make_unique<Tile[]>(chunkSize * chunkSize)) {
  for (unsigned int i = 0; i < chunkSize * chunkSize; i++) {
    int x = i % chunkSize + chunkX * chunkSize;
    int y = i / chunkSize + chunkY * chunkSize;

    float noise_x = static_cast<float>(x) / perlinZoom;
    float noise_y = static_cast<float>(y) / perlinZoom;

    m_Tiles[i].elevation = (perlinGenerator(noise_x, noise_y) + 1) * (maxElevation/2);
    m_Tiles[i].type = (m_Tiles[i].elevation < waterLevel) ? Tile::WATER : Tile::LAND;
  }
}