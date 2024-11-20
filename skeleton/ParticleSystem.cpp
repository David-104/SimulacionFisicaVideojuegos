#include "ParticleSystem.h"
#include "UniformGenerator.h"
#include "GaussianGenerator.h"
#include <iostream>

#include "ParticleSpringForceGenerator.h"
#include "RubberForceGenerator.h"
#include "SpringForceGenerator.h"

ParticleSystem::ParticleSystem(float pl, Vector3 p)
{
	particleLife = pl;

	pos = p;

	modelParticle.acceleration = Vector3(0.0, 0.0, 0.0);
	modelParticle.gravity = -9.8;
	modelParticle.damping = 1.0;
	modelParticle.shape = CreateShape(PxSphereGeometry(1));
	modelParticle.color = Vector4(1.0, 0.85, 0.6, 1.0);
	modelParticle.mass = 1.0;
}

ParticleSystem::ParticleSystem(float particleLife = 10, Vector3 pos = {0, 0, 0}, GeneratorType type = UNIFORM, Vector3 meanVel = Vector3(0.0, 1.0, 0.0), Vector3 meanPos = Vector3(0.0, 0.0, 0.0)) : particleLife(particleLife), pos(pos)
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
