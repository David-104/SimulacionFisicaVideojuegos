#pragma once
#include "core.hpp"
#include "Particle.h"

class ForceGenerator
{
public:
    ForceGenerator() {};
    ~ForceGenerator() {};
    virtual void UpdateForce(Particle* p) { };
};

