#include "ASCIIColors.h"

#include <cassert>

ASCIIColor256::ASCIIColor256(Grayscale g, Mode m) : m_Mode(m) {
  assert(0 <= g && g <= 100);
  g /= 4;
  switch (g) {
    case 0:     m_Color = BLACK;      break;
    case 25:    m_Color = WHITE;      break;
    default:    m_Color = g + 231;    break;
  }
}

ASCIIColor256::ASCIIColor256(Color c, Mode m) : m_Color(c), m_Mode(m) {}

ASCIIColor256::ASCIIColor256(int r, int g, int b, Mode m) : m_Color(16 + 36*r + 6*g + b), m_Mode(m) {
  assert(0 <= r && r < 6); assert(0 <= g && g < 6); assert(0 <= b && b < 6);
}

std::ostream& operator<<(std::ostream& ostr, const ASCIIColor256& color) {
  ostr << "\033[" << color.m_Mode << "8;5;" << color.m_Color << "m";
  return ostr;
}