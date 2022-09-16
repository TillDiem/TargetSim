#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
//include vector
#include <vector>


class MySensitiveDetector : public G4VSensitiveDetector
{
public:
	MySensitiveDetector(G4String name);
	~MySensitiveDetector();
private:
	virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
	std::vector<int> trackID;
	std::vector<int> PDGCodes;
};


#endif
