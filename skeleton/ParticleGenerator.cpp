#include "ParticleGenerator.h"
#include <random>
ParticleGenerator::ParticleGenerator(ParticleSystem* ps, Vector3 v, Vector3 p) : particleSys(ps), meanVel(v), meanPos(p)
{
	modelParticle.acceleration = Vector3(0.0, 0.0, 0.0);
	modelParticle.gravity = -9.8;
	modelParticle.damping = 1.0;
	modelParticle.shape = CreateShape(PxSphereGeometry(1));

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distribution(0.0, 1.0);
	modelParticle.color = Vector4(distribution(gen), distribution(gen), distribution(gen), 1.0);
}

ParticleGenerator::~ParticleGenerator()
{
	
}

void ParticleGenerator::Update(double t)
{
	particleSys->addParticle(createParticle());
}
