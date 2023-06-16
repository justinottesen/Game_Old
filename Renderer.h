#ifndef __RENDERER_H
#define __RENDERER_H

#include "Error.h"
#include "Map.h"

class Renderer {
  public:
    Renderer(const Map* map) : m_Map(map) {}
    virtual ~Renderer() {};

    virtual game_error_t draw() const = 0;

  protected:
    const Map* m_Map;
};

#endif