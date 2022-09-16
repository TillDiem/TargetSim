#include "run.hh"

////////////////////////////////////////////////
// Used for outputting the run data to a file //
////////////////////////////////////////////////

MyRunAction::MyRunAction()
{
G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
analysisManager->CreateNtuple("HitData", "HitData");  // rows
analysisManager->CreateNtupleIColumn("Event");  // Integer Column for event number
analysisManager->CreateNtupleDColumn("hit_pos_x");
analysisManager->CreateNtupleDColumn("hit_pos_y");
analysisManager->CreateNtupleDColumn("hit_pos_z");
analysisManager->CreateNtupleDColumn("hit_t");
analysisManager->CreateNtupleDColumn("hit_e");
analysisManager->CreateNtupleDColumn("hit_mom_x");
analysisManager->CreateNtupleDColumn("hit_mom_y");
analysisManager->CreateNtupleDColumn("hit_mom_z");
analysisManager->CreateNtupleSColumn("hit_particle_name");
analysisManager->CreateNtupleIColumn("hit_pdg_code");
analysisManager->CreateNtupleIColumn("hit_track_id");
analysisManager->CreateNtupleSColumn("hit_process");
analysisManager->CreateNtupleIColumn("hit_parent_id");
analysisManager->FinishNtuple(0);

}

MyRunAction::~MyRunAction()
{
}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

	G4int runNumber = run->GetRunID();
	std::stringstream strRunID;
	strRunID << runNumber;
	analysisManager->OpenFile("output"+strRunID.str()+".root");

}

void MyRunAction::EndOfRunAction(const G4Run* run)
{
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	analysisManager->Write();
	analysisManager->CloseFile();
}
