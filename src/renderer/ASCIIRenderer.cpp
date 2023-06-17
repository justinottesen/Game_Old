#include "ASCIIRenderer.h"

#include <cstring>

game_error_t ASCIIRenderer::draw()
{
  std::cout << std::string(m_ViewWidth + 2, '-') << std::endl;
  for (unsigned int y = m_ViewY; y < m_ViewY + m_ViewHeight; y++) {
    std::cout << "|";
    for (unsigned int x = m_ViewX; x < m_ViewX + m_ViewWidth; x++) {
      const Map::Tile& t = m_Map->getTile(x, y);
      // SET HIGHLIGHT COLOR
      switch (t.type) {
        case Map::Tile::LAND:
          setColor(ASCIIColor256(0, 3, 1, ASCIIColor256::HIGHLIGHT));
          break;
        case Map::Tile::WATER:
          setColor(ASCIIColor256(0, 2, 4, ASCIIColor256::HIGHLIGHT));
          break;
      }
      // TODO: SET TEXT COLOR
      // TODO: SET TEXT VALUE
      std::cout << " ";
    }
    resetColor();
    std::cout << "|" << std::endl;
  }
  std::cout << std::string(m_ViewWidth + 2, '-') << std::endl;
  return ERROR_NONE;
}

char ASCIIRenderer::getAscii(unsigned int val, unsigned int max, bool reverse = false) {
  if (reverse) { val = max - val; }
  return asciiScale[(val * (strlen(asciiScale)-1)) / max];
}