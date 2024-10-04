#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this
  auto sideSideOver2 = w->GetSize()/2;

  if (stack.empty() && visited[-sideSideOver2][-sideSideOver2] == false)
  {
    stack.push_back({-sideSideOver2, -sideSideOver2});
    w->SetNodeColor({-sideSideOver2,-sideSideOver2}, Color::Red);
    visited[-sideSideOver2][-sideSideOver2] = true;
    return true;
  }

  if (stack.empty())
  {
    return false;
  }

  auto currentPoint = stack.back();
  std::vector<Point2D> visitables = getVisitables(w, currentPoint);
  if (visitables.empty()) {
    w->SetNodeColor(stack.back(), Color::Black);
    stack.pop_back();
    return true;
  }
  int randomNumber = w->GetRand();
  randomNumber = randomNumber % visitables.size();
  Point2D visitable = visitables[randomNumber];
  stack.push_back(visitable);
  w->SetNodeColor(visitable, Color::Red);
  if (currentPoint.Up() == visitable)
  {
    //visitables[randomNumber]
    //w->SetNodeColor(visitable, Color::Red);
    w->SetNorth(currentPoint, false);
  }
  if (currentPoint.Down() == visitable)
  {
    //w->SetNodeColor(visitable, Color::Red);
    w->SetSouth(currentPoint, false);
  }
  if (currentPoint.Left() == visitable)
  {
    //w->SetNodeColor(visitable, Color::Red);
    w->SetWest(currentPoint, false);
  }
  if (currentPoint.Right() == visitable)
  {
    //w->SetNodeColor(visitable, Color::Red);
    w->SetEast(currentPoint, false);
  }

  visited[visitable.x][visitable.y] = true;
  return true;
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
