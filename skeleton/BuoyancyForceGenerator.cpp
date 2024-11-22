#include "BuoyancyForceGenerator.h"

BuoyancyForceGenerator::BuoyancyForceGenerator(float h, float d, float g, Particle* p) : ForceGenerator(), height(h), liquidDensity(d), gravity(g), liquidParticle(p)
{
}

BuoyancyForceGenerator::~BuoyancyForceGenerator()
{
}

void BuoyancyForceGenerator::UpdateForce(Particle* p, double t)
{
    float h = p->getTransform()->p.y;
    float h0 = liquidParticle->getTransform()->p.y;

    force = Vector3(0);
    float immersed = 0.0f;
    float heightDiff = h- h0;
    
    if(heightDiff > height * 0.5)
        immersed = 0.0f;
    else if (heightDiff < height * 0.5)
        immersed = 1.0f;
    else
        immersed = heightDiff / height + 0.5;

    force.y = liquidDensity * p->getVolume() * immersed * gravity;
    p->applyForce(force);
}
