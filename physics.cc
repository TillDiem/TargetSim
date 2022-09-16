#include "physics.hh"


MyPhysicsList::MyPhysicsList()
{
RegisterPhysics(new G4HadronPhysicsQGSP_BERT());
RegisterPhysics(new G4EmStandardPhysics());
RegisterPhysics(new G4OpticalPhysics());
RegisterPhysics(new G4DecayPhysics());
RegisterPhysics(new G4HadronElasticPhysics());
RegisterPhysics(new G4HadronDElasticPhysics());
RegisterPhysics(new G4HadronHElasticPhysics());
RegisterPhysics(new G4ChargeExchangePhysics());
RegisterPhysics(new G4NeutronTrackingCut());
RegisterPhysics(new G4IonBinaryCascadePhysics());
RegisterPhysics(new G4IonPhysics());

}

MyPhysicsList::~MyPhysicsList()
{}
