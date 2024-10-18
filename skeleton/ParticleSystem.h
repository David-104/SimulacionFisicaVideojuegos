#pragma once
#include <vector>
#include"Particle.h"

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();
private:
	std::vector<Particle*> particles;
	//vector de gens
	//num max particulas para gen
	//struct particulas y vida
};

