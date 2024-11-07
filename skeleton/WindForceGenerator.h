#pragma once
#include "ForceGenerator.h"
class WindForceGenerator : public ForceGenerator
{
public:
    WindForceGenerator(Vector3 windVel, float windCoef, float k1, float k2);
    ~WindForceGenerator() override;
    void UpdateForce(Particle* p) override;
private:
    Vector3 windVel;
    float windCoef;
    float k1;
    float k2;
};

