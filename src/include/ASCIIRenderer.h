#ifndef __ASCII_RENDERER_H
#define __ASCII_RENDERER_H

#include "Renderer.h"

class ASCIIRenderer : public Renderer {
  public:
    ASCIIRenderer(const Map* map) : Renderer(map) {}

    game_error_t draw() const;
  private:

    const char* asciiScale = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";

    char getAscii(unsigned int val, unsigned int max, bool reverse);
};

#endif