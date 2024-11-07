#pragma once
#include "ForceGenerator.h"
class GravityForceGenerator : public ForceGenerator
{
public:
    GravityForceGenerator(float gAccel);
    ~GravityForceGenerator();
    void UpdateForce(Particle* p) override;
private:
    Vector3 acceleration;
};

