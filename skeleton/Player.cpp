#include "Player.h"

#include <iostream>

#include "RenderUtils.hpp"

float const PLAYER_SPEED_LIMIT = 50; 
float const PLAYER_SPEED_FORCE = 1000; //valor alto para que el movimiento sea instantaneo
float const JUMP_FORCE = 100;

Player::Player(Vector3 pos, PxScene* scene, PxPhysics* physics, Camera* cam) : scene(scene), physics(physics), cam(cam)
{
    float mass = 1.0;
    float radius = 0.5;
    float height = 2;
    PxTransform transform = PxTransform(pos);
    rigid = physics->createRigidDynamic(transform);

    //ya que physx no tiene geometria de cilindro asumimos que una capsula es un cilindro (en este caso de altura 2 y radio 0.5) para calcular el tensor de inercia
    auto shape = CreateShape(PxCapsuleGeometry(0.5, 0.5));
    //setear material del jugador
    PxMaterial* material = physics->createMaterial(0.0, 10.0, 0.0);
    shape->setMaterials(&material, 1);
    rigid->attachShape(*shape);
    rigid->setMass(mass);

    //tensor de un cilindro porque el de la capsula es mucho mas complicado
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
    std::cout << "{ " << rigid->getLinearVelocity().x << ", " << rigid->getLinearVelocity().z << " }\n";
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

    //movimiento por fuerzas en vez de por velocidad por si acaso para que no interfiera con los muelles
    rigid->addForce(movementDir * PLAYER_SPEED_FORCE);

    //esto deberia de limitar la velocidad a la deseada para que aunque el movimiento sea por fuerzas no sea cada vez mayor al estar sumando fuerzas constantemente
    if (rigid->getLinearVelocity().magnitude() > PLAYER_SPEED_LIMIT)
    {
        Vector3 newVel = Vector3(rigid->getLinearVelocity().x, 0, rigid->getLinearVelocity().z).getNormalized() * PLAYER_SPEED_LIMIT;
        newVel += Vector3(0, rigid->getLinearVelocity().y, 0);
        rigid->setLinearVelocity(newVel);
    }
   
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
    case ' ': //espacio
        jump();
    default:
        inputDirection = { 0, 0 };
        break;
    }
}

void Player::jump()
{
    rigid->addForce(Vector3(0, JUMP_FORCE, 0));
}
