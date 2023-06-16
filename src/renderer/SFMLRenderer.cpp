#include "SFMLRenderer.h"

#include <SFML/Graphics.hpp>

SFMLRenderer::SFMLRenderer(const Map* map) : Renderer(map) {
  sf::Window window(sf::VideoMode(800, 600), "My window");
}

game_error_t SFMLRenderer::draw() {
  return ERROR_NONE;
}