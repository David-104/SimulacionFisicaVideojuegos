#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(float gAccel)
{
    acceleration = Vector3(0.0, gAccel, 0.0);
}

GravityForceGenerator::~GravityForceGenerator()
{
}

void GravityForceGenerator::UpdateForce(Particle* p)
{
    Vector3 force = p->getMass() * acceleration;
    //aplicar fuerza
}
