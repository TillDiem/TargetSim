#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	G4double primaryParticles = 1;
	fParticleGun = new G4ParticleGun(primaryParticles);


	// Read in on start - later overwritten using a macro
	G4String particleName = "proton";
	G4double particleEnergy = 120*GeV;
	std::cout << "Particle: " << particleName << " Energy: " << particleEnergy << std::endl;

	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition *particle = particleTable->FindParticle(particleName);

	if(particle){
		G4ThreeVector position(0,0,-1.5*m);
		G4ThreeVector momentumDirection(0,0,1);
		fParticleGun->SetParticleDefinition(particle);
		fParticleGun->SetParticlePosition(position);
		fParticleGun->SetParticleMomentumDirection(momentumDirection);
		fParticleGun->SetParticleEnergy(particleEnergy);
	}
	else{
		G4cout << "Particle " << particleName << " not found" << G4endl;
	}



}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event* anEvent)
{
	fParticleGun->GeneratePrimaryVertex(anEvent);
}
