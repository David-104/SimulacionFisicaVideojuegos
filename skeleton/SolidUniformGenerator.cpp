#include "SolidUniformGenerator.h"

SolidUniformGenerator::SolidUniformGenerator(SolidoRigidoSystem* sys, Vector3 meanVel, Vector3 meanPos) : SolidGenerator(sys, meanVel, meanPos)
{
    gen = std::mt19937(rd());
    distribution = std::uniform_real_distribution<>(-1.0, 1.0);
}

SolidUniformGenerator::~SolidUniformGenerator()
{
}

SolidoRigido* SolidUniformGenerator::createSolido()
{
	Vector3 pos = Vector3(meanPos.x * distribution(gen), meanPos.y * distribution(gen), meanPos.z * distribution(gen)) + solidoSys->getPos();

	Vector3 vel = Vector3(meanVel.x * distribution(gen), meanVel.y * distribution(gen), meanVel.z * distribution(gen));

	SolidoRigidoSystem::ModelSolidoRigido modelSolido = solidoSys->getModelSolidoRigido();

    SolidoRigido* solido = new SolidoRigido(pos, modelSolido.shape, solidoSys->getScene(), solidoSys->getPhysics(), modelSolido.color, modelSolido.solidoLife);
    solido->setMassSpaceInertiaTensor(modelSolido.tensor);
    solido->setVel(vel);

    return solido;
}
