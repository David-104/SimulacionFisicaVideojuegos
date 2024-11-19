#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(double k, double restingLength, Vector3 p) : _k(k), _restingLength(restingLength), _pos(p)
{
}

SpringForceGenerator::~SpringForceGenerator()
{
}

void SpringForceGenerator::UpdateForce(Particle* p, double t)
{
    Vector3 relativePos = _pos - p->getTransform()->p;

    float length = relativePos.normalize();
    float deltaX = length - _restingLength;

    force = relativePos * deltaX * _k;

    p->applyForce(force);
}


