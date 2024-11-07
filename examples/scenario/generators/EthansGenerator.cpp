//
// Created by ethan on 11/7/2024.
//

#include "EthansGenerator.h"

#include "../FastNoiseLite.h"
#include "../PerlinNoise.hpp"

std::vector<Color32> Generate(int sideSize, float displacement) {
/*
  siv::PerlinNoise base = siv::PerlinNoise();
  std::vector<Color32> result;
  //base.
  base.noise2D(sideSize, sideSize);
  */
  std::vector<Color32> colors;
  FastNoiseLite base;
  base.SetFractalOctaves(2);
  base.SetSeed(28); //This number has no meaning except that it is my boyfriend's favorite number
  base.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
  const float FREQUENCY_HIGH = 4.0f, FREQUENCY_LOW = 1.0f, TOTAL_AMPLITUDE = 1.25f, X_OFFSET = 50.0f, Y_OFFSET = 50.0f, REDISTRIBUTION_EXPONENT = 1.5f;


  for (int y = 0; y < sideSize; y++) {
    for (int x = 0; x < sideSize; x++) {
      double nx = x/sideSize - 0.5, ny = y/sideSize - 0.5;
      // Calculate elevation
      // Merge a high and low frequency generation to create a new result
      float elevation = (base.GetNoise(FREQUENCY_LOW*nx, FREQUENCY_LOW*ny) + (.25f * base.GetNoise(FREQUENCY_HIGH*nx + X_OFFSET , FREQUENCY_HIGH*ny + Y_OFFSET)));
      elevation /= TOTAL_AMPLITUDE;
      elevation = pow(elevation, REDISTRIBUTION_EXPONENT);

    }
  }
}

std::string EthansGenerator::GetName() { return "EthanGenerator"; }