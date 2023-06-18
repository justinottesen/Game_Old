#ifndef __ASCII_RENDERER_H
#define __ASCII_RENDERER_H

#include "Renderer.h"
#include "ASCIIColors.h"

class ASCIIRenderer : public Renderer {
  public:
    ASCIIRenderer(const Map* map, 
                  unsigned int viewWidth, unsigned int viewHeight,
                  int viewX, int viewY) : Renderer(map), 
                                          m_ViewWidth(viewWidth),
                                          m_ViewHeight(viewHeight),
                                          m_ViewX(viewX),
                                          m_ViewY(viewY) {}

    game_error_t draw();
  private:
    void setColor(ASCIIColor256::Color color, ASCIIColor256::Mode mode) 
      { std::cout << ASCIIColor256(color, mode); }
    void setColor(const ASCIIColor256& color) { std::cout << color; }
    void resetColor() { std::cout << ASCIIColor256::RESET(); }

    const char* asciiScale = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";

    char getAscii(unsigned int val, unsigned int max, bool reverse);

    unsigned int m_ViewWidth;
    unsigned int m_ViewHeight;

    int m_ViewX;
    int m_ViewY;
};

#endif