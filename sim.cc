#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4Decay.hh"


#include "construction.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv) {
    // Make the RunManager  -> Takes care of stepping, run actions, etc.

    G4RunManager *runManager = new G4RunManager();

    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());

    runManager->Initialize();

    // Make the Manager for the Visiualisation
    // use the cli input to determine the type of visualisation
    G4UIExecutive *ui =  nullptr;

    //Sets the UI manager only if no macro is given to the program!
    if(argc == 1){
	 ui = new G4UIExecutive(argc, argv);
    }
    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();

    // Load the UI manager
    G4UImanager *uiManager = G4UImanager::GetUIpointer();

    if(ui)
    {
    	uiManager->ApplyCommand("/control/execute vis.mac");
    	ui->SessionStart();
    }
    else
    {
	G4String command = "/control/execute ";
	G4String fileName = argv[1];
	uiManager->ApplyCommand(command + fileName);
    }

    // Start the ui interface



  return 0;
}
