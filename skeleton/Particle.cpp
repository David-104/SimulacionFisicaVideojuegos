#include "Particle.h"
#include <cmath>s
Particle::Particle(Vector3D pos, Vector3D vel, Vector3D a, float d) : vel(vel), a(a), d(d)
{
	pose = new PxTransform(PxVec3(pos.x, pos.y, pos.z));

	PxShape* shape = CreateShape(PxSphereGeometry(1));
	renderItem = new RenderItem(shape, pose, Vector4(0.0, 0.0, 0.0, 1.0));
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	delete(pose);
}

void Particle::Integrate(double t)
{
	std::cout << vel * d << std::endl;
	vel = vel * pow(d, t) + a * t;
	pose->p = pose->p + Vector3(vel.x, vel.y, vel.z) * t;
}
