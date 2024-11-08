#include "WindForceGenerator.h"

WindForceGenerator::WindForceGenerator(Vector3 windVel, float windCoef, float k1, float k2) : windVel(windVel), windCoef(windCoef), k1(k1), k2(k2)
{
}

WindForceGenerator::~WindForceGenerator()
{
}

void WindForceGenerator::UpdateForce(Particle* p, double t)
{
    Vector3 velDiff = windVel - p->getVel();
    force = k1 * velDiff + k2 * (velDiff).magnitude() * velDiff;
    p->applyForce(force);
}
