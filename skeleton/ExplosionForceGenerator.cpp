#include "ExplosionForceGenerator.h"

#include <iostream>

static const float e = 2.71828;

ExplosionForceGenerator::ExplosionForceGenerator(Vector3 pos, float intensity, float radius, float duration) : ForceGenerator(), pos(pos), intensity(intensity), radius(radius), duration(duration), time(0)
{
}

ExplosionForceGenerator::~ExplosionForceGenerator()
{
}

void ExplosionForceGenerator::UpdateForce(Particle* p, double t)
{
	if (time < duration) {
		Vector3 particlePos = p->getTransform()->p;
		float distance = (particlePos - pos).magnitude();

		if (distance < radius) {
			force = (intensity / pow(distance, 2)) * (particlePos - pos).getNormalized() * pow(e, -time / duration);
			if (isnan(force.magnitude()))
				force = Vector3(0);
		}
		else
			force = Vector3(0);

		time += t;
		p->applyForce(force);
		std::cout << "{" << force.x << " ," << force.y << " ," << force.z << " }\n";
	}
}
