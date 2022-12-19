#include "run.hh"

////////////////////////////////////////////////
// Used for outputting the run data to a file //
////////////////////////////////////////////////

MyRunAction::MyRunAction()
{
	G4cout << "MyRunAction::MyRunAction()" << G4endl;
}

MyRunAction::~MyRunAction()
{
}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
	AnalysisManager* analysisManager = AnalysisManager::Instance();
	analysisManager->Book("output.root");
	analysisManager->SetRun(run->GetRunID());
	analysisManager->EventReset();

	MCTruthManager * mctm = MCTruthManager::Instance();
	mctm->EventReset();
}

void MyRunAction::EndOfRunAction(const G4Run* run)
{
	AnalysisManager* analysisManager = AnalysisManager::Instance();
	G4cout << "MyRunAction::EndOfRunAction()" << G4endl;
	analysisManager->Save();
}
