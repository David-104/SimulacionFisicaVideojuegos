#pragma once
#include "ParticleSystem.h"
#include "Particle.h"
class ParticleGenerator
{
public:
	ParticleGenerator(ParticleSystem* ps);
	~ParticleGenerator();
	void Update(double t);
private:
	ParticleSystem* particleSys;
	//Particle* modelParticle;
	float meanPos;
	float meanVel;
};

