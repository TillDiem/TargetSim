#include "detector.hh"
#include "run.hh"
#include "action.hh"

#include "MCTruthManager.hh"
#include "MCParticle.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
	G4cout << "MySensitiveDetector::MySensitiveDetector" << G4endl;
	// Constructor
}

MySensitiveDetector::~MySensitiveDetector()
{
	// Destructor
}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{


	MCTruthManager *  mctm = MCTruthManager::Instance();

	G4cout << "MySensitiveDetector::ProcessHits" << G4endl;

	MCParticle * particle = mctm->GetMCParticle(aStep->GetTrack()->GetTrackID());

	G4cout << "MySensitiveDetector::ProcessHits: " << particle->PDGCode() << G4endl;


	particle->AddTrajectoryHit(aStep);



	return true;
}
