#pragma once
#include "SolidoForceGenerator.h"
class SolidoWindGenerator : public SolidoForceGenerator
{
public:
    SolidoWindGenerator(Vector3 windVel, float windCoef, float k1, float k2);
    ~SolidoWindGenerator();
    void UpdateForce(SolidoRigido* solido, double t) override;
protected:
    Vector3 windVel;
    float windCoef;
    float k1;
    float k2;
};

