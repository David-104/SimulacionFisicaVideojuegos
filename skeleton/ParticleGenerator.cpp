#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(ParticleSystem* ps) : particleSys(ps)
{
	
}

ParticleGenerator::~ParticleGenerator()
{

}

void ParticleGenerator::Update(double t)
{
	Vector3 pos(0, 0, 0);
	Particle* particle = new Particle(pos, Vector3(0, 10, 0), Vector3(0, 0, 0), 0.75, -9.8);
	particleSys->addParticle(particle);
}
