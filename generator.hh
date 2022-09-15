#ifndef GENERATOR_CC
#define GENERATOR_CC

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
	  MyPrimaryGenerator();
 	  ~MyPrimaryGenerator();
          virtual void GeneratePrimaries(G4Event* anEvent);
private:
	  G4ParticleGun* fParticleGun;

};

#endif
