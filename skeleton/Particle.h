#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
//#include "Vector3D.h"
using namespace physx;
class Particle
{
public:
	Particle(Vector3 pos, Vector3 vel, Vector3 a, float d, float gravity);
	Particle(Vector3 pos, Vector3 vel, Vector3 a, float d, float gravity, float mass);
	Particle(Vector3 pos, Vector3 vel, Vector3 a, float d, float gravity, PxShape* shape, const Vector4& color);
	Particle(Vector3 pos, Vector3 vel, Vector3 a, float d, float gravity, PxShape* shape, const Vector4& color, float mass);
	~Particle();
	
	inline PxTransform* getTransform() { return pose; }
	inline float getMass() { return mass; }
	void Integrate(double t);
	void applyForce(Vector3 force);
protected:
	Vector3 vel;
	Vector3 a;
	float d;
	float gravity;
	float mass;
	PxTransform* pose;
	RenderItem* renderItem;
};

