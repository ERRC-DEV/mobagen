#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  // todo: implement
  bool neighbors[8];
  int neighborNumber = 0;
  int numNeighbors = 0;
  for (int i = -1; i < 2; i++)
  {
    for (int j = -1; j < 2; j++)
    {
      neighbors[neighborNumber] = world.Get(Point2D(point.x+i, point.y+j));
      neighborNumber++;
    }
  }
  for (int i = 0; i < 8; i++)
  {
    if (neighbors[i])
    {
      numNeighbors++;
    }
  }

  return numNeighbors;
}
