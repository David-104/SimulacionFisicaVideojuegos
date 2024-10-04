#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

#include "Vector3D.h"
#include "Particle.h"
#include "Proyectile.h"

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


RenderItem* center = nullptr;
RenderItem* xAxis = nullptr;
RenderItem* yAxys = nullptr;
RenderItem* zAxis = nullptr;
Proyectile* proyectile = nullptr;

void customVector3DTests() {
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
}

void createAxis() {
	PxShape* shape = CreateShape(PxSphereGeometry(1));

	Vector3D position1(0.0, 0.0, 0.0);
	PxTransform* tr1 = new PxTransform(PxVec3(position1.x, position1.y, position1.z));
	center = new RenderItem(shape, tr1, PxVec4(1.0, 1.0, 1.0, 1.0));

	Vector3D position2(10.0, 0.0, 0.0);
	PxTransform* tr2 = new PxTransform(PxVec3(position2.x, position2.y, position2.z));
	xAxis = new RenderItem(shape, tr2, PxVec4(1.0, 0.0, 0.0, 1.0));

	Vector3D position3(0.0, 10.0, 0.0);
	PxTransform* tr3 = new PxTransform(PxVec3(position3.x, position3.y, position3.z));

	yAxys = new RenderItem(shape, tr3, PxVec4(0.0, 1.0, 0.0, 1.0));

	Vector3D position4(0.0, 0.0, 10.0);
	PxTransform* tr4 = new PxTransform(PxVec3(position4.x, position4.y, position4.z));
	zAxis = new RenderItem(shape, tr4, PxVec4(0.0, 0.0, 1.0, 1.0));
}

void cleanupAxis() {
	DeregisterRenderItem(center);
	DeregisterRenderItem(xAxis);
	DeregisterRenderItem(yAxys);
	DeregisterRenderItem(zAxis);
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

	proyectile = new Proyectile(Vector3D(0.0, 0.0, 0.0), Vector3D(0.0, 0.0, 0.0), Vector3D(10.0, 0.0, 0.0), 0.75, 1.0, -9.8, 0.5);
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
	proyectile->Integrate(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	proyectile->~Proyectile();
	cleanupAxis();


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
	case ' ':
	{
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
