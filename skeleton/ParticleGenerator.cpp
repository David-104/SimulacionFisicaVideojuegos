#include "ParticleGenerator.h"
#include <random>
ParticleGenerator::ParticleGenerator(ParticleSystem* ps, Vector3 v, Vector3 p) : particleSys(ps), meanVel(v), meanPos(p)
{

}

ParticleGenerator::~ParticleGenerator()
{
	
}

void ParticleGenerator::Update(double t)
{
	particleSys->addParticle(createParticle());
}
