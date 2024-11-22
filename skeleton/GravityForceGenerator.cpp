#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(float gAccel) : gAccel(gAccel)
{
    
}

GravityForceGenerator::~GravityForceGenerator()
{
}

void GravityForceGenerator::UpdateForce(Particle* p, double t)
{
    force = Vector3(0.0, p->getMass() * gAccel, 0.0);
    p->applyForce(force);
}
