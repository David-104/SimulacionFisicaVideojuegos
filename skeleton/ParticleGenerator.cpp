#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(ParticleSystem* ps) : particleSys(ps)
{
	//modelParticle = new Particle(particleSys->getPos(), Vector3(0, 10, 0), Vector3(0, 0, 0), 0.75, -9.8);
}

ParticleGenerator::~ParticleGenerator()
{

}

void ParticleGenerator::Update(double t)
{
	//particleSys->addParticle(modelParticle);
}
