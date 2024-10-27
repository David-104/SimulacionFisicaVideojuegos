#include "UniformGenerator.h"
#include <iostream>

UniformGenerator::UniformGenerator(ParticleSystem* ps, Vector3 meanVel, Vector3 meanPos) : ParticleGenerator(ps, meanVel, meanPos)
{
	gen = std::mt19937(rd());
	distribution = std::uniform_real_distribution<>(-1.0, 1.0);
}

UniformGenerator::~UniformGenerator()
{

}

Particle* UniformGenerator::createParticle()
{
	Vector3 pos = Vector3(meanPos.x * distribution(gen), meanPos.y * distribution(gen), meanPos.z * distribution(gen));

	Vector3 vel = Vector3(meanVel.x * distribution(gen), meanVel.y * distribution(gen), meanVel.z * distribution(gen));

	return new Particle(pos, vel, modelParticle.acceleration, modelParticle.damping, modelParticle.gravity, modelParticle.shape, modelParticle.color);
}
