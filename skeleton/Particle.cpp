#include "Particle.h"

Particle::Particle(Vector3D pos, Vector3D vel) : vel(vel)
{
	pose = new PxTransform(PxVec3(pos.x, pos.y, pos.z));

	PxShape* shape = CreateShape(PxSphereGeometry(1));
	renderItem = new RenderItem(shape, pose, Vector4(0.0, 0.0, 0.0, 1.0));
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::Integrate(double t)
{
	pose->p = pose->p + Vector3(vel.x, vel.y, vel.z) * t;
}
