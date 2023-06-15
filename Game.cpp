#include "Game.h"

Game::Game() : m_Map(new Map()), 
               m_Renderer(new ASCIIRenderer(m_Map))
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