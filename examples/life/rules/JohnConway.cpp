#include "JohnConway.h"

#include <imgui.h>

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement
  int bounds = world.SideSize();

  for (int i = 0; i < bounds; i++)
  {
    for (int j = 0; j < bounds; j++)
    {
      int numAlive = CountNeighbors(world, Point2D (i, j));
      if (world.Get(Point2D (i, j)))
      {
        if (numAlive < 2)
        {
          world.SetNext(Point2D (i, j), false);
        }
        else if (numAlive > 3)
        {
          world.SetNext(Point2D (i, j), false);
        }
        else
        {
          world.SetNext(Point2D (i, j), true);
        }
      }
      else
      {
        if (numAlive < 3)
        {
          world.SetNext(Point2D (i, j), false);
        }
        else
        {
          world.SetNext(Point2D (i, j), true);
        }
      }
    }
  }

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
      if (i == 0 && j == 0)
      {
        continue;
      }
      neighbors[neighborNumber] = world.Get(Point2D(point.x + i, point.y + j));
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
