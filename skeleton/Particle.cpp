#include "Particle.h"
#include <cmath>

enum IntegrationModes { EULER, SEMI, VERLET };

constexpr IntegrationModes INTEGRATION_MODE = EULER;

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 a = Vector3(0, 0, 0), float d = 1, float g = 0) : vel(vel), a(a), d(d), gravity(g), forceApplied(Vector3(0))
{
	pose = new PxTransform(pos);

	PxShape* shape = CreateShape(PxSphereGeometry(1));
	renderItem = new RenderItem(shape, pose, Vector4(0.0, 0.0, 0.0, 1.0));
}

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 a, float d, float g, float mass) : vel(vel), a(a), d(d), gravity(g), mass(mass), forceApplied(Vector3(0))
{
	pose = new PxTransform(pos);

	PxShape* shape = CreateShape(PxSphereGeometry(1));
	renderItem = new RenderItem(shape, pose, Vector4(0.0, 0.0, 0.0, 1.0));
}

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 a, float d, float g, PxShape* shape, const Vector4& color) : vel(vel), a(a), d(d), gravity(g), forceApplied(Vector3(0))
{
	pose = new PxTransform(pos);
	renderItem = new RenderItem(shape, pose, color);
}

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 a, float d, float gravity, PxShape* shape, const Vector4& color, float mass) : vel(vel), a(a), d(d), gravity(gravity), mass(mass), forceApplied(Vector3(0))
{
	pose = new PxTransform(pos);
	renderItem = new RenderItem(shape, pose, color);
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::Integrate(double t)
{
	a = forceApplied / mass;

	switch (INTEGRATION_MODE)
	{
	case EULER:
		pose->p = pose->p + vel * t;
		vel = vel * pow(d, t) + (a + Vector3(0, 1, 0) * gravity) * t;
		break;
	case SEMI:
		vel = vel * pow(d, t) + (a + Vector3(0, 1, 0) * gravity) * t;
		pose->p = pose->p + vel * t;
	case VERLET:
		break;
	}

	forceApplied = Vector3(0.0, 0.0, 0.0);
}

void Particle::applyForce(Vector3 force)
{
	forceApplied += force;
}
