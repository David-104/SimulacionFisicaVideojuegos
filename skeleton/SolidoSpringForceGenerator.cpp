#include "SolidoSpringForceGenerator.h"

SolidoSpringForceGenerator::SolidoSpringForceGenerator(double k, double restingLength, Vector3 p) : _k(k), _restingLength(restingLength), _pos(p)
{
}

SolidoSpringForceGenerator::~SolidoSpringForceGenerator()
{
}

void SolidoSpringForceGenerator::UpdateForce(SolidoRigido* solido, double t)
{
    Vector3 relativePos = _pos - solido->getPose()->p;

    float length = relativePos.normalize();
    float deltaX = length - _restingLength;

    if (deltaX > 0.0f)
        force = relativePos * deltaX * _k;
    else
        force = Vector3(0);

    solido->addForce(force);
}
