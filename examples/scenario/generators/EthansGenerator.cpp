//
// Created by ethan on 11/7/2024.
//

#include "EthansGenerator.h"
#include "Random.h"
#include <iostream>
#include <iomanip>

//#include "glm/gtx/compatibility.hpp"

std::vector<Color32> EthansGenerator::Generate(int sideSize, float time) {
  if (sideSize != sideSizeCached) {
    sideSizeCached = sideSize;
    generateElevationMap(time);
    // set timestamp of last/first update
    timeOfLastUpdate = time;
  } else {
    // get time difference
    // run erode with the dt
    float const dt = time - timeOfLastUpdate;
    timeOfLastUpdate = time;
  }

  return heightsToColor();
}

void EthansGenerator::generateElevationMap(float displacement)
{
  FastNoiseLite base = FastNoiseLite(FastNoiseLite::NoiseType_Perlin);
  //base.SetFractalOctaves(2);
  //base.SetFrequency(4.0f);
  //base.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
  //base = FastNoiseLite(FastNoiseLite::NoiseType_Perlin);
  const float FREQUENCY_HIGH = 4.0f, FREQUENCY_LOW = 1.0f, TOTAL_AMPLITUDE = 1.25f, X_OFFSET = 0.0050f, Y_OFFSET = 0.0050f, REDISTRIBUTION_EXPONENT = 1.0f, LERP_MIX = 0.5f;

  for (int y = 0; y < sideSizeCached; y++) {
    for (int x = 0; x < sideSizeCached; x++) {
      float nx = (2.0f*(float)x/(float)sideSizeCached)-1, ny = (2.0f*(float)y/(float)sideSizeCached)-1;
      // Calculate elevation
      // Merge a high and low frequency generation to create a new result
      //float elevation = base.GetNoise((float)(FREQUENCY_LOW*x), (float)(FREQUENCY_LOW*y), displacement);
      float elevation = (base.GetNoise((float)(FREQUENCY_LOW*x), (float)(FREQUENCY_LOW*y), displacement) + (.25f * base.GetNoise((float)(FREQUENCY_HIGH*x + X_OFFSET), (float)(FREQUENCY_HIGH*y + Y_OFFSET), displacement))) / TOTAL_AMPLITUDE;
      if (elevation < 0.0f)
      {
        elevation = abs(elevation);
      }

      elevation /= TOTAL_AMPLITUDE;
      elevation = pow(elevation, REDISTRIBUTION_EXPONENT);

      // Testing
      //elevationMap[y][x] = test;
      // Force islands
      // GOOD LORD FIX THE DISTANCE CALCULATION THIS LOOKS SO DAMN WRONG
      float distance = 1.0f - ((1.0f-(nx*nx)) * (1.0f-(ny*ny)));
      //float distance = 1.0f;
      //distance -= pow((((float)x-(float)sideSizeCached)*((float)x-(float)sideSizeCached)) * (((float)y-(float)sideSizeCached)*((float)y-(float)sideSizeCached)),0.5f);

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

void EthansGenerator::doErosion(float dt)
{

}


std::string EthansGenerator::GetName() { return "EthanGenerator"; }