#include "GaussianGenerator.h"

GaussianGenerator::GaussianGenerator(ParticleSystem* ps, float v, Vector3 meanVel, Vector3 meanPos) : ParticleGenerator(ps, meanVel, meanPos), variation(v)
{
    gen = std::mt19937(rd());
    distribution = std::normal_distribution<>(meanVel.magnitude(), variation);
}

GaussianGenerator::~GaussianGenerator()
{
}

Particle* GaussianGenerator::createParticle()
{
    Vector3 pos = Vector3(meanPos.x * distribution(gen), meanPos.y * distribution(gen), meanPos.z * distribution(gen));

    Vector3 vel = Vector3(meanVel.x * distribution(gen), meanVel.y * distribution(gen), meanVel.z * distribution(gen));

    return new Particle(pos, vel, modelParticle.acceleration, modelParticle.damping, modelParticle.gravity, modelParticle.shape, modelParticle.color);
}
