#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();

  // todo: add your code here to align each boid in a neighborhood
  // hint: iterate over the neighborhood


  int numneighbors = neighborhood.size();


  if (numneighbors > 0)
  {
    for (Boid* neighbor : neighborhood)
    {
      if (neighbor->getPosition().x == boid->getPosition().x && neighbor->getPosition().y == boid->getPosition().y)
      {
        numneighbors--;
        continue;
      }

      averageVelocity += neighbor->getVelocity();
    }
    averageVelocity /= numneighbors;

  }


  return Vector2f::normalized(averageVelocity);
}