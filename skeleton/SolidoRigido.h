#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

using namespace physx;

class SolidoRigido
{
public:
    SolidoRigido(Vector3 pos, PxShape* shape, PxScene* scene, PxPhysics* physics, Vector4 color = Vector4(1.0), float life = 100, float density = 0.15);
    ~SolidoRigido();
    void update(double t);
    void addForce(Vector3 force);
    bool isAlive() { return alive; }
    void setMassSpaceInertiaTensor(Vector3 tensor);
    void setMass(float mass) { rigid->setMass(mass); }
    void setVel(Vector3 vel) { rigid->setLinearVelocity(vel); }
    const PxTransform* getPose() { return &rigid->getGlobalPose(); }
    Vector3 getVel() { return rigid->getLinearVelocity(); }
protected:
    PxRigidDynamic* rigid;
    RenderItem* renderItem;
    PxScene* scene;
    bool alive = true;
    float lifeTime;
    float lifeTimeTimer;
};
