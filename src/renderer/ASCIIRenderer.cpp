#include "ASCIIRenderer.h"

#include <cstring>

game_error_t ASCIIRenderer::draw()
{
  std::cout << std::string(m_Map->width() + 2, '-') << std::endl;
  for (unsigned int y = 0; y < m_Map->height(); y++) {
    std::cout << "|";
    for (unsigned int x = 0; x < m_Map->width(); x++) {
      if (m_Map->getTile(x, y).elevation > 50) {
        setColor(OLIVE, BG);
      } else if (m_Map->getTile(x, y).elevation > 0) {
        setColor(GREEN, BG);
      } else if (m_Map->getTile(x, y).elevation > -5) {
        setColor(BLUE, BG);
      } else {
        setColor(NAVY, BG);
      }
      std::cout << " ";
    }
    resetColor();
    std::cout << "|" << std::endl;
  }
  std::cout << std::string(m_Map->width() + 2, '-') << std::endl;
  return ERROR_NONE;
}

char ASCIIRenderer::getAscii(unsigned int val, unsigned int max, bool reverse = false) {
  if (reverse) { val = max - val; }
  return asciiScale[(val * (strlen(asciiScale)-1)) / max];
}