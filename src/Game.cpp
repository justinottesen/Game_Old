#include "Game.h"

#include "ASCIIRenderer.h"

Game::Game() : m_Map(std::make_unique<Map>()), 
               m_Renderer(std::make_unique<ASCIIRenderer>(m_Map.get(), 200, 50, 0, 0))
{
  
}

void Game::run()
{
  m_Renderer->draw();
}