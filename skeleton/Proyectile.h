#pragma once
#include "Particle.h"
class Proyectile : public Particle
{
public:
	Proyectile(Vector3 pos, Vector3 vel, Vector3 a, float d, float gravity , float mass, float scalingFactor);
	Proyectile(Vector3 pos, Vector3 vel, Vector3 a, float d, float gravity , float mass, float scalingFactor, PxShape* shape, const Vector4& color);
	~Proyectile();
private:
	float mass;
	float scalingFactor;
	void Scale();
};

