#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

  float desiredDistance = desiredMinimalDistance;

  for (Boid* neighbor : neighborhood)
  {
    if (neighbor->getPosition().x == boid->getPosition().x && neighbor->getPosition().y == boid->getPosition().y)
    {
      continue;
    }
    else
    {
      Vector2f direction = neighbor->getPosition() - boid->getPosition();
      float distance = sqrt( direction.x * direction.x + direction.y * direction.y );
      if (desiredDistance <= distance)
      {
        continue;
      }
      Vector2f hat = {direction.x / distance, direction.y / distance};
      float strength = 1/distance;
      separatingForce -= (hat * strength);
    }
    Vector2f distance = neighbor->getPosition() - boid->getPosition();
  }
  //
  //    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
  //    if (!neighborhood.empty()) {
  //        Vector2f position = boid->transform.position;
  //        int countCloseFlockmates = 0;
  //        // todo: find and apply force only on the closest mates
  //    }

  separatingForce = Vector2f::normalized(separatingForce);

  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
