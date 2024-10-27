#pragma once
#include "ParticleGenerator.h"
#include <random>
class GaussianGenerator : public ParticleGenerator
{
public:
    GaussianGenerator(ParticleSystem* ps, float variation, Vector3 meanVel, Vector3 meanPos);
    ~GaussianGenerator();
private:
    Particle* createParticle() override;

    float variation;
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen; // Standard mersenne_twister_engine seeded with rd()
    std::normal_distribution<> distribution;
};

