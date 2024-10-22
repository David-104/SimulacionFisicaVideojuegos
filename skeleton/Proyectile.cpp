#include "Proyectile.h"

Proyectile::Proyectile(Vector3 pos, Vector3 vel, Vector3 a, float d, float gravity, float mass, float scalingFactor) : Particle(pos, vel, a, d, gravity), mass(mass), scalingFactor(scalingFactor)
{
	Scale();
}

Proyectile::Proyectile(Vector3 pos, Vector3 vel, Vector3 a, float d, float gravity, float mass, float scalingFactor,
    PxShape* shape, const Vector4& color) : Particle(pos, vel, a, d, gravity, shape, color), mass(mass), scalingFactor(scalingFactor)
{
	Scale();
}


Proyectile::~Proyectile()
{
	
}

void Proyectile::Scale() {
	Vector3 newVel = vel * scalingFactor;
	float ogSpeed = vel.magnitude();
	float newSpeed = newVel.magnitude();

	mass = mass * pow(ogSpeed, 2) / pow(newSpeed, 2);
	vel = newVel;
}
