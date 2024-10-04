#include "Proyectile.h"

Proyectile::Proyectile(Vector3D pos, Vector3D vel, Vector3D a, float d, float mass, float gravity, float scalingFactor) : Particle(pos, vel, a + Vector3D(0.0, gravity, 0.0), d), mass(mass), gravity(gravity), scalingFactor(scalingFactor)
{
	Scale();
}

Proyectile::~Proyectile()
{
	Particle::~Particle();
}

void Proyectile::Scale() {

}