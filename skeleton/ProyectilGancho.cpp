#include "ProyectilGancho.h"

#include "Player.h"

ProyectilGancho::ProyectilGancho(PxScene* scene, PxPhysics* physics, Vector3 pos, Vector3 vel, PxShape* shape) : SolidoRigido(pos, shape, scene, physics, Vector4(1.0, 1.0, 0.0, 1.0))
{
    rigid->setLinearVelocity(vel);
    rigid->setName("proyectilGancho");
}

ProyectilGancho::~ProyectilGancho()
{
    
}
