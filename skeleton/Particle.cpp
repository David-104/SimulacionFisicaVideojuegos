#include "Particle.h"
#include <cmath>

enum IntegrationModes { EULER, SEMI, VERLET };

constexpr IntegrationModes INTEGRATION_MODE = EULER;


Particle::Particle(Vector3D pos, Vector3D vel, Vector3D a = Vector3D(0, 0, 0), float d = 1, float g = 0) : vel(vel), a(a), d(d), gravity(g)
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
	switch (INTEGRATION_MODE)
	{
	case EULER:
		pose->p = pose->p + Vector3(vel.x, vel.y, vel.z) * t;
		vel = vel * pow(d, t) + (a + Vector3D(0, 1, 0) * gravity) * t;
		break;
	case SEMI:
		vel = vel * pow(d, t) + (a + Vector3D(0, 1, 0) * gravity) * t;
		pose->p = pose->p + Vector3(vel.x, vel.y, vel.z) * t;
	case VERLET:
		break;
	default:
		break;
	}
}
