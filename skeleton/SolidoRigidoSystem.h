#pragma once
#include"SolidoRigido.h"
#include <list>

#include "SolidoForceGenerator.h"

//#include "ForceGenerator.h"
class SolidGenerator;
class SolidoRigidoSystem
{
public:
	enum GeneratorType {NONE, UNIFORM, GAUSSIAN };
	struct ModelSolidoRigido {
	    PxShape* shape;
		Vector4 color;
		Vector3 tensor;
		float solidoLife;
	};
	SolidoRigidoSystem(PxScene* scene, PxPhysics* physics, float solidLife = 100, Vector3 pos = Vector3(0), GeneratorType type = UNIFORM, Vector3 meanVel = Vector3(0), Vector3 meanPos = Vector3(0), float maxSolNum = 1000, float maxSolDist = 1000);
	~SolidoRigidoSystem();
	void Update(double t);
	void addSolidoRigido(SolidoRigido* solido);
	inline Vector3 getPos() { return pos; }
	inline ModelSolidoRigido getModelSolidoRigido() { return modelSolido; }
	void setModelSolidoRigido(ModelSolidoRigido ms);
	void UpdateForceGenerators(double t);
	inline void AddForceGenerator(SolidoForceGenerator* fg) { forceGenerators.push_back(fg); }

	void applyForceToSolidosRigidos(Vector3 force);
	PxScene* getScene() { return scene; }
	PxPhysics* getPhysics() { return physics; }
private:
	PxScene* scene;
	PxPhysics* physics;
	float MAX_SOLIDOS_NUM = 100;
	float MAX_SOLIDOS_DIST = 1000;
	Vector3 pos;
	ModelSolidoRigido modelSolido;

	std::list<SolidoRigido*> solidos;
	std::list<SolidGenerator*> generators;
	std::vector<std::list<SolidoRigido*>::iterator> solidosToErase;
	std::vector<SolidoForceGenerator*> forceGenerators;

	void updateSolidos(double t);
	void updateGenerators(double t);
	void removeSolidos();
};

