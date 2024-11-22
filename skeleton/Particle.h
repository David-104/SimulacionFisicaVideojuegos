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
	Particle(Vector3 pos, Vector3 vel, Vector3 a, float d, float gravity, PxShape* shape, const Vector4& color, float mass, float volume);
	~Particle();
	
	inline PxTransform* getTransform() { return pose; }
	inline float getMass() { return mass; }
	inline float getVolume() { return volume; }
	inline Vector3 getVel() { return vel; }
	void Integrate(double t);
	void applyForce(Vector3 force);
protected:
	Vector3 vel;
	Vector3 a;
	Vector3 forceApplied;
	float d;
	float gravity;
	float mass;
	float volume; //el volumen va a ser siempre un cubo porque solo estoy poniendo esto para el de flotacion
	PxTransform* pose;
	RenderItem* renderItem;
};

