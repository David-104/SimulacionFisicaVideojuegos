#include "SolidoRigido.h"

SolidoRigido::SolidoRigido(Vector3 pos, PxShape* shape, PxScene* scene, PxPhysics* physics, Vector4 color, float life, float density) : scene(scene)
{
    PxTransform transform = PxTransform(pos);
    rigid = physics->createRigidDynamic(transform);
    rigid->attachShape(*shape);
    PxRigidBodyExt::updateMassAndInertia(*rigid, density);
    scene->addActor(*rigid);

    renderItem = new RenderItem(shape, rigid, color);

    lifeTime = life;
    lifeTimeTimer = 0.0;
}

SolidoRigido::~SolidoRigido()
{
    scene->removeActor(*rigid);
    rigid->release();
    renderItem->release();
}

void SolidoRigido::update(double t)
{
    if(lifeTime != -1)
    {
        lifeTimeTimer += t;
        if (lifeTimeTimer > lifeTime)
            alive = false;
    }
}

void SolidoRigido::addForce(Vector3 force)
{
    rigid->addForce(force);
}

void SolidoRigido::setMassSpaceInertiaTensor(Vector3 tensor)
{
    rigid->setMassSpaceInertiaTensor(tensor);
}
