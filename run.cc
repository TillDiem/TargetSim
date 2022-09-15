#include "run.hh"

////////////////////////////////////////////////
// Used for outputting the run data to a file //
////////////////////////////////////////////////

MyRunAction::MyRunAction()
{
G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
analysisManager->CreateNtuple("Hits", "Hits");  // rows
analysisManager->CreateNtupleIColumn("fEvent");  // Integer Column for event number
analysisManager->CreateNtupleDColumn("fX");
analysisManager->CreateNtupleDColumn("fY");
analysisManager->CreateNtupleDColumn("fZ");
analysisManager->CreateNtupleDColumn("time");
analysisManager->CreateNtupleDColumn("energy");
analysisManager->CreateNtupleDColumn("fPx");
analysisManager->CreateNtupleDColumn("fPy");
analysisManager->CreateNtupleDColumn("fPz");
analysisManager->CreateNtupleSColumn("particle");
analysisManager->CreateNtupleIColumn("PDG");
analysisManager->CreateNtupleIColumn("fTrackID");
analysisManager->CreateNtupleSColumn("fprocess");
analysisManager->CreateNtupleIColumn("fParentID");

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
