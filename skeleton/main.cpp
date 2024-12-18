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
#include "WhirlwindForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "Player.h"
#include "SolidoRigido.h"
#include "SolidoRigidoSystem.h"
#include "SolidoWindGenerator.h"

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


//cosas mias no de Physx
std::vector<RenderItem*> renderItems;
std::vector<Proyectile*> proyectiles;
std::vector<ParticleSystem*> particleSystems;
std::vector<SolidoRigidoSystem*> solidosSystems;
ExplosionForceGenerator* efg;
enum ProyectileType {Bullet, Fireball, Energy };
ProyectileType currentProyectile = Bullet;
Player* player;

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

void createGravityForceGenerator() {
	ParticleSystem::ModelParticleData model;
	model.acceleration = Vector3(0.0, 0.0, 0.0);
	model.gravity = 0.0;
	model.damping = 1.0;
	model.shape = CreateShape(PxSphereGeometry(1));
	model.color = Vector4(0.0, 0.75, 0.75, 1.0);
	model.mass = 0.1;
	ParticleSystem* ps = new ParticleSystem(10000, Vector3(0, 0, 0), ParticleSystem::GeneratorType::GAUSSIAN, Vector3(10.0, 1.0, 0.1), Vector3(0.0, 0.0, 0.0));
	particleSystems.push_back(ps);
	ps->setModelParticle(model);

	GravityForceGenerator* fg = new GravityForceGenerator(-10);
	GravityForceGenerator* fg2 = new GravityForceGenerator(100);
	ps->AddForceGenerator(fg);
	ps->AddForceGenerator(fg2);
}

void createWindForceGenerator() {
	ParticleSystem::ModelParticleData model;
	model.acceleration = Vector3(0.0, 0.0, 0.0);
	model.gravity = 0.0;
	model.damping = 1.0;
	model.shape = CreateShape(PxSphereGeometry(1));
	model.color = Vector4(0.0, 0.75, 0.75, 1.0);
	model.mass = 0.1;
	ParticleSystem* ps = new ParticleSystem(10000, Vector3(0, 0, 0), ParticleSystem::GeneratorType::GAUSSIAN, Vector3(10.0, 1.0, 0.1), Vector3(0.0, 0.0, 0.0));
	particleSystems.push_back(ps);
	ps->setModelParticle(model);

	WindForceGenerator* wfg = new WindForceGenerator(Vector3(0.0, 0.0, -100.0), 0.0, 1.0, 0.0);
	ps->AddForceGenerator(wfg);
}

void createWhirlwindForceGenerator() {
	ParticleSystem::ModelParticleData model;
	model.acceleration = Vector3(0.0, 0.0, 0.0);
	model.gravity = 0.0;
	model.damping = 1.0;
	model.shape = CreateShape(PxSphereGeometry(1));
	model.color = Vector4(0.0, 0.75, 0.75, 1.0);
	model.mass = 0.1;
	ParticleSystem* ps = new ParticleSystem(100, Vector3(0, 0, 0), ParticleSystem::GeneratorType::GAUSSIAN, Vector3(10.0, 1.0, 10.0), Vector3(0.0, 0.0, 0.0), 10000, 1000);
	particleSystems.push_back(ps);
	ps->setModelParticle(model);

	WhirlwindForceGenerator* torbellino = new WhirlwindForceGenerator(Vector3(0), 0.0, 1.0, 0.0, 50.0, 50.0);
	ps->AddForceGenerator(torbellino);
}

void createExplosionForceGenerator() {
	ParticleSystem::ModelParticleData model;
	model.acceleration = Vector3(0.0, 0.0, 0.0);
	model.gravity = 0.0;
	model.damping = 1.0;
	model.shape = CreateShape(PxSphereGeometry(1));
	model.color = Vector4(1.0, 0.0, 0.0, 1.0);
	model.mass = 0.1;
	ParticleSystem* ps = new ParticleSystem(200, Vector3(0.1, 0, 0.1), ParticleSystem::GeneratorType::UNIFORM, Vector3(0.1, 0.1, 0.1), Vector3(0.0, 0.0, 0.0));
	particleSystems.push_back(ps);
	ps->setModelParticle(model);

	efg = new ExplosionForceGenerator(Vector3(0), 10.0, 500.0, 1.0);
	ps->AddForceGenerator(efg);
}

void createSpring1Demo()
{
	Vector3 pos = Vector3(0, 10, 0);
	ParticleSystem* ps = new ParticleSystem(-1, pos);
	particleSystems.push_back(ps);
	ps->createSpring1Demo();

	PxShape* shape = CreateShape(PxBoxGeometry(1, 1, 1));
	RenderItem* aux;
	PxTransform* tr1 = new PxTransform(pos);
	aux = new RenderItem(shape, tr1, PxVec4(0.0, 0.0, 0.0, 1.0));
	renderItems.push_back(aux);
}

void createSpring2Demo()
{
	Vector3 pos = Vector3(0, 0, 0);
	ParticleSystem* ps = new ParticleSystem(-1, pos);
	particleSystems.push_back(ps);
	ps->createSpring2Demo();
}


void createSpringRubberDemo()
{
	Vector3 pos = Vector3(0, 0, 0);
	ParticleSystem* ps = new ParticleSystem(-1, pos);
	particleSystems.push_back(ps);
	ps->createSpringRubberDemo();
}

void createBuoyancyDemo()
{
	Vector3 pos = Vector3(0, 0, 0);
	ParticleSystem* ps = new ParticleSystem(-1, pos);
	particleSystems.push_back(ps);
	ps->createBuoyancyDemo();
}

void solidoRigido1Demo()
{
	float width = 2.0, height = 1.0, depth = 1.0;
	PxShape* shape = CreateShape(PxBoxGeometry(width, height, depth));
	float mass = 1.0;
	SolidoRigido* rigido = new SolidoRigido(Vector3(0.0, 20.0, 0.0), shape, gScene, gPhysics, Vector4(1.0, 0.0, 0.0, 1.0));
	Vector3 tensor = Vector3(1 / 12 * mass * (pow(depth, 2) + pow(height, 2)),
		1 / 12 * mass * (pow(width, 2) + pow(depth, 2)),
		1 / 12 * mass * (pow(width, 2) + pow(height, 2)));
	rigido->setMass(mass);
	rigido->setMassSpaceInertiaTensor(tensor);

	PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform(Vector3(0)));
	PxShape* shapeSuelo = CreateShape(PxBoxGeometry(100.0, 1.0, 100.0));
	suelo->attachShape(*shapeSuelo);
	gScene->addActor(*suelo);

	RenderItem* sueloRI = new RenderItem(shapeSuelo, suelo, Vector4(1));
}

void solidoRigido2Demo()
{
	//esta el problemilla de que se generan a veces unos dentros de otros y salen volando, pero quitando eso funciona

	SolidoRigidoSystem::ModelSolidoRigido model;
	model.shape = CreateShape(PxBoxGeometry(1, 1, 1));
	model.color = Vector4(1.0, 0.0, 0.0, 1.0);
	model.tensor = Vector3(1 / 6 * 1 * pow(1, 2));
	model.solidoLife = 5;

	SolidoRigidoSystem* sys = new SolidoRigidoSystem(gScene, gPhysics, 10, Vector3(0), SolidoRigidoSystem::GAUSSIAN, Vector3(1, 1, 1), Vector3(1, 1, 1), 100, 100);
	solidosSystems.push_back(sys);
	sys->setModelSolidoRigido(model);

	SolidoRigidoSystem::ModelSolidoRigido model2;
	model2.shape = CreateShape(PxBoxGeometry(3, 3, 3));
	model2.color = Vector4(0.0, 0.0, 1.0, 1.0);
	model2.tensor = Vector3(1 / 6 * 2 * pow(3, 2));
	model2.solidoLife = 2;

	SolidoRigidoSystem* sys2 = new SolidoRigidoSystem(gScene, gPhysics, 10, Vector3(0), SolidoRigidoSystem::UNIFORM, Vector3(1, 1, 1), Vector3(10, 1, 10), 100, 100);
	solidosSystems.push_back(sys2);
	sys2->setModelSolidoRigido(model2);


	PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform(Vector3(0)));
	PxShape* shapeSuelo = CreateShape(PxBoxGeometry(100.0, 1.0, 100.0));
	suelo->attachShape(*shapeSuelo);
	gScene->addActor(*suelo);

	RenderItem* sueloRI = new RenderItem(shapeSuelo, suelo, Vector4(1));


	SolidoWindGenerator* wg = new SolidoWindGenerator(Vector3(0.0, 0.0, -1000.0), 0.0, 1.0, 0.0);
	sys2->AddForceGenerator(wg);
}

void createGameScene()
{
	PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform(Vector3(0)));
	PxShape* shapeSuelo = CreateShape(PxBoxGeometry(100.0, 1.0, 100.0));
	suelo->attachShape(*shapeSuelo);
	gScene->addActor(*suelo);
	RenderItem* sueloRI = new RenderItem(shapeSuelo, suelo, Vector4(1));

	PxRigidStatic* cubo = gPhysics->createRigidStatic(PxTransform(Vector3(0, 50, 0)));
	PxShape* cuboShape = CreateShape(PxBoxGeometry(5, 5, 5));
	suelo->attachShape(*cuboShape);
	gScene->addActor(*cubo);
	RenderItem* cuboRI = new RenderItem(cuboShape, cubo, Vector4(0, 0, 0, 1));

	//player
	player = new Player(Vector3(10, 5, 10), gScene, gPhysics, GetCamera());
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

	//createAxis();

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


	//createGravityForceGenerator();
	//createWindForceGenerator();
	//createWhirlwindForceGenerator();
	//createExplosionForceGenerator();

	//createSpring1Demo();
	//createSpring2Demo();
	//createSpringRubberDemo();
	//createBuoyancyDemo();

	//solidoRigido1Demo();
	//solidoRigido2Demo();

	createGameScene();
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

    for (auto solidoSys : solidosSystems)
    {
		solidoSys->Update(t);
    }

	player->update();
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

    for (auto particle_system : particleSystems)
    {
		delete particle_system;
    }

	for (auto solid_system : solidosSystems)
	{
		delete solid_system;
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
	player->processInput(toupper(key));
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	    case 'Z':
	    {
		    ShootProyectile(currentProyectile);
		    break;
	    }
	    case 'E':
	    {
		    if (efg != nullptr)
			    efg->resetTime();
		    break;
	    }
	    case 'P':
	    {
		    switch (currentProyectile)
		    {
		    case Bullet:
			    currentProyectile = Fireball;
			    break;
		    case Fireball:
			    currentProyectile = Energy;
			    break;
		    case Energy:
			    currentProyectile = Bullet;
			    break;
		    }
		    break;
	    }
	    case 'F':
	    {
		    if (particleSystems.size() > 0)
		    {
			    Vector3 force = Vector3(0, 100, 0);
			    particleSystems[0]->applyForceToParticles(force);
		    }
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
