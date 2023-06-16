#ifndef __SFML_RENDERER_H
#define __SFML_RENDERER_H

#include "Renderer.h"

class SFMLRenderer : public Renderer {
  public:
    SFMLRenderer(const Map* map);

    game_error_t draw() const;
  private:

};

#endif