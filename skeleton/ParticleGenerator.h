#pragma once
#include "ParticleSystem.h"
#include "Particle.h"

class ParticleGenerator
{
public:
	ParticleGenerator(ParticleSystem* ps);
	~ParticleGenerator();
	void Update(double t);
protected:
	virtual Particle* createParticle() { return nullptr; }

	struct ModelParticleData {
		Vector3 acceleration;
		float damping;
		float gravity;
		PxShape* shape;
		Vector4 color;
	};
	Vector3 meanPos;
	Vector3 meanVel;
	ModelParticleData modelParticle;
	ParticleSystem* particleSys;
};

