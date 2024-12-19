#pragma once
#include "SolidoRigido.h"
class Player;

class ProyectilGancho : public SolidoRigido
{
public:
    ProyectilGancho(PxScene* scene, PxPhysics* physics, Vector3 pos, Vector3 vel, PxShape* shape);
    ~ProyectilGancho();
    void onCollision();
};

