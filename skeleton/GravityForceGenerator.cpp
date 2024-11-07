#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(float gAccel)
{
    force = Vector3(0.0, gAccel, 0.0);
}

GravityForceGenerator::~GravityForceGenerator()
{
}

void GravityForceGenerator::UpdateForce(Particle* p)
{
    p->applyForce(force);
}
