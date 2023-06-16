#ifndef __ASCII_COLORS_H
#define __ASCII_COLORS_H

#include <iostream>


class ASCIIColor256 {
  public:
    enum Color {
      BLACK = 0,  MAROON,  GREEN,  OLIVE,   NAVY,  PURPLE,   TEAL,  SILVER,
      GRAY,       RED,     LIME,   YELLOW,  BLUE,  MAGENTA,  CYAN,  WHITE
    };
    enum Mode { TEXT = 3, HIGHLIGHT };

    static const char* RESET() { return "\033[0m"; }

    typedef int Grayscale;

    ASCIIColor256(Grayscale g, Mode m);
    ASCIIColor256(Color c, Mode m);
    ASCIIColor256(int r, int g, int b, Mode m);

    friend std::ostream& operator<<(std::ostream& ostr, const ASCIIColor256& color);
  
  private:

    int m_Color;
    Mode m_Mode;
};

std::ostream& operator<<(std::ostream& ostr, const ASCIIColor256& color);

#endif