#pragma once
#include "ForceGenerator.h"
class ExplosionForceGenerator : public ForceGenerator
{
public:
	ExplosionForceGenerator(Vector3 pos, float force, float radius, float duration);
	~ExplosionForceGenerator();
	void UpdateForce(Particle* p, double t) override;
	inline void resetTime() { time = 0; }
private:
	Vector3 pos;
	float intensity;
	float radius;
	float duration;
	float time;
};

