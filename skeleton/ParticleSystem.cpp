#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include <iostream>

ParticleSystem::ParticleSystem(float particleLife = 10, Vector3 pos = {0, 0, 0}) : particleLife(particleLife), pos(pos)
{
	ParticleGenerator* pg = new ParticleGenerator(this);
	generators.push_back(pg);
}

ParticleSystem::~ParticleSystem()
{
	for each (ParticleData data in particles)
	{
		data.particle->~Particle();
	}

	for each (ParticleGenerator* gen in generators)
	{
		gen->~ParticleGenerator();
	}
}

void ParticleSystem::Update(double t)
{
	if (particles.size() < MAX_PARTICLE_NUM) {
		updateGenerators(t);
	}

	updateParticles(t);

	//std::cout << particles.size() << std::endl;
}

void ParticleSystem::addParticle(Particle* particle)
{
	ParticleData particleData;
	particleData.particle = particle;
	particleData.life = 0;
	particles.push_back(particleData);
}

void ParticleSystem::updateParticles(double t)
{
	for (std::list<ParticleData>::iterator it = particles.begin(); it != particles.end(); it++) {
		float dist = Vector3(it->particle->getTransform()->p - pos).magnitude();
		if (it->life < particleLife && dist < MAX_PARTICLE_DIST) {
			it->particle->Integrate(t);
			it->life++;
		}
		else
			particlesToErase.push_back(it);
	}

	removeParticles();
}

void ParticleSystem::updateGenerators(double t)
{
	for each (ParticleGenerator* pg in generators)
	{
		pg->Update(t);
	}
}

void ParticleSystem::removeParticles()
{
	for each (std::list<ParticleData>::iterator it in particlesToErase)
	{
		it->particle->~Particle();
		particles.erase(it);
	}
	particlesToErase.clear();
}
