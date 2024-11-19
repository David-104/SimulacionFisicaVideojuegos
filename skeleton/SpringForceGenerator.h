#pragma once
#include "ForceGenerator.h"
class SpringForceGenerator : public ForceGenerator
{
public:
    SpringForceGenerator(double k, double restingLength, Vector3 p);
    ~SpringForceGenerator();
    virtual void UpdateForce(Particle* p, double t) override;
    inline void setK(double k) { _k = k; }
protected:
    double _k;
    double _restingLength;
    Vector3 _pos;
};

