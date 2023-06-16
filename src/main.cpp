#include "Game.h"

#include <iostream>

#include <ctime>

int main()
{
  std::srand(std::time(NULL));

  Game g;

  g.run();

  return EXIT_SUCCESS;
}
