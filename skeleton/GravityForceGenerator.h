#pragma once
#include "ForceGenerator.h"
class GravityForceGenerator : public ForceGenerator
{
public:
    GravityForceGenerator(float gAccel);
    ~GravityForceGenerator() override;
    void UpdateForce(Particle* p) override;
};

