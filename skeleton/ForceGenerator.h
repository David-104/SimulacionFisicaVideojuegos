#pragma once
#include "core.hpp"
#include "Particle.h"

class ForceGenerator
{
public:
    ForceGenerator() = default;
    virtual ~ForceGenerator() = default;
    virtual void UpdateForce(Particle* p) { }
protected:
    Vector3 force;    
};

