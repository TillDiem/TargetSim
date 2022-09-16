#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
	// Messenger for changing the geometry of the detector
	fMessenger = new G4GenericMessenger(this, "/detector/", "Detector control");
	nCols = 100;
	nRows = 100;
	fMessenger->DeclareProperty("nCols",nCols, "Set number of photosensors (Column)");
	fMessenger->DeclareProperty("nRows",nRows, "Set number of photosensors (Rows)");

	DefineMaterial();
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::DefineMaterial()
{
	G4NistManager* nist = G4NistManager::Instance();
	air = nist->FindOrBuildMaterial("G4_AIR");
	carbon = nist->FindOrBuildMaterial("G4_C");
}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	// Materials

	G4double xWorld = 2.5*m;
	G4double yWorld = 2.5*m;
	G4double zWorld = 2.5*m;

	solidWorld = new G4Box("solidWorld",xWorld,yWorld,zWorld);
	logicWorld = new G4LogicalVolume(solidWorld,air,"logicWorld");
	physWorld = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicWorld,"physWorld",0,false,0,true);

	// AirVolume1
	solidAir1 = new G4Box("solidAir1",1*m,1*m,1*m);
	logicAir1 = new G4LogicalVolume(solidAir1,air,"logicAir1");
	physAir1 = new G4PVPlacement(0,G4ThreeVector(0.,0.,-1.1*m),logicAir1,"physAir1",logicWorld,false,0,true);


	// Interaction Chamber
	solidRadiator = new G4Box("solidRadiator",1*m,1*m,0.1*m);
	logicRadiator = new G4LogicalVolume(solidRadiator,carbon,"logicRadiator");
	physRadiator = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicRadiator,"physRadiator",logicWorld,false,0,true);

	// AirVolume2
	solidAir2 = new G4Box("solidAir2",1*m,1*m,1*m);
	logicAir2 = new G4LogicalVolume(solidAir2,air,"logicAir2");
	physAir2 = new G4PVPlacement(0,G4ThreeVector(0.,0.,+1.1*m),logicAir2,"physAir2",logicWorld,false,0,true);

	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField(){
       MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
       MySensitiveDetector *sensDet2 = new MySensitiveDetector("SensitiveDetector2");
       MySensitiveDetector *sensDet3 = new MySensitiveDetector("SensitiveDetector3");
       logicAir1->SetSensitiveDetector(sensDet);
       logicAir2->SetSensitiveDetector(sensDet2);
       logicRadiator->SetSensitiveDetector(sensDet3);
}
