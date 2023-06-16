#ifndef __ASCII_COLORS_H
#define __ASCII_COLORS_H

#include <iostream>

enum Color {
  BLACK = 0,
  MAROON,
  GREEN,
  OLIVE,
  NAVY,
  PURPLE,
  TEAL,
  SILVER,
  GRAY,
  RED,
  LIME,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE
};

enum ColorMode { TXT = 3, BG };

class ASCIIColor256 {
  public:

    static const char* RESET() { return "\033[0m"; }

    typedef int grayscale;

    ASCIIColor256(grayscale g, ColorMode m);
    ASCIIColor256(Color c, ColorMode m);
    ASCIIColor256(int r, int g, int b, ColorMode m);

    friend std::ostream& operator<<(std::ostream& ostr, const ASCIIColor256& color);
  
  private:

    int m_Color;
    ColorMode m_Mode;
};

std::ostream& operator<<(std::ostream& ostr, const ASCIIColor256& color);

#endif