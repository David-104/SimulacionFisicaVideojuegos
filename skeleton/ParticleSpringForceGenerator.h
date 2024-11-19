#pragma once
#include "SpringForceGenerator.h"
class ParticleSpringForceGenerator : public SpringForceGenerator
{
public:
    ParticleSpringForceGenerator(double k, double restingLength, Particle* p);
    ~ParticleSpringForceGenerator();
    virtual void UpdateForce(Particle* p, double t) override;
private:
    Particle* particle;
};

