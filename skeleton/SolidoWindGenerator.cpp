#include "SolidoWindGenerator.h"

SolidoWindGenerator::SolidoWindGenerator(Vector3 windVel, float windCoef, float k1, float k2) : windVel(windVel), windCoef(windCoef), k1(k1), k2(k2)
{

}

SolidoWindGenerator::~SolidoWindGenerator()
{
}

void SolidoWindGenerator::UpdateForce(SolidoRigido* solido, double t)
{
    Vector3 velDiff = windVel - solido->getVel();
    force = k1 * velDiff + k2 * (velDiff).magnitude() * velDiff;
    solido->addForce(force);
}
