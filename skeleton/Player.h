#pragma once
#include <list>

#include "ForceGenerator.h"
#include "SolidoForceGenerator.h"
#include "SolidoRigido.h"
using namespace physx;
class Player :SolidoRigido
{
public:
    Player(Vector3 pos, PxScene* scene, PxPhysics* physics, Camera* cam);
    ~Player();
    void update(double dt) override;
    void movement();
    void processInput(unsigned char key);
    void jump();
    void shootGrapplingHook();
    void createGrapplingHook(Vector3 pos);
    void removeGrapplingHook();
private:
    Camera* cam = nullptr;
    PxVec2 inputDirection = {0, 0};
    std::list<SolidoForceGenerator*> forceGenerators;
    SolidoForceGenerator* grapplingHook = nullptr;
};

