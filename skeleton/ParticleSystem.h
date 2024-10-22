#pragma once
#include"Particle.h"
#include <list>
class ParticleGenerator;
class ParticleSystem
{
public:
	ParticleSystem(float particleLife, Vector3 pos);
	~ParticleSystem();
	void Update(double t);
	void addParticle(Particle* particle);
private:
	float const MAX_PARTICLE_NUM = 100;
	float particleLife;
	Vector3 pos; 

	struct ParticleData {
		Particle* particle;
		float life;
	};

	std::list<ParticleData> particles;
	std::list<ParticleGenerator*> generators;
	std::vector<std::list<ParticleData>::iterator> particlesToErase;
	//vector de gens
	//num max particulas para gen

	void updateParticles(double t);
	void updateGenerators(double t);
	void removeParticles();
};

