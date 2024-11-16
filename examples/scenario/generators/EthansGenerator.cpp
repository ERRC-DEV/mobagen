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
  FastNoiseLite base = FastNoiseLite(FastNoiseLite::NoiseType_Perlin);
  //base.SetFractalOctaves(2);
  //base.SetFrequency(4.0f);
  //base.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
  //base = FastNoiseLite(FastNoiseLite::NoiseType_Perlin);
  const float FREQUENCY_HIGH = 4.0f, FREQUENCY_LOW = 1.0f, TOTAL_AMPLITUDE = 1.25f, X_OFFSET = 0.0050f, Y_OFFSET = 0.0050f, REDISTRIBUTION_EXPONENT = 1.5f, LERP_MIX = 0.4f;

  for (int y = 0; y < sideSizeCached; y++) {
    for (int x = 0; x < sideSizeCached; x++) {
      double nx = x/sideSizeCached, ny = y/sideSizeCached;
      // Calculate elevation
      // Merge a high and low frequency generation to create a new result
      float test = base.GetNoise(nx,ny);
      //float elevation = (base.GetNoise(FREQUENCY_LOW*nx, FREQUENCY_LOW*ny) + (.25f * base.GetNoise(FREQUENCY_HIGH*nx + X_OFFSET , FREQUENCY_HIGH*ny + Y_OFFSET)));
      //elevation /= TOTAL_AMPLITUDE;
      //elevation = pow(elevation, REDISTRIBUTION_EXPONENT);

      // Testing
      elevationMap[y][x] = test;

      // Force islands
      float distance = 1 - (1-(nx*nx)) * (1-(ny*ny));

      //elevation = std::lerp(elevation, 1-distance, LERP_MIX);

      //elevationMap[x][y] = elevation;
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
        colors.push_back(Color32::LerpColor(Color::SandyBrown, Color::Red, (elevation - 0.7f) / 0.1f));
      else
        colors.push_back(Color32::LerpColor(Color::Red, Color::White, (elevation - 0.8f) / 0.2f));
    }
  }
  return colors;
}

void EthansGenerator::doErosion(float dt)
{

}


std::string EthansGenerator::GetName() { return "EthanGenerator"; }