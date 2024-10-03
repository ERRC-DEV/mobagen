#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this
  Point2D startPoint;
  if (stack.empty())
  {
    startPoint = randomStartPoint(w);
  }
  else
  {
    startPoint = stack.back();
  }

  std::vector<Point2D> visitables = getVisitables(w, startPoint);
  if (visitables.empty())
  {
    stack.pop_back();
  }

  return false;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  // todo: implement this
  // Check North
  if (!(p.x+1 > sideOver2))
  {
    if (!visited[p.x+1][p.y])
    {
      visitables.push_back(Point2D(p.x + 1, p.y));
    }
  }
  // Check South
  if (!(p.x-1 < -sideOver2))
  {
    if (!visited[p.x-1][p.y])
    {
      visitables.push_back(Point2D(p.x - 1, p.y));
    }
  }
  // Check East
  if (!(p.y+1 > sideOver2))
  {
    if (!visited[p.x][p.y+1])
    {
      visitables.push_back(Point2D(p.x, p.y + 1));
    }
  }
  // Check West
  if (!(p.y-1 < -sideOver2))
  {
    if (!visited[p.x][p.y-1])
    {
      visitables.push_back(Point2D(p.x, p.y - 1));
    }
  }


  return visitables;
}
