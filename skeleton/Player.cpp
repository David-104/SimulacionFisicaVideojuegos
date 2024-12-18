#include "Player.h"

#include <iostream>

#include "RenderUtils.hpp"

float const PLAYER_SPEED = 500;

Player::Player(Vector3 pos, PxScene* scene, PxPhysics* physics, Camera* cam) : scene(scene), physics(physics), cam(cam)
{
    PxTransform transform = PxTransform(pos);
    rigid = physics->createRigidDynamic(transform);
    auto shape = CreateShape(PxBoxGeometry(1, 2, 1));
    rigid->attachShape(*shape);
    PxRigidBodyExt::updateMassAndInertia(*rigid, 0.15);
    scene->addActor(*rigid);
}

Player::~Player()
{
}

void Player::update()
{
    std::cout << "{ " << inputDirection.x << ", " << inputDirection.y << " }\n";
    movement();
    cam->setEye(rigid->getGlobalPose().p + Vector3(0, 2, 0));
}

void Player::movement()
{
    Vector3 camForward = cam->getDir();
    camForward.y = 0;
    camForward.normalize();
    Vector3 camRight = Vector3(0, 1, 0).cross(camForward);
    camRight.y = 0;
    camRight.normalize();

    Vector3 movementDir = Vector3(camForward * inputDirection.x + camRight * inputDirection.y);
    movementDir.normalize();
    rigid->setLinearVelocity(movementDir * PLAYER_SPEED);
    inputDirection = { 0, 0 };
}

void Player::processInput(unsigned char key)
{
    switch(key)
    {
    case 'W':
        inputDirection = { 1, 0 };
        break;
    case 'A':
        inputDirection = { 0, 1 };
        break;
    case 'S':
        inputDirection = { -1, 0 };
        break;
    case 'D':
        inputDirection = { 0, -1 };
        break;
    default:
        inputDirection = { 0, 0 };
        break;
    }
}
