#pragma once
#include "SolidoForceGenerator.h"
class SolidoSpringForceGenerator : public SolidoForceGenerator
{
public:
    SolidoSpringForceGenerator(double k, double restingLength, Vector3 p);
    ~SolidoSpringForceGenerator();
    virtual void UpdateForce(SolidoRigido* solido, double t) override;
    inline void setK(double k) { _k = k; }
protected:
    double _k;
    double _restingLength;
    Vector3 _pos;
};

