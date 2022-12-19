// -----------------------------------------------------------------------------
//  MCTruthManager.h
//
//  Class definition of the MC truth manager
//   * Author: Everybody is an author!
//   * Creation date: 10 August 2020
// -----------------------------------------------------------------------------

#ifndef MCTruthManager_h
#define MCTruthManager_h 1

// Q-Pix includes
#include "MCParticle.hh"

// GEANT4 includes
#include "globals.hh"

// ROOT includes
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"

// C++ includes
#include <map>
#include <set>

class MCTruthManager {

    public:

        MCTruthManager();
        ~MCTruthManager();

        void EventReset();

        void SetRun(int const);
        void SetEvent(int const);

        static MCTruthManager* Instance();

        void AddMCParticle(MCParticle *);
        MCParticle * GetMCParticle(int const);

        inline std::map< int, MCParticle * > GetMCParticleMap() const { return mc_particle_map_; }

    private:

        static MCTruthManager * instance_;

        int run_;
        int event_;

           // MC particle map
        // std::map< int, MCParticle > mc_particle_map_;
        std::map< int, MCParticle * > mc_particle_map_;

};

#endif
