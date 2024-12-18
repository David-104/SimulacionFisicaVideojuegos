#pragma once
#include <random>
#include "SolidGenerator.h"

class SolidUniformGenerator : public SolidGenerator
{
public:
    SolidUniformGenerator(SolidoRigidoSystem* sys, Vector3 meanVel, Vector3 meanPos);
    ~SolidUniformGenerator();
private:
    SolidoRigido* createSolido() override;

    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen; // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> distribution;
};

