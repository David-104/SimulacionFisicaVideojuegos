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
	Particle createParticle();
	ParticleSystem* particleSys;
	//Particle* modelParticle;
	float meanPos;
	float meanVel;
};

