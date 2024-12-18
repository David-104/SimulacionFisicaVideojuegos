#pragma once
#include "SolidoRigido.h"

class SolidoForceGenerator
{
public:
    SolidoForceGenerator() = default;
    virtual ~SolidoForceGenerator() = default;
    virtual void UpdateForce(SolidoRigido* p, double t) {}
protected:
    Vector3 force;
};

