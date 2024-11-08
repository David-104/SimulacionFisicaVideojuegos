#include "WhirlwindForceGenerator.h"

WhirlwindForceGenerator::WhirlwindForceGenerator(Vector3 centre, float windCoef, float k1, float k2, float whirlwindForce, float height) : WindForceGenerator(Vector3(0), windCoef, k1, k2), centre(centre), whirlwindForce(whirlwindForce), height(height)
{
}

WhirlwindForceGenerator::~WhirlwindForceGenerator()
{
}

void WhirlwindForceGenerator::UpdateForce(Particle* p, double t)
{
    Vector3 particlePos = p->getTransform()->p;
    windVel = whirlwindForce * Vector3(-(particlePos.z - centre.z), height - (particlePos.y - centre.y), particlePos.x - centre.x).getNormalized();
    WindForceGenerator::UpdateForce(p, t);
}
