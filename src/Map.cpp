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
  int chunkY = y / static_cast<int>(m_ChunkSize);

  int xInChunk = x % static_cast<int>(m_ChunkSize);
  int yInChunk = y % static_cast<int>(m_ChunkSize);
  // Mod returning negative is implementation based, kind of annoying
  if (xInChunk < 0) { xInChunk += m_ChunkSize; }
  if (yInChunk < 0) { yInChunk += m_ChunkSize; }
  if (m_ChunkMap.count(std::make_pair(chunkX, chunkY)) == 0) {
    m_Chunks.push_back(new Chunk(chunkX, chunkY, m_ElevationGenerator, m_PerlinZoom, 
                                m_ChunkSize, m_MaxElevation, m_WaterLevel));
    m_ChunkMap[std::make_pair(chunkX, chunkY)] = m_Chunks.back();
  }
  return m_ChunkMap.find(std::make_pair(chunkX, chunkY))->second->getTile(xInChunk, yInChunk);
}

Map::Chunk::Chunk(unsigned int chunkX,
                  unsigned int chunkY,
                  const PerlinGenerator& perlinGenerator,
                  unsigned int perlinZoom,
                  unsigned int chunkSize,
                  unsigned int maxElevation,
                  unsigned int waterLevel) : m_Size(chunkSize),
                                             m_Tiles(new Tile[m_Size*m_Size]) {
  for (unsigned int i = 0; i < chunkSize * chunkSize; i++) {
    int x = i % chunkSize + chunkX * chunkSize;
    int y = i / chunkSize + chunkY * chunkSize;

    float noise_x = static_cast<float>(x) / perlinZoom;
    float noise_y = static_cast<float>(y) / perlinZoom;

    m_Tiles[i].elevation = (perlinGenerator(noise_x, noise_y) + 1) * (maxElevation/2);
    m_Tiles[i].type = (m_Tiles[i].elevation < waterLevel) ? Tile::WATER : Tile::LAND;
  }
}