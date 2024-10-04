#pragma once
#include "Particle.h"
class Proyectile : public Particle
{
public:
	Proyectile(Vector3D pos, Vector3D vel, Vector3D a, float d, float mass, float gravity, float scalingFactor);
	~Proyectile();
private:
	float mass;
	float gravity;
	float scalingFactor;
	void Scale();
};

