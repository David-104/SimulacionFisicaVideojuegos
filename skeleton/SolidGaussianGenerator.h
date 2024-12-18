#pragma once
#include <random>
#include "SolidGenerator.h"

class SolidGaussianGenerator : public SolidGenerator
{
public:
    SolidGaussianGenerator(SolidoRigidoSystem* sys, float variation, Vector3 meanVel, Vector3 meanPos);
    ~SolidGaussianGenerator();
private:
    SolidoRigido* createSolido() override;

    float variation;
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen; // Standard mersenne_twister_engine seeded with rd()
    std::normal_distribution<> distribution;
};

