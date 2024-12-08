//
// Created by ethan on 11/7/2024.
//

#ifndef ETHANSGENERATOR_H
#define ETHANSGENERATOR_H
#define GLM_ENABLE_EXPERIMENTAL

#include "../GeneratorBase.h"
#include <glm/vec3.hpp>
#include <glm/gtx/normal.hpp>
#include "../PerlinNoise.hpp"
#include "../FastNoiseLite.h"

class EthansGenerator : public ScenarioGeneratorBase {
private:
  float elevationMap[2048][2048];
  int sideSizeCached = 0;
  float timeOfLastUpdate = 0;
  std::vector<Color32> heightsToColor();
  void generateElevationMap(float displacement);
  void doErosion(float dt);
  glm::vec3 getSurfaceNormal(int x, int y);

  // Erosion constants
  float minVol = 0.01;
  float density = 1;
  float friction = 0.05;
  float depositionRate = 0.1;
  float evapRate = 0.001;
public:
  std::vector<Color32> Generate(int sideSize, float displacement = 0) override;
  std::string GetName() override;

};

struct WaterDroplet {
  // Construct Particle at Position
  WaterDroplet(glm::vec2 _pos) { pos = _pos; }

  glm::vec2 pos;
  glm::vec2 speed = glm::vec2(0.0);

  float volume = 1.0;    // This will vary in time
  float sediment = 0.0;  // Fraction of Volume that is Sediment!
};

#endif //ETHANSGENERATOR_H
