#include "Proyectile.h"

Proyectile::Proyectile(Vector3D pos, Vector3D vel, Vector3D a, float d, float gravity, float mass, float scalingFactor) : Particle(pos, vel, a, d, gravity), mass(mass), scalingFactor(scalingFactor)
{
	Scale();
}

Proyectile::Proyectile(Vector3D pos, Vector3D vel, Vector3D a, float d, float gravity, float mass, float scalingFactor,
    PxShape* shape, const Vector4& color) : Particle(pos, vel, a, d, gravity, shape, color), mass(mass), scalingFactor(scalingFactor)
{
	Scale();
}


Proyectile::~Proyectile()
{
	
}

void Proyectile::Scale() {
	Vector3D newVel = vel * scalingFactor;
	float ogSpeed = vel.Module();
	float newSpeed = newVel.Module();

	mass = mass * pow(ogSpeed, 2) / pow(newSpeed, 2);
	vel = newVel;
}
