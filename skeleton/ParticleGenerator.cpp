#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(ParticleSystem* ps) : particleSys(ps)
{
	meanPos = ps->getPos();
	meanVel = Vector3(10.0, 10.0, 10.0);

	modelParticle.acceleration = Vector3(0.0, 0.0, 0.0);
	modelParticle.gravity = -9.8;
	modelParticle.damping = 1.0;
	modelParticle.shape = CreateShape(PxSphereGeometry(1));
	modelParticle.color = Vector4(0.75, 0.0, 1.0, 1.0);
}

ParticleGenerator::~ParticleGenerator()
{
	
}

void ParticleGenerator::Update(double t)
{
	particleSys->addParticle(createParticle());
}
