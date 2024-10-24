#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
//#include "Vector3D.h"
using namespace physx;
class Particle
{
public:
	Particle(Vector3 pos, Vector3 vel, Vector3 a, float d, float gravity);
	Particle(Vector3 pos, Vector3 vel, Vector3 a, float d, float gravity, PxShape* shape, const Vector4& color);
	~Particle();

	void Integrate(double t);
	inline PxTransform* getTransform() { return pose; }
protected:
	Vector3 vel;
	Vector3 a;
	float d;
	float gravity;
	PxTransform* pose;
	RenderItem* renderItem;
};

