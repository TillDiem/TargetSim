#include "physics.hh"


MyPhysicsList::MyPhysicsList()
{
RegisterPhysics(new G4HadronPhysicsQGSP_BERT());
RegisterPhysics(new G4EmStandardPhysics());
RegisterPhysics(new G4OpticalPhysics());
RegisterPhysics(new G4DecayPhysics());
 //RegisterPhysics(new QGSP_BERT());
  //AddPhysicsList("QGSP_BERT");
}

MyPhysicsList::~MyPhysicsList()
{}
