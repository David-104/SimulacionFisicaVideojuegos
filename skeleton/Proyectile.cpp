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
	vel = vel * scalingFactor;
	mass = mass / scalingFactor;
	gravity = gravity * scalingFactor;
}
