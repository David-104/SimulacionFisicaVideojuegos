#pragma once
#include "ParticleSpringForceGenerator.h"

class RubberForceGenerator : public ParticleSpringForceGenerator
{
public:
    RubberForceGenerator(double k, double restingLength, Particle* p);
    ~RubberForceGenerator();
    virtual void UpdateForce(Particle* p, double t) override;
};
