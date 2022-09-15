#include "physics.hh"


MyPhysicsList::MyPhysicsList()
{
RegisterPhysics(new G4HadronPhysicsFTFP_BERT());
RegisterPhysics(new G4EmStandardPhysics());
 //RegisterPhysics(new QGSP_BERT());
  //AddPhysicsList("QGSP_BERT");
 // RegisterPhysics(new G4OpticalPhysics());
}

MyPhysicsList::~MyPhysicsList()
{}
