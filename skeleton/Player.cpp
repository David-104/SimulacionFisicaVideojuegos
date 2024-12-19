#include "Player.h"

#include <iostream>

#include "RenderUtils.hpp"

float const PLAYER_SPEED = 500;

Player::Player(Vector3 pos, PxScene* scene, PxPhysics* physics, Camera* cam) : scene(scene), physics(physics), cam(cam)
{
    float mass = 1.0;
    float radius = 0.5;
    float height = 2;
    PxTransform transform = PxTransform(pos);
    rigid = physics->createRigidDynamic(transform);

    //ya que physx no tiene geometria de cilindro asumimos que una capsula es un cilindro (en este caso de altura 2 y radio 0.5) para calcular el tensor de inercia
    auto shape = CreateShape(PxCapsuleGeometry(0.5, 0.5));
    rigid->attachShape(*shape);
    rigid->setMass(mass);

    Vector3 tensor = Vector3(1/12 * mass *(3 * pow(radius, 2) + pow(height, 2)),
        1/2 * mass * pow(radius, 2),
        1 / 12 * mass * (3 * pow(radius, 2) + pow(height, 2)));

    rigid->setMassSpaceInertiaTensor(tensor);

    //bloqueamos la rotacion para que el rigido de la capsula no se "caiga"
    rigid->setRigidDynamicLockFlags(PxRigidDynamicLockFlag::eLOCK_ANGULAR_X |
        PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y |
        PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);

    //no hace falta tener un renderItem porque es en primera persona y no se va a ver

    scene->addActor(*rigid);
}

Player::~Player()
{
}

void Player::update()
{
    //std::cout << "{ " << inputDirection.x << ", " << inputDirection.y << " }\n";
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

    //IMPORTANTE: decidir cual usar
    //movimiento por fuerzas
    //rigid->addForce(movementDir * PLAYER_SPEED);
    //movimiento por velocidad
    rigid->setLinearVelocity(movementDir * PLAYER_SPEED + Vector3(0, rigid->getLinearVelocity().y, 0)); //bastante feo lo de tener que añadir por separado la velocidad que ya existia en el eje y, pero el calculo del movimiento es como es y no tenog tiempo de hacerlo mas bonito
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
