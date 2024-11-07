#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

//#include "Vector3D.h"
#include "Particle.h"
#include "Proyectile.h"
#include "ParticleSystem.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"

std::string display_text = "This is a test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

std::vector<RenderItem*> renderItems;
std::vector<Proyectile*> proyectiles;
std::vector<ParticleSystem*> particleSystems;
enum ProyectileType {Bullet, Fireball, Energy };
ProyectileType currentProyectile = Bullet;


/*void customVector3DTests() {
	Vector3D patata(5.0, 0.0, 0.0);
	cout << patata << endl;

	Vector3D tomate(1.0, 2.0, 3.0);
	cout << tomate << endl;

	float module = patata.Module();
	cout << module << endl;

	cout << patata.Normalized() << endl;
	cout << patata << " ";
	patata.Normalize();
	cout << patata << endl;

	cout << patata + tomate << endl;

	cout << patata * 7 << endl;

	cout << patata * tomate << endl;

	cout << (tomate == patata) << " ";
	tomate = patata;
	cout << (tomate == patata);
}*/

void createAxis() {
	PxShape* shape = CreateShape(PxSphereGeometry(1));

	RenderItem* aux;
	Vector3 position1(0.0, 0.0, 0.0);
	PxTransform* tr1 = new PxTransform(position1);
	aux = new RenderItem(shape, tr1, PxVec4(1.0, 1.0, 1.0, 1.0));
	renderItems.push_back(aux);

	Vector3 position2(10.0, 0.0, 0.0);
	PxTransform* tr2 = new PxTransform(position2);
	aux = new RenderItem(shape, tr2, PxVec4(1.0, 0.0, 0.0, 1.0));
	renderItems.push_back(aux);

	Vector3 position3(0.0, 10.0, 0.0);
	PxTransform* tr3 = new PxTransform(position3);
	aux = new RenderItem(shape, tr3, PxVec4(0.0, 1.0, 0.0, 1.0));
	renderItems.push_back(aux);

	Vector3 position4(0.0, 0.0, 10.0);
	PxTransform* tr4 = new PxTransform(position4);
	aux = new RenderItem(shape, tr4, PxVec4(0.0, 0.0, 1.0, 1.0));
	renderItems.push_back(aux);
}

void ShootProyectile(ProyectileType type) {
	Camera* cam = GetCamera();
	Vector3 pos = cam->getTransform().p;
	Vector3 dir = cam->getDir();

	Vector3 a;
	float speed, damping, gravity, mass, scalingFactor;
	PxShape* shape;
	Vector4 color;

    switch (type)
    {
    case Bullet:
		speed = 100.0;
		a = Vector3(0.0, 0.0, 0.0);
		damping = 0.75;
		gravity = -9.8;
		mass = 1.0;
		scalingFactor = 0.5;
		shape = CreateShape(PxSphereGeometry(0.25));
		color = { 0.75, 0.75, 0.0, 1.0 };
		break;
    case Fireball:
		speed = 50.0;
		a = Vector3(0.0, 0.0, 0.0);
		damping = 0.75;
		gravity = -9.8;
		mass = 10.0;
		scalingFactor = 0.5;
		shape = CreateShape(PxSphereGeometry(1.5));
		color = { 1.0, 0.0, 0.0, 1.0 };
		break;
    case Energy:
		speed = 75.0;
		a = Vector3(0.0, 0.0, 0.0);
		damping = 0.75;
		gravity = 9.8;
		mass = 100.0;
		scalingFactor = 0.5;
		shape = CreateShape(PxBoxGeometry(0.5, 0.5, 0.5));
		color = { 0.0, 0.5, 1.0, 1.0 };
		break;
    default: //no deberia pasar nunca pero nunca se sabe
		speed = 10.0;
		a = Vector3(0.0, 0.0, 0.0);
		damping = 0.75;
		gravity = -9.8;
		mass = 1.0;
		scalingFactor = 0.5;
		shape = CreateShape(PxSphereGeometry(1));
		color = { 0.0, 0.0, 0.0, 0.0 }; 
        break;
    }
	Proyectile* proyectile = new Proyectile(pos, dir * speed, a, damping, gravity, mass, scalingFactor, shape, color);
	proyectiles.push_back(proyectile);
}

// Initialize physics engine
void initPhysics(bool interactive)
{
	//customVector3DTests();

	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	createAxis();

	//manera super sucia de los diferentes sistemas pero bueno

	/*//sistema de "niebla"
	particleSystems.push_back(new ParticleSystem(100, Vector3(0, 0, 0), ParticleSystem::GeneratorType::GAUSSIAN, Vector3(0.0, 1.0, 0.0), Vector3(10.0, 0.0, 10.0)));
	ParticleSystem::ModelParticleData model;
	model.acceleration = Vector3(0.0, 0.0, 0.0);
	model.gravity = -9.8;
	model.damping = 1.0;
	model.shape = CreateShape(PxSphereGeometry(5));
	model.color = Vector4(1.0, 1.0, 1.0, 1.0);
	particleSystems[0]->setModelParticle(model);

	//sistema de "manguera"
	particleSystems.push_back(new ParticleSystem(100, Vector3(0, 0, 0), ParticleSystem::GeneratorType::GAUSSIAN, Vector3(10.0, 1.0, 0.1), Vector3(0.0, 0.0, 0.0)));
	model.shape = CreateShape(PxCapsuleGeometry(0.5, 1));
	model.color = Vector4(0.0, 0.75, 0.75, 1.0);
	particleSystems[1]->setModelParticle(model);

	//sistema de "explosion"
	particleSystems.push_back(new ParticleSystem(100, Vector3(0, 0, 0), ParticleSystem::GeneratorType::UNIFORM, Vector3(10.0, 10.0, 10.0), Vector3(0.0, 0.0, 0.0)));
	model.shape = CreateShape(PxSphereGeometry(1));
	model.color = Vector4(1.0, 0.0, 0.0, 1.0);
	particleSystems[2]->setModelParticle(model);*/

	ParticleSystem::ModelParticleData model;
	model.acceleration = Vector3(0.0, 0.0, 0.0);
	model.gravity = 0.0;
	model.damping = 1.0;
	model.shape = CreateShape(PxSphereGeometry(1));
	model.color = Vector4(0.0, 0.75, 0.75, 1.0);
	model.mass = 0.1;
	particleSystems.push_back(new ParticleSystem(100, Vector3(0, 0, 0), ParticleSystem::GeneratorType::GAUSSIAN, Vector3(10.0, 1.0, 0.1), Vector3(0.0, 0.0, 0.0)));
	particleSystems[0]->setModelParticle(model);

	/*GravityForceGenerator* fg = new GravityForceGenerator(-10);
	GravityForceGenerator* fg2 = new GravityForceGenerator(100);
	particleSystems[0]->AddForceGenerator(fg);
	particleSystems[0]->AddForceGenerator(fg2);*/

	WindForceGenerator* wfg = new WindForceGenerator(Vector3(0.0, 0.0, -100.0), 0.0, 1.0, 0.0);
	particleSystems[0]->AddForceGenerator(wfg);
}

    
// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
	for each (Proyectile* proyectile in proyectiles)
	{
		proyectile->Integrate(t);
	}

    for each (ParticleSystem* ps in particleSystems)
    {
        ps->Update(t);
    }
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{

	for each (Proyectile * proyectile in proyectiles)
	{
		proyectile->~Proyectile();
	}

	for each (RenderItem* renderItem in renderItems)
	{
		DeregisterRenderItem(renderItem);
	}


	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case 'Z':
	{
		ShootProyectile(currentProyectile);
		break;
	}
	case '1':
	{
		currentProyectile = Bullet;
		break;
	}
	case '2':
	{
		currentProyectile = Fireball;
		break;
	}
	case '3':
	{
		currentProyectile = Energy;
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}

int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}
