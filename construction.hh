#ifndef CONSTURCTION_CC
#define CONSTURCTION_CC

#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4GenericMessenger.hh"

#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	  MyDetectorConstruction();
  	  ~MyDetectorConstruction();

          virtual G4VPhysicalVolume* Construct();
private:
	  G4LogicalVolume* logicDetector;
	  virtual void ConstructSDandField();

	  G4int nCols;
	  G4int nRows;

	  G4GenericMessenger* fMessenger;

	  G4Box *solidWorld, *solidAir1, *solidAir2, *solidAir3,*solidAir4,*solidAir5,*solidAir6,*solidRadiator, *solidBox;
	  G4LogicalVolume *logicWorld, *logicAir1, *logicAir2, *logicAir3,*logicAir4,*logicAir5,*logicAir6,*logicRadiator, *logicBox;
	  G4VPhysicalVolume *physWorld, *physAir1, *physAir2, *physAir3, *physAir4, *physAir5, *physAir6, *physRadiator, *physBox;

	  G4Material *air, *lAr, *carbon, *iron, *polysterene, *galactic;

	  void DefineMaterial();

};


#endif
