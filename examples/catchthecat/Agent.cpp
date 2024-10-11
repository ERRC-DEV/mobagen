#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;

struct ASNode {
  Point2D point;
  int accDist;
  int heuristicDist;

  //operator < is overloaded to me used in a priority queue
  bool operator<(const ASNode &rhs) const {
    return accDist + heuristicDist > rhs.accDist + rhs.heuristicDist;
  }
};

int Agent::getHeuristic(Point2D point, int sideSize) {
  if (point.x == 0 && point.y == 0) {
    return sideSize/2;
  }
  if(point.x + point.y > 0) {
    if(point.x - point.y > 0) {
      return (sideSize / 2) - point.x;
    }
    else if(point.x - point.y < 0) {
      return (sideSize / 2) - point.y;
    }
  }
  else if(point.x + point.y < 0) {
    if (point.x - point.y > 0) {
      return (-sideSize / 2) + point.y;
    }
    else if(point.x - point.y < 0) {
      return (-sideSize / 2) + point.x;
    }
  }
}

std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  priority_queue<ASNode> queue;                   // to store next ones to visit
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat();
  queue.push({catPos, 0, w->getWorldSideSize()/2});
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!queue.empty()) {
    // get the current from frontier
    auto current = queue.top();
    queue.pop();
    visited[current.point] = true;
    std::vector<Point2D> neighbors = getVisitableNeighbors(w, catPos);
    // iterate over the neighs:
    for (auto neighbor : neighbors) {
      if (!visited[neighbor]) {
        // Push to the queue
        cameFrom.emplace(neighbor, current.point);
        // just push them all, it is automatically sorted
      }
    }
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return vector<Point2D>();
}

std::vector<Point2D> Agent::getVisitableNeighbors(World* w, Point2D p) {
  vector<Point2D> neighbors;
  Point2D nextPoint = w->NE(p);
  if (w->isValidPosition(nextPoint) && w->catCanMoveToPosition(nextPoint)) {
    neighbors.push_back(nextPoint);
  }
  nextPoint = w->NW(p);
  if (w->isValidPosition(nextPoint) && w->catCanMoveToPosition(nextPoint)) {
    neighbors.push_back(nextPoint);
  }
  nextPoint = w->E(p);
  if (w->isValidPosition(nextPoint) && w->catCanMoveToPosition(nextPoint)) {
    neighbors.push_back(nextPoint);
  }
  nextPoint = w->W(p);
  if (w->isValidPosition(nextPoint) && w->catCanMoveToPosition(nextPoint)) {
    neighbors.push_back(nextPoint);
  }
  nextPoint = w->SW(p);
  if (w->isValidPosition(nextPoint) && w->catCanMoveToPosition(nextPoint)) {
    neighbors.push_back(nextPoint);
  }
  nextPoint = w->SE(p);
  if (w->isValidPosition(nextPoint) && w->catCanMoveToPosition(nextPoint)) {
    neighbors.push_back(nextPoint);
  }


  return neighbors;
}
