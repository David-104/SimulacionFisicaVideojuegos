#include "SolidoRigidoSystem.h"

#include <iostream>

#include "SolidGaussianGenerator.h"
#include "SolidGenerator.h"
#include "SolidUniformGenerator.h"

SolidoRigidoSystem::SolidoRigidoSystem(PxScene* scene, PxPhysics* physics, float solidLife, Vector3 pos, GeneratorType type, Vector3 meanVel,
                                       Vector3 meanPos, float maxSolNum, float maxSolDist) : scene(scene), physics(physics), MAX_SOLIDOS_NUM(maxSolNum), MAX_SOLIDOS_DIST(maxSolDist), pos(pos)
{
	SolidGenerator* sg;
	switch (type)
	{
	case NONE:
		break;
	case UNIFORM:
		sg = new SolidUniformGenerator(this, meanVel, meanPos);
		break;
	case GAUSSIAN:
		sg = new SolidGaussianGenerator(this, 5.0, meanVel, meanPos);
		break;
	}
	generators.push_back(sg);

	modelSolido.shape = CreateShape(PxBoxGeometry(1, 1, 1));
	modelSolido.color = Vector4(1.0, 0.0, 0.0, 1.0);
	modelSolido.tensor = Vector3(1 / 6 * 1 * pow(1, 2));
	modelSolido.solidoLife = solidLife;
}

SolidoRigidoSystem::~SolidoRigidoSystem()
{
	for each (auto solido in solidos)
	{
		delete solido;
	}

	for each (SolidGenerator * gen in generators)
	{
		delete gen;
	}
}

void SolidoRigidoSystem::Update(double t)
{
	if (solidos.size() < MAX_SOLIDOS_NUM) //&& generators.size() > 0
		updateGenerators(t);

	/*if (forceGenerators.size() > 0)
		UpdateForceGenerators(t);*/

	updateSolidos(t);

	std::cout << solidos.size() << std::endl;
}

void SolidoRigidoSystem::addSolidoRigido(SolidoRigido* solido)
{
	solidos.push_back(solido);
}

void SolidoRigidoSystem::setModelSolidoRigido(ModelSolidoRigido ms)
{
	modelSolido = ms;
}

void SolidoRigidoSystem::UpdateForceGenerators(double t)
{
	/*for each (ForceGenerator * fg in forceGenerators)
	{
		for each (SolidoData data in solidos)
		{
			fg->UpdateForce(data.solido, t);
		}
	}*/
}

void SolidoRigidoSystem::createSpring1Demo()
{
}

void SolidoRigidoSystem::createSpring2Demo()
{
}

void SolidoRigidoSystem::createSpringRubberDemo()
{
}

void SolidoRigidoSystem::createBuoyancyDemo()
{
}

void SolidoRigidoSystem::applyForceToSolidosRigidos(Vector3 force)
{
	for (auto solido : solidos)
	{
		solido->addForce(force);
	}
}

void SolidoRigidoSystem::updateSolidos(double t)
{

	for (std::list<SolidoRigido*>::iterator it = solidos.begin(); it != solidos.end(); it++) {
		float dist = Vector3((*it)->getPose()->p - pos).magnitude();

		if ((dist < MAX_SOLIDOS_DIST || MAX_SOLIDOS_DIST != -1) && (*it)->isAlive()) //max solidos dist = -1 significa que no tienen distancia limite
			(*it)->update(t);
		else
			solidosToErase.push_back(it);
	}

	removeSolidos();
}

void SolidoRigidoSystem::updateGenerators(double t)
{
	for each (SolidGenerator * pg in generators)
	{
		pg->update(t);
	}
}

void SolidoRigidoSystem::removeSolidos()
{
	for each (auto it in solidosToErase)
	{
		(*it)->~SolidoRigido();
		solidos.erase(it);
	}
	solidosToErase.clear();
}
