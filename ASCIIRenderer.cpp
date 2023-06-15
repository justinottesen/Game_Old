#include "ASCIIRenderer.h"

#define COLOR(txt_bg, col, bright) \
        std::cout << "\033[" txt_bg col bright "m"

// txt_bg
#define TXT      "3"
#define BG        "4"

// col
#define BLACK     "0"
#define RED       "1"
#define GREEN     "2"
#define YELLOW    "3"
#define BLUE      "4"
#define MAGENTA   "5"
#define CYAN      "6"
#define WHITE     "7"

// bright
#define BRIGHT    ";1"
#define NORMAL    ""


#define BG_COLOR(x)     std::cout << "\033"
#define RESET_COLOR     std::cout << "\033[0m"

game_error_t ASCIIRenderer::draw()
{
  std::cout << std::string(m_Map->width() + 2, '-') << std::endl;
  for (unsigned int y = 0; y < m_Map->height(); y++) {
    std::cout << "|";
    COLOR(TXT, BLUE, NORMAL);
    for (unsigned int x = 0; x < m_Map->width(); x++) {
      std::cout << getAscii(m_Map->getTile(x, y).food, 99, true);
    }
    RESET_COLOR;
    std::cout << "|" << std::endl;
  }
  std::cout << std::string(m_Map->width() + 2, '-') << std::endl;

  std::cout << std::endl;

  RESET_COLOR;
  return ERROR_NONE;
}

char ASCIIRenderer::getAscii(unsigned int val, unsigned int max, bool reverse = false) {
  if (reverse) { val = max - val; }
  return asciiScale[(val * (strlen(asciiScale)-1)) / max];
}