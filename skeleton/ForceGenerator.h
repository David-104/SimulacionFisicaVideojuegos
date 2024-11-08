#pragma once
#include "core.hpp"
#include "Particle.h"

class ForceGenerator
{
public:
    ForceGenerator() = default;
    virtual ~ForceGenerator() = default;
    virtual void UpdateForce(Particle* p, double t) { }
protected:
    Vector3 force;    
};

