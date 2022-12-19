#include "action.hh"
#include "run.hh"
#include "G4Event.hh"

MyActionInitialization::MyActionInitialization()
{
G4cout << "My Action Begin" << G4endl;
}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::BeginOfEventAction(const G4Event*)
{
	G4cout << "Begin of Event" << G4endl;
}

void MyActionInitialization::EndOfEventAction(const G4Event* event)
{

	G4cout << "Event " << event->GetEventID() << G4endl;
	G4cout << "End of event action" << G4endl;

	MCTruthManager* mctm = MCTruthManager::Instance();
	AnalysisManager* am = AnalysisManager::Instance();

	auto const MCParticleMap = mctm->GetMCParticleMap();


	am->SetEvent(event->GetEventID());


	for(auto const& particle: MCParticleMap)
	{

		am->AddMCParticle(particle.second);
	}

	am->EventFill();
	am->EventReset();
	mctm->EventReset();


}



void MyActionInitialization::Build() const
{
  MyPrimaryGenerator *primaryGenerator = new MyPrimaryGenerator();
  SetUserAction(primaryGenerator);
}
