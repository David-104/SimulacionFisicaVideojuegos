#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "Vector3D.h"
using namespace physx;
class Particle
{
public:
	Particle(Vector3D pos, Vector3D vel);
	~Particle();

	void Integrate(double t);
private:
	Vector3D vel;
	PxTransform* pose;
	RenderItem* renderItem;
};

