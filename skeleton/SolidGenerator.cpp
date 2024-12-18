#include "SolidGenerator.h"

SolidGenerator::SolidGenerator(SolidoRigidoSystem* sys, Vector3 meanVel, Vector3 meanPos) : solidoSys(sys), meanVel(meanVel), meanPos(meanPos)
{

}

SolidGenerator::~SolidGenerator()
{
}

void SolidGenerator::update(double dt)
{
    solidoSys->addSolidoRigido(createSolido());
}
