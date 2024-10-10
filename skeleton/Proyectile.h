#pragma once
#include "Particle.h"
class Proyectile : public Particle
{
public:
	Proyectile(Vector3D pos, Vector3D vel, Vector3D a, float d, float gravity , float mass, float scalingFactor);
	~Proyectile();
	enum ProyectileType { };
private:
	float mass;
	float scalingFactor;
	void Scale();
};

