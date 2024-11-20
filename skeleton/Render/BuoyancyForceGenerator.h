#pragma once
#include "../ForceGenerator.h"

class BuoyancyForceGenerator : public ForceGenerator
{
public:
    BuoyancyForceGenerator(float h, float V, float d, float g, Particle* p);
    ~BuoyancyForceGenerator();
    virtual void UpdateForce(Particle* p, double t) override;
private:
    float height;
    float volume;
    float liquidDensity;
    float gravity;

    Particle* liquidParticle;
};
