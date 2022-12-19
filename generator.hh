#ifndef GENERATOR_CC
#define GENERATOR_CC

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4Proton.hh"
#include "G4ParticleDefinition.hh"
#include "G4Neutron.hh"
#include "G4HadronicProcessStore.hh"
#include "G4HadronicProcess.hh"
#include "G4RootAnalysisManager.hh"

#include "TH1D.h"
#include "TFile.h"



class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
	  MyPrimaryGenerator();
 	  ~MyPrimaryGenerator();
          virtual void GeneratePrimaries(G4Event* anEvent);
private:
	  G4ParticleGun* fParticleGun;
	  TH1D* fSpectrum;

//    	  G4GenericMessenger* msg_; // Messenger for configuration parameters
};

#endif
