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
	ParticleSystem(float particleLife = 100, Vector3 pos = Vector3(0), GeneratorType type = UNIFORM, Vector3 meanVel = Vector3(0), Vector3 meanPos = Vector3(0), float maxPartNum = 1000, float maxPartDist = 1000);
	~ParticleSystem();
	void Update(double t);
	void addParticle(Particle* particle);
	inline Vector3 getPos() { return pos; }
	inline ModelParticleData getModelParticle() { return modelParticle; }
	void setModelParticle(ModelParticleData mp);
	void UpdateForceGenerators(double t);
	inline void AddForceGenerator(ForceGenerator* fg) { forceGenerators.push_back(fg); }

	void createSpring1Demo();
	void createSpring2Demo();
	void createSpringRubberDemo();
	void createBuoyancyDemo();

	void applyForceToParticles(Vector3 force);
private:
	float MAX_PARTICLE_NUM = 100;
	float MAX_PARTICLE_DIST = 1000;
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

