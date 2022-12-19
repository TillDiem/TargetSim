#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
	G4cout << "MyDetectorConstruction::MyDetectorConstruction()" << G4endl;
	DefineMaterial();
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::DefineMaterial()
{
	G4NistManager* nist = G4NistManager::Instance();
	air = nist->FindOrBuildMaterial("G4_AIR");
	carbon = nist->FindOrBuildMaterial("G4_C");
	iron = nist->FindOrBuildMaterial("G4_Fe");
	polysterene = nist->FindOrBuildMaterial("G4_POLYSTYRENE");
	galactic = nist->FindOrBuildMaterial("G4_Galactic");

}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	// Materials

	G4double xWorld = 5*cm;
	G4double yWorld = 5*cm;
	G4double zWorld = 5*cm;

	double length = 0.5*cm;



	solidWorld = new G4Box("solidWorld",xWorld,yWorld,zWorld);
	logicWorld = new G4LogicalVolume(solidWorld,air,"logicWorld");
	physWorld = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicWorld,"physWorld",0,false,0,true);

	solidBox = new G4Box("solidBox",xWorld/2.,yWorld/2.,zWorld/2.);
	logicBox = new G4LogicalVolume(solidBox,polysterene,"logicBox");
	physBox = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicBox,"physBox",logicWorld,false,0,true);


	solidRadiator = new G4Box("solidRadiator",length,length,length);
	logicRadiator = new G4LogicalVolume(solidRadiator,iron,"logicRadiator");
	physRadiator = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicRadiator,"physRadiator",logicBox,false,0,true);

/* 	// AirVolume1 */
	/* solidAir1 = new G4Box("solidAir1",0.4*cm,1*cm,1*cm); */
	/* logicAir1 = new G4LogicalVolume(solidAir1,polysterene,"logicAir1"); */
	/* physAir1 = new G4PVPlacement(0,G4ThreeVector(0.6*cm,0.,0.),logicAir1,"physAir1",logicWorld,false,0,true); */

/* 	// AirVolume2 */
/* 	solidAir2 = new G4Box("solidAir2",0.4*cm,1*cm,1*cm); */
/* 	logicAir2 = new G4LogicalVolume(solidAir2,polysterene,"logicAir2"); */
/* 	physAir2 = new G4PVPlacement(0,G4ThreeVector(-0.6*cm,0.,0.),logicAir2,"physAir2",logicWorld,false,0,true); */

/* /1* 	// AirVolume3 *1/ */
/* 	solidAir3 = new G4Box("solidAir3",0.2*cm,0.4*cm,0.2*cm); */
/* 	logicAir3 = new G4LogicalVolume(solidAir3,polysterene,"logicAir3"); */
/* 	physAir3 = new G4PVPlacement(0,G4ThreeVector(0.,0.6*cm,0.),logicAir3,"physAir3",logicWorld,false,0,true); */

/* /1* 	// AirVolume4 *1/ */
/* 	solidAir4 = new G4Box("solidAir4",0.2*cm,0.4*cm,0.2*cm); */
/* 	logicAir4 = new G4LogicalVolume(solidAir4,polysterene,"logicAir4"); */
/* 	physAir4 = new G4PVPlacement(0,G4ThreeVector(0.,-0.6*cm,0.),logicAir4,"physAir4",logicWorld,false,0,true); */

/* /1* 	// AirVolume5 *1/ */
/* 	solidAir5 = new G4Box("solidAir5",0.2*cm,1*cm,0.4*cm); */
/* 	logicAir5 = new G4LogicalVolume(solidAir5,polysterene,"logicAir5"); */
/* 	physAir5 = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.6*cm),logicAir5,"physAir5",logicWorld,false,0,true); */

/* 	// AirVolume6 */
/* 	solidAir6 = new G4Box("solidAir6",0.2*cm,1*cm,0.4*cm); */
/* 	logicAir6 = new G4LogicalVolume(solidAir6,polysterene,"logicAir6"); */
/* 	physAir6 = new G4PVPlacement(0,G4ThreeVector(0.,0.,-0.6*cm),logicAir6,"physAir6",logicWorld,false,0,true); */


	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField(){
       MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
       MySensitiveDetector *sensDet2 = new MySensitiveDetector("SensitiveDetector2");
       //MySensitiveDetector *sensDet3 = new MySensitiveDetector("SensitiveDetector3");
       logicRadiator->SetSensitiveDetector(sensDet);
       logicBox->SetSensitiveDetector(sensDet2);
       //logicWorld->SetSensitiveDetector(sensDet3);

}
