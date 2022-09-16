#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"
#include "G4HadronPhysicsFTFQGSP_BERT.hh"
#include "G4HadronPhysicsQGSP_BERT.hh"
#include "G4DecayPhysics.hh"



class MyPhysicsList : public G4VModularPhysicsList
{
public:
  MyPhysicsList();
  ~MyPhysicsList();

};


#endif
