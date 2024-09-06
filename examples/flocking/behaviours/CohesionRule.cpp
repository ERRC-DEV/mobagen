#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood

  // find center of mass

  Vector2f centerPosition = Vector2f::zero();
  int numneighbors = neighborhood.size();

  for (Boid* neighbor : neighborhood)
  {
    if (neighbor->getPosition().x == boid->getPosition().x && neighbor->getPosition().y == boid->getPosition().y)
    {
      continue;
    }
    else
    {

    }
  }

  return cohesionForce;
}