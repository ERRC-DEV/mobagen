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

  // Erosion constants

public:
  std::vector<Color32> Generate(int sideSize, float displacement = 0) override;
  std::string GetName() override;

};

#endif //ETHANSGENERATOR_H
