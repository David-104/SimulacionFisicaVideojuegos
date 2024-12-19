#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

using namespace physx;

class SolidoRigido
{
public:
    SolidoRigido(Vector3 pos, PxShape* shape, PxScene* scene, PxPhysics* physics, Vector4 color = Vector4(1.0), float life = -1, float density = 0.15);
    virtual ~SolidoRigido();
    virtual void update(double t);
    void addForce(Vector3 force);
    void setMassSpaceInertiaTensor(Vector3 tensor);
    void removeRenderItem();
    void setAlive(bool onoff) { alive = onoff; }
    bool isAlive() { return alive; }
    void setMass(float mass) { rigid->setMass(mass); }
    void setVel(Vector3 vel) { rigid->setLinearVelocity(vel); }
    const PxTransform* getPose() { return &rigid->getGlobalPose(); }
    Vector3 getVel() { return rigid->getLinearVelocity(); }
    PxRigidDynamic* getRigid() { return rigid; }
protected:
    PxRigidDynamic* rigid = nullptr;
    RenderItem* renderItem = nullptr;
    PxScene* scene = nullptr;
    bool alive = true;
    float lifeTime = -1;
    float lifeTimeTimer = 0;
};
