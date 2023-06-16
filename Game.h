#ifndef __GAME_H
#define __GAME_H

#include "Map.h"
#include "Renderer.h"

class Game {
  public:
    Game();

    void run();

    ~Game();

  private:
    Map* m_Map;
    Renderer* m_Renderer;
};

#endif