#pragma once
#include "ParticleGenerator.h"
#include <random>

class UniformGenerator : public ParticleGenerator
{
public:
	UniformGenerator(ParticleSystem* ps);
	~UniformGenerator();
private:

	Particle* createParticle() override;

	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen; // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> distribution;
};

