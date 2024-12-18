#pragma once
#include "core.hpp"
#include "SolidoRigidoSystem.h"

class SolidGenerator
{
public:
    SolidGenerator(SolidoRigidoSystem* sys, Vector3 meanVel, Vector3 meanPos);
    ~SolidGenerator();
    void update(double t);
protected:
    virtual SolidoRigido* createSolido() { return nullptr; }
    Vector3 meanPos;
    Vector3 meanVel;
    SolidoRigidoSystem* solidoSys;
};

