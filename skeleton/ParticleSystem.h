#pragma once
#include"Particle.h"
#include <list>

#include "ForceGenerator.h"
class ParticleGenerator;
class ParticleSystem
{
public:
    enum GeneratorType { UNIFORM, GAUSSIAN};
	struct ModelParticleData {
		Vector3 acceleration;
		float damping;
		float gravity;
		PxShape* shape;
		Vector4 color;
		float mass;
	};
	ParticleSystem(float particleLife, Vector3 pos, GeneratorType type, Vector3 meanVel, Vector3 meanPos);
	~ParticleSystem();
	void Update(double t);
	void addParticle(Particle* particle);
	inline Vector3 getPos() { return pos; }
	inline ModelParticleData getModelParticle() { return modelParticle; }
	void setModelParticle(ModelParticleData mp);
	void UpdateForceGenerators(double t);
	inline void AddForceGenerator(ForceGenerator* fg) { forceGenerators.push_back(fg); }
private:
	float const MAX_PARTICLE_NUM = 100;
	float const MAX_PARTICLE_DIST = 1000;
	float particleLife;
	Vector3 pos; 
	ModelParticleData modelParticle;

	struct ParticleData {
		Particle* particle;
		float life;
	};

	std::list<ParticleData> particles;
	std::list<ParticleGenerator*> generators;
	std::vector<std::list<ParticleData>::iterator> particlesToErase;
	std::vector<ForceGenerator*> forceGenerators;
	//vector de gens
	//num max particulas para gen

	void updateParticles(double t);
	void updateGenerators(double t);
	void removeParticles();
};

