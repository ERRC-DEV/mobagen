//
// Created by ethan on 11/7/2024.
//

#ifndef ETHANSGENERATOR_H
#define ETHANSGENERATOR_H

#include "../GeneratorBase.h"

class EthansGenerator : public ScenarioGeneratorBase {
public:
  std::vector<Color32> Generate(int sideSize, float displacement = 0) override;
  std::string GetName() override;

};

#endif //ETHANSGENERATOR_H
