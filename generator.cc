#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	G4double primaryParticles = 1;
	fParticleGun = new G4ParticleGun(primaryParticles);

	// load root file
	TFile* fRootFile = new TFile("Sr90_spectrum.root");
	fSpectrum = (TH1D*)fRootFile->Get("h1");


	// Read in on start - later overwritten using a macro
	G4String particleName = "neutron";


	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition *particle = particleTable->FindParticle(particleName);

	if(particle){
		G4ThreeVector position(0,0,-0.5*m);
		G4ThreeVector momentumDirection(0,0,1);
		fParticleGun->SetParticleDefinition(particle);
		fParticleGun->SetParticlePosition(position);
		fParticleGun->SetParticleMomentumDirection(momentumDirection);
	}
	else{
		G4cout << "Particle " << particleName << " not found" << G4endl;
	}

	G4cout << "Primary generator initialized" << G4endl;



}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event* anEvent)
{

	G4cout << "Generating primary particles" << G4endl;
	G4double particleEnergy = 10*MeV;//fSpectrum->GetRandom();
	fParticleGun->SetParticleEnergy(100*MeV);
	fParticleGun->GeneratePrimaryVertex(anEvent);
	G4cout << "Primary particles generated" << G4endl;
}
