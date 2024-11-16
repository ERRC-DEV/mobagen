//
// Created by ethan on 11/7/2024.
//

#include "EthansGenerator.h"
#include "Random.h"
#include <iostream>
#include <iomanip>

//#include "glm/gtx/compatibility.hpp"

std::vector<Color32> EthansGenerator::Generate(int sideSize, float displacement) {
  if (sideSize != sideSizeCached) {
    sideSizeCached = sideSize;
    generateElevationMap();
    // set timestamp of last/first update
  } else {
    // get time difference
    // run erode with the dt
  }

  return heightsToColor();
}

void EthansGenerator::generateElevationMap() {
  FastNoiseLite base;
  base.SetFractalOctaves(2);
  base.SetSeed(28); //This number has no meaning except that it is my boyfriend's favorite number
  base.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
  const float FREQUENCY_HIGH = 4.0f, FREQUENCY_LOW = 1.0f, TOTAL_AMPLITUDE = 1.25f, X_OFFSET = 50.0f, Y_OFFSET = 50.0f, REDISTRIBUTION_EXPONENT = 1.5f, LERP_MIX = 0.4f;


  for (int y = 0; y < sideSizeCached; y++) {
    for (int x = 0; x < sideSizeCached; x++) {
      double nx = x/sideSizeCached - 0.5, ny = y/sideSizeCached - 0.5;
      // Calculate elevation
      // Merge a high and low frequency generation to create a new result
      float elevation = (base.GetNoise(FREQUENCY_LOW*nx, FREQUENCY_LOW*ny) + (.25f * base.GetNoise(FREQUENCY_HIGH*nx + X_OFFSET , FREQUENCY_HIGH*ny + Y_OFFSET)));
      elevation /= TOTAL_AMPLITUDE;
      elevation = pow(elevation, REDISTRIBUTION_EXPONENT);

      // Force islands
      float distance = 1 - (1-(nx*nx)) * (1-(ny*ny));

      elevation = std::lerp(elevation, 1-distance, LERP_MIX);

      elevationMap[x][y] = elevation;
    }
  }

}
std::vector<Color32> EthansGenerator::heightsToColor()
{
  std::vector<Color32> colors;
  for (int y = 0; y < sideSizeCached; y++) {
    for (int x = 0; x < sideSizeCached; x++) {

      float elevation = elevationMap[y][x];
      if (elevation < 0.3)
        colors.push_back(Color32::LerpColor(Color::DarkBlue, Color::Blue, elevation / 0.3f));
      else if (elevation < 0.5)
        colors.push_back(Color32::LerpColor(Color::Blue, Color::Green, (elevation - 0.3f) / 0.2f));
      else if (elevation < 0.7)
        colors.push_back(Color32::LerpColor(Color::Green, Color::SandyBrown, (elevation - 0.5f) / 0.2f));
      else if (elevation < 0.8)
        colors.push_back(Color32::LerpColor(Color::SandyBrown, Color::Gray, (elevation - 0.7f) / 0.1f));
      else
        colors.push_back(Color32::LerpColor(Color::Gray, Color::White, (elevation - 0.8f) / 0.2f));
    }
  }
  return colors;
}

std::string EthansGenerator::GetName() { return "EthanGenerator"; }