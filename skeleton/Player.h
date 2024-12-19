#pragma once
#include "SolidoRigido.h"
using namespace physx;
class Player
{
public:
    Player(Vector3 pos, PxScene* scene, PxPhysics* physics, Camera* cam);
    ~Player();
    void update();
    void movement();
    void processInput(unsigned char key);
    void jump();
private:
    PxScene* scene = nullptr;
    PxPhysics* physics = nullptr;
    Camera* cam = nullptr;
    PxRigidDynamic* rigid = nullptr;
    PxVec2 inputDirection = {0, 0};
};

