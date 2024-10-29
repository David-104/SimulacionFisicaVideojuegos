#pragma once
#include "ParticleSystem.h"
#include "Particle.h"

class ParticleGenerator
{
public:
	ParticleGenerator(ParticleSystem* ps, Vector3 meanVel, Vector3 meanPos);
	~ParticleGenerator();
	void Update(double t);
protected:
	virtual Particle* createParticle() { return nullptr; }
	Vector3 meanPos;
	Vector3 meanVel;
	ParticleSystem* particleSys;
};

