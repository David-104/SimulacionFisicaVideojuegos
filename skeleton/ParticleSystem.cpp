#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(float particleLife = 10, Vector3 pos = {0, 0, 0}) : particleLife(particleLife), pos(pos)
{
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::Update(double t)
{
	if (particles.size() < MAX_PARTICLE_NUM) {
		Particle* particle = new Particle(Vector3D(pos.x, pos.y, pos.z), Vector3D(0, 10, 0), Vector3D(0, 0, 0), 0.75, -9.8);
		ParticleData newParticleTest;
		newParticleTest.particle = particle;
		newParticleTest.life = 0;
		particles.push_back(newParticleTest);
	}

	updateParticles(t);

	std::cout << particles.size() << std::endl;
}

void ParticleSystem::updateParticles(double t)
{
	for (std::list<ParticleData>::iterator it = particles.begin(); it != particles.end(); it++) {
		if (it->life < particleLife) {
			it->particle->Integrate(t);
			it->life++;
		}
		else
			particlesToErase.push_back(it);
	}

	for each (std::list<ParticleData>::iterator it in particlesToErase)
	{
		it->particle->~Particle();
		particles.erase(it);
	}

	particlesToErase.clear();
}
