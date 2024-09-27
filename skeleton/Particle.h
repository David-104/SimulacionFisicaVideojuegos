#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "Vector3D.h"
using namespace physx;
class Particle
{
public:
	Particle(Vector3D pos, Vector3D vel, Vector3D a, float d);
	~Particle();

	void Integrate(double t);
private:
	Vector3D vel;
	Vector3D a;
	float d;
	PxTransform* pose;
	RenderItem* renderItem;
};
