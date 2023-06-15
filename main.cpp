#include "Map.h"

#include <iostream>

int main()
{
  Map::Parameters ps;

  Map map(ps);
  map.printAscii(std::cout);

  return EXIT_SUCCESS;
}
