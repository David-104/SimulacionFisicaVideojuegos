#include "ParticleSpringForceGenerator.h"

ParticleSpringForceGenerator::ParticleSpringForceGenerator(double k, double restingLength, Particle* p) : SpringForceGenerator(k, restingLength, p->getTransform()->p), particle(p)
{
}

ParticleSpringForceGenerator::~ParticleSpringForceGenerator()
{
}

void ParticleSpringForceGenerator::UpdateForce(Particle* p, double t)
{
    _pos = particle->getTransform()->p;
    SpringForceGenerator::UpdateForce(p, t);
}
