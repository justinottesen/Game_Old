#include "Game.h"

#include "ASCIIRenderer.h"
#include "SFMLRenderer.h"

#if defined(RENDERER)
  typedef RENDERER _Renderer;
#else
  typedef ASCIIRenderer _Renderer;
#endif

Game::Game() : m_Map(new Map()), 
               m_Renderer(new _Renderer(m_Map))
{
  
}

void Game::run()
{
  m_Renderer->draw();
}

Game::~Game()
{
  delete m_Map;
  delete m_Renderer;
}