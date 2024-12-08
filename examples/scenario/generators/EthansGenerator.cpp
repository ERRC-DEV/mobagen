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
    doErosion(dt);
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

      float distance = 1.0f - ((1.0f-(nx*nx)) * (1.0f-(ny*ny)));

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

void EthansGenerator::doErosion(float dt)  // Code base/pseudocode is taken from particle generator as inspiration and modified to suit my generator's needs
{
  //glm::vec3 getSurfaceNormal();

  static int cycles = 1;
  if (dt > 0.500) {
    if (cycles > 1) cycles--;
  } else
    cycles++;

  for (int i = 0; i < cycles; i++)
  {
    glm::vec2 startPos = glm::vec2(Random::Range(1, (int)sideSizeCached - 2), Random::Range(1, (int)sideSizeCached - 2));
    WaterDroplet drop(startPos);

    while (drop.volume > minVol)
    {
      // If it is out of bounds, destroy it
      if ((int)drop.pos.x >= sideSizeCached || (int)drop.pos.y >= sideSizeCached || (int)drop.pos.x <= 0 || (int)drop.pos.y <= 0)
      {
        break;
      }
      /*if (elevationMap[(int)drop.pos.x][(int)drop.pos.y] < 0.5f) Toyed around with having it break when it hits the water level. Did not like it
      {
        break;
      }*/

      glm::vec3 normal = getSurfaceNormal((int)drop.pos.x, (int)drop.pos.y); // Normal of surface
      glm::vec2 initialPos = glm::vec2(drop.pos.x, drop.pos.y); // The inital position

      //Move the drop
      drop.speed += dt * glm::vec2(normal.x, normal.z) / (drop.volume * density);
      drop.pos += dt * drop.speed;
      drop.speed *= (1.0 - dt * friction);

      // If this moved it out of bounds, kill it
      if (drop.pos.x >= sideSizeCached || drop.pos.y >= sideSizeCached || drop.pos.x <= 0 || drop.pos.y <= 0)
      {
        break;
      }

      float maxsediment = drop.volume * glm::length(drop.speed) * (elevationMap[(int)initialPos.x][(int)initialPos.y] - elevationMap[(int)drop.pos.x][(int)drop.pos.y]);
      if (maxsediment < 0.0) maxsediment = 0.0;
      float sdiff = maxsediment - drop.sediment;

      drop.sediment += dt * depositionRate * sdiff;
      elevationMap[(int)initialPos.x][(int)initialPos.y] -= dt * drop.volume * depositionRate * sdiff;

      drop.volume *= (1.0f - dt * evapRate);
    }
  }
}

glm::vec3 EthansGenerator::getSurfaceNormal(int x, int y)
{
  glm::vec3 normal = glm::vec3(0, 0, 0);
  float scale = 5;

  static const float sqrt2 = sqrtf(2);

  // Cardinal directions
  normal += glm::vec3(0.15) * glm::normalize(glm::vec3(scale * (elevationMap[x][y] - elevationMap[x + 1][y]), 1.0, 0.0)); //East
  normal += glm::vec3(0.15) * glm::normalize(glm::vec3(scale * (elevationMap[x - 1][y] - elevationMap[x][y]), 1.0, 0.0)); //West
  normal += glm::vec3(0.15) * glm::normalize(glm::vec3(0.0, 1.0, scale * (elevationMap[x][y] - elevationMap[x][y + 1]))); //North
  normal += glm::vec3(0.15) * glm::normalize(glm::vec3(0.0, 1.0, scale * (elevationMap[x][y - 1] - elevationMap[x][y]))); //South

  // Diagonal
  normal += glm::vec3(0.1) * glm::normalize(glm::vec3(scale * (elevationMap[x][y] - elevationMap[x + 1][y + 1]) / sqrt2, sqrt2,scale * (elevationMap[x][y] - elevationMap[x + 1][y + 1]) / sqrt2));  // Positive Y
  normal += glm::vec3(0.1) * glm::normalize(glm::vec3(scale * (elevationMap[x][y] - elevationMap[x + 1][y - 1]) / sqrt2, sqrt2,scale * (elevationMap[x][y] - elevationMap[x + 1][y - 1]) / sqrt2));  // Positive Y
  normal += glm::vec3(0.1) * glm::normalize(glm::vec3(scale * (elevationMap[x][y] - elevationMap[x - 1][y + 1]) / sqrt2, sqrt2,scale * (elevationMap[x][y] - elevationMap[x - 1][y + 1]) / sqrt2));  // Positive Y
  normal += glm::vec3(0.1) * glm::normalize(glm::vec3(scale * (elevationMap[x][y] - elevationMap[x - 1][y - 1]) / sqrt2, sqrt2,scale * (elevationMap[x][y] - elevationMap[x - 1][y - 1]) / sqrt2));  // Positive Y

  return normal;
}



std::string EthansGenerator::GetName() { return "EthanGenerator"; }