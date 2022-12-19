// -----------------------------------------------------------------------------
//  G4_QPIX | EventAction.cpp
//
//
//   * Author: Everybody is an author!
//   * Creation date: 15 Aug 2019
// -----------------------------------------------------------------------------

#include "EventAction.hh"

// Q-Pix includes
#include "AnalysisManager.hh"
#include "MCTruthManager.hh"

// GEANT4 includes
#include "G4Event.hh"
#include "G4GenericMessenger.hh"


EventAction::EventAction()
{
}


EventAction::~EventAction()
{
}


void EventAction::BeginOfEventAction(const G4Event*)
{
    // int mod = event->GetEventID() % 1000;
    // if (mod == 0)
    // {
    //     G4cout << "Starting event" << event->GetEventID() << "..." << G4endl;
    // }
}


void EventAction::EndOfEventAction(const G4Event* event)
{
    // get MC truth manager
    MCTruthManager * mc_truth_manager = MCTruthManager::Instance();

    // get map of particles from MC truth manager
    auto const MCParticleMap = mc_truth_manager->GetMCParticleMap();


    // get analysis manager
    AnalysisManager * analysis_manager = AnalysisManager::Instance();

    // set event number
    // event->SetEventID(event->GetEventID() + event_id_offset_);
    // analysis_manager->SetEvent(event->GetEventID());
    analysis_manager->SetEvent(event->GetEventID());
   // get map of particles from MC truth manager
    // auto const MCParticleMap = mc_truth_manager->GetMCParticleMap();

    // add particle to analysis manager
    for (auto const& p : MCParticleMap)
    {
        auto const& particle = p.second;

        analysis_manager->AddMCParticle(particle);
    }

    // write event to ROOT file and reset event variables
    analysis_manager->EventFill();
    analysis_manager->EventReset();

    // reset event in MC truth manager
    mc_truth_manager->EventReset();
}
