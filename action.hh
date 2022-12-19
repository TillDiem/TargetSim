#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"
#include "generator.hh"
#include "run.hh"
#include "MCTruthManager.hh"
#include "AnalysisManager.hh"

class MyActionInitialization : public G4VUserActionInitialization
{
  public:
    MyActionInitialization();
    ~MyActionInitialization();


    virtual void EndOfEventAction(const G4Event*);
    virtual void BeginOfEventAction(const G4Event*);

    virtual void Build() const;
};

#endif
