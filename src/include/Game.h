#ifndef __GAME_H
#define __GAME_H

#include "Map.h"
#include "Renderer.h"

class Game {
  public:
    Game();

    void run();

  private:
    std::unique_ptr<Map> m_Map;
    std::unique_ptr<Renderer> m_Renderer;
};

#endif