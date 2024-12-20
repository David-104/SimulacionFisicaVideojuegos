#include "ParticleSystem.h"
#include "UniformGenerator.h"
#include "GaussianGenerator.h"
#include <iostream>

#include "ParticleSpringForceGenerator.h"
#include "RubberForceGenerator.h"
#include "SpringForceGenerator.h"
#include "BuoyancyForceGenerator.h"
#include "GravityForceGenerator.h"


ParticleSystem::ParticleSystem(float particleLife, Vector3 pos, GeneratorType type, Vector3 meanVel, Vector3 meanPos, float maxPartNum, float maxPartDist) : particleLife(particleLife), pos(pos), MAX_PARTICLE_NUM(maxPartNum), MAX_PARTICLE_DIST(maxPartDist)
{
	ParticleGenerator* pg;
    switch (type)
    {
    case UNIFORM:
		pg = new UniformGenerator(this, meanVel, meanPos);
		break;
    case GAUSSIAN:
		pg = new GaussianGenerator(this, 5.0, meanVel, meanPos);
		break;
    }
    generators.push_back(pg);

	modelParticle.acceleration = Vector3(0.0, 0.0, 0.0);
	modelParticle.gravity = -9.8;
	modelParticle.damping = 1.0;
	modelParticle.shape = CreateShape(PxSphereGeometry(1));
	modelParticle.color = Vector4(1.0, 1.0, 1.0, 1.0);
	modelParticle.mass = 1.0;
}

ParticleSystem::~ParticleSystem()
{
	for each (ParticleData data in particles)
	{
		delete data.particle;
	}

	for each (ParticleGenerator* gen in generators)
	{
		delete gen;
	}
}

void ParticleSystem::Update(double t)
{
	if (particles.size() < MAX_PARTICLE_NUM)
		updateGenerators(t);

	if (forceGenerators.size() > 0)
		UpdateForceGenerators(t);

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

void ParticleSystem::setModelParticle(ModelParticleData mp)
{
	modelParticle = mp;
}

void ParticleSystem::UpdateForceGenerators(double t)
{
    for each(ForceGenerator* fg in forceGenerators)
    {
		for each (ParticleData data in particles)
		{
			fg->UpdateForce(data.particle, t);
		}
    }
}

void ParticleSystem::createSpring1Demo()
{
	Particle* p1 = new Particle(Vector3(-10, 0, 0), Vector3(0), Vector3(0), 0.85, -10, 1.0);
	particles.push_back(ParticleData{p1, 0});
	SpringForceGenerator* f1 = new SpringForceGenerator(5, 10, pos);
	forceGenerators.push_back(f1);
}

void ParticleSystem::createSpring2Demo()
{
	PxShape* shape = CreateShape(PxSphereGeometry(1));
	Particle* p1 = new Particle(Vector3(10, 0, 0), Vector3(0), Vector3(0), 0.85, 0, shape, Vector4(1.0, 1.0, 0.0, 1.0), 1.0);
	Particle* p2 = new Particle(Vector3(-10, 0, 0), Vector3(0), Vector3(0), 0.85, 0, shape, Vector4(1.0, 0.0, 1.0, 1.0), 1.0);
	particles.push_back(ParticleData{ p1, 0 });
	particles.push_back(ParticleData{ p2, 0 });
	ParticleSpringForceGenerator* f1 = new ParticleSpringForceGenerator(5, 10, p1);
	ParticleSpringForceGenerator* f2 = new ParticleSpringForceGenerator(5, 10, p2);
	forceGenerators.push_back(f1);
	forceGenerators.push_back(f2);
}

void ParticleSystem::createSpringRubberDemo()
{
	PxShape* shape = CreateShape(PxSphereGeometry(1));
	Particle* p1 = new Particle(Vector3(-10, 0, 0), Vector3(0), Vector3(0), 0.85, 0, shape, Vector4(1.0, 1.0, 0.0, 1.0), 1.0);
	Particle* p2 = new Particle(Vector3(10, 0, 0), Vector3(0), Vector3(0), 0.85, 0, shape, Vector4(1.0, 0.0, 1.0, 1.0), 1.0);
	particles.push_back(ParticleData{ p1, 0 });
	particles.push_back(ParticleData{ p2, 0 });

	RubberForceGenerator* f1 = new RubberForceGenerator(5, 20, p1);
	RubberForceGenerator* f2 = new RubberForceGenerator(5, 20, p2);
	forceGenerators.push_back(f1);
	forceGenerators.push_back(f2);
}

void ParticleSystem::createBuoyancyDemo()
{
	
	PxShape* shape1 = CreateShape(PxBoxGeometry(1, 1, 1));
	//caso Fg = E
	Particle* p1 = new Particle(Vector3(0, 10, 0), Vector3(0), Vector3(0), 0.85, 0, shape1, Vector4(1.0, 0.0, 0.0, 1.0), 0.5, 0.001);
	particles.push_back(ParticleData{ p1, 0 });

	//caso Fg > E
	Particle* p2 = new Particle(Vector3(10, 15, 0), Vector3(0), Vector3(0), 0.85, 0, shape1, Vector4(0.0, 1.0, 0.0, 1.0), 10.0, 0.001);
	particles.push_back(ParticleData{ p2, 0 });

	//caso Fg < E
	Particle* p3 = new Particle(Vector3(-10, 15, 0), Vector3(0), Vector3(0), 0.85, 0, shape1, Vector4(0.0, 0.0, 1.0, 1.0), 0.1, 0.001);
	particles.push_back(ParticleData{ p3, 0 });

	
	PxShape* shape2 = CreateShape(PxBoxGeometry(10, 0.001, 10));
	Particle* water = new Particle(Vector3(0, 10, 0), Vector3(0), Vector3(0), 0.85, 0, shape2, Vector4(0.0, 1.0, 1.0, 1.0), 1.0);

	float gravity = 10;
	BuoyancyForceGenerator* f1 = new BuoyancyForceGenerator(1, 1000, gravity, water );
	forceGenerators.push_back(f1);
	
	GravityForceGenerator* gf = new GravityForceGenerator(-gravity);
	forceGenerators.push_back(gf);
}

void ParticleSystem::applyForceToParticles(Vector3 force)
{
    for (auto pData : particles)
    {
		pData.particle->applyForce(force);
    }
}

void ParticleSystem::updateParticles(double t)
{
	for (std::list<ParticleData>::iterator it = particles.begin(); it != particles.end(); it++) {
		float dist = Vector3(it->particle->getTransform()->p - pos).magnitude();
		if ((it->life < particleLife || particleLife == -1) && dist < MAX_PARTICLE_DIST) { //particleLife == -1 es que son inmorrtales por tiempo
			it->particle->Integrate(t);
			it->life += t;
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
