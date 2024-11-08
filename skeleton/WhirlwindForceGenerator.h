#pragma once
#include "WindForceGenerator.h"
class WhirlwindForceGenerator : public WindForceGenerator
{
public:
    WhirlwindForceGenerator(Vector3 centre, float windCoef, float k1, float k2, float whirlwindForce, float height);
    ~WhirlwindForceGenerator();
    void UpdateForce(Particle* p, double t) override;
private:
    Vector3 centre;
    float whirlwindForce;
    float height;
};

