#include "RubberForceGenerator.h"

#include <iostream>
#include <ostream>

RubberForceGenerator::RubberForceGenerator(double k, double restingLength, Particle* p) : ParticleSpringForceGenerator(k, restingLength, p)
{
}

RubberForceGenerator::~RubberForceGenerator()
{
}

void RubberForceGenerator::UpdateForce(Particle* p, double t)
{
    Vector3 relativePos = particle->getTransform()->p - p->getTransform()->p;

    float length = relativePos.normalize();
    float deltaX = length - _restingLength;
    //std:: cout << "Length: "<< length << " deltaX: " << deltaX << std::endl;
    if(deltaX > 0.0f) //significa que la goma se esta estirando y queremos fuerza
        force = relativePos * deltaX * _k;
    else //la goma no se esta estirando 
        force = Vector3(0);

    p->applyForce(force);
}