#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood

  // find center of mass

  Vector2f centerPosition = Vector2f::zero();
  Vector2f direction = Vector2f::zero();
  int numneighbors = neighborhood.size();


  if (numneighbors > 0)
    {

    for (Boid* neighbor : neighborhood)
    {
      if (neighbor->getPosition().x == boid->getPosition().x && neighbor->getPosition().y == boid->getPosition().y)
      {
        continue;
      }

      centerPosition += neighbor->getPosition();
    }

    centerPosition /= numneighbors;
    direction = centerPosition - boid->getPosition();
    float distance;
    if (direction == Vector2f::zero())
    {
      distance = .000000000000000000001f;
    }
    else
    {
      float distance = sqrt( direction.x * direction.x + direction.y * direction.y );
    }

    Vector2f hat = {direction.x / distance, direction.y / distance};
    float strength = distance/boid->getDetectionRadius();
    cohesionForce = (hat * distance);
    }

  return Vector2f::normalized(cohesionForce);
}