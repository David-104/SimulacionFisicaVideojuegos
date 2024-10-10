#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "Vector3D.h"
using namespace physx;
class Particle
{
public:
	Particle(Vector3D pos, Vector3D vel, Vector3D a, float d, float gravity);
	Particle(Vector3D pos, Vector3D vel, Vector3D a, float d, float gravity, PxShape* shape, const Vector4& color);
	~Particle();

	void Integrate(double t);
protected:
	Vector3D vel;
	Vector3D a;
	float d;
	float gravity;
	PxTransform* pose;
	RenderItem* renderItem;
};

