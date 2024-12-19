#pragma once
#include <list>
#include "ProyectilGancho.h"
#include "SolidoForceGenerator.h"
#include "SolidoRigido.h"

extern std::vector<SolidoRigido*> toDelete;
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
    void createGrapplingHook();
    void removeGrapplingHook();
    void removeProyectilGancho() { proyectilGancho = nullptr; }
    void addForceGenerator(SolidoForceGenerator* fg) { forceGenerators.push_back(fg); }
private:
    Camera* cam = nullptr;
    PxVec2 inputDirection = {0, 0};
    std::list<SolidoForceGenerator*> forceGenerators;
    SolidoForceGenerator* grapplingHook = nullptr;
    ProyectilGancho* proyectilGancho = nullptr;
};

