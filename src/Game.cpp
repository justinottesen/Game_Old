#include "Game.h"

#include "ASCIIRenderer.h"

Game::Game() : m_Map(new Map()), 
               m_Renderer(new ASCIIRenderer(m_Map, 200, 50, 0, 0))
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