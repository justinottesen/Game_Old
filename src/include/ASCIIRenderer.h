#ifndef __ASCII_RENDERER_H
#define __ASCII_RENDERER_H

#include "Renderer.h"
#include "ASCIIColors.h"

class ASCIIRenderer : public Renderer {
  public:
    ASCIIRenderer(const Map* map) : Renderer(map) {}

    game_error_t draw();
  private:

    void setColor(Color color, ColorMode mode) { std::cout << ASCIIColor256(color, mode); }
    void setColor(const ASCIIColor256& color) { std::cout << color; }
    void resetColor() { std::cout << ASCIIColor256::RESET(); }

    const char* asciiScale = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";

    char getAscii(unsigned int val, unsigned int max, bool reverse);
};

#endif