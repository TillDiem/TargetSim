#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
	// Constructor
}

MySensitiveDetector::~MySensitiveDetector()
{
	// Destructor
}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
	// Process hits
	G4Track *track = aStep->GetTrack();

	//track->SetTrackStatus(fStopAndKill); // Kill the track if detected by one pixel

	// Get Information
	G4double energy = track->GetKineticEnergy();
	G4double time = track->GetGlobalTime();
	G4ThreeVector position = track->GetPosition();
	G4ThreeVector momentum = track->GetMomentum();
	G4String particleName = track->GetDefinition()->GetParticleName();
	G4int PDGcode = track->GetParticleDefinition()->GetPDGEncoding();
	G4int trackID = track->GetTrackID();


	G4StepPoint *preStep = aStep->GetPreStepPoint();
	G4StepPoint *postStep = aStep->GetPostStepPoint();

	G4ThreeVector prePosition = preStep->GetPosition();
        G4String process = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();

	//Get parent track Id
	G4int parentID = track->GetParentID();

	// We dont have any information about the exact xy position of the photon
	// We just konw that it hit the detector at the xy postition of the pixel
	// We can use the the 'touched volume' to get its copy number => coordinates (unique identifier)

	const G4VTouchable* touchable = preStep->GetTouchable();
	G4int copyNo = touchable->GetCopyNumber();

	// Get translation and rotation of the pixel
	G4VPhysicalVolume *volume = touchable->GetVolume();
	G4ThreeVector posDetector = volume->GetTranslation();

	G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	analysisManager->FillNtupleIColumn(0,evt);
	analysisManager->FillNtupleDColumn(1,position[0]);
	analysisManager->FillNtupleDColumn(2,position[1]);
	analysisManager->FillNtupleDColumn(3,position[2]);
	analysisManager->FillNtupleDColumn(5,time);
	analysisManager->FillNtupleDColumn(4,energy);
	analysisManager->FillNtupleDColumn(6,momentum[0]);
	analysisManager->FillNtupleDColumn(7,momentum[1]);
	analysisManager->FillNtupleDColumn(8,momentum[2]);
	analysisManager->FillNtupleSColumn(9,particleName);
	analysisManager->FillNtupleIColumn(10,PDGcode);
	analysisManager->FillNtupleIColumn(11,trackID);
	analysisManager->FillNtupleSColumn(12,process);
	analysisManager->FillNtupleIColumn(13,parentID);
	analysisManager->AddNtupleRow(0);

	return true;
}
