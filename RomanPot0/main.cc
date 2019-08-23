#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"
#include "G4RunManager.hh"
#include "G4eMultipleScattering.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "Randomize.hh"
#include "G4PhysListFactory.hh"
#include "EventAction.hh"
#include "QGSP_BERT.hh"
#include "QGSP_BIC.hh"

#include <ctime>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
  if(argc != 4)
  {
      cout<<"ERROR::Not enough input arguments!"<<endl;
      cout<<"--> [0]: script_name"<<endl;
      cout<<"--> [1]: mac_file_name"<<endl;
      cout<<"--> [2]: input_file_name"<<endl;
      cout<<"--> [3]: output_file_name"<<endl;
      assert(0);
  }
  G4PhysListFactory factory;
  G4String physName = "QGSP_BIC";

  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  CLHEP::HepRandom::setTheSeed(time(NULL));

  G4RunManager* runManager = new G4RunManager;  
  G4VModularPhysicsList* phys = factory.GetReferencePhysList(physName);

  runManager->SetUserInitialization(phys);
  runManager->SetUserInitialization(new DetectorConstruction); 

  RunAction* runAction = new RunAction();
  G4String inputFileFileName = argv[2];
  G4String outputFileFileName = argv[3];
  runAction->SetOutputFileName(outputFileFileName);
  PrimaryGeneratorAction* primary = new PrimaryGeneratorAction(runAction,inputFileFileName);
  EventAction* eventAction = new EventAction(runAction);
  SteppingAction* stepAction = new SteppingAction(runAction);

  runManager->SetUserAction(runAction);  
  runManager->SetUserAction(primary);
  runManager->SetUserAction(eventAction);  
  runManager->SetUserAction(stepAction);

  // Get the pointer to the User Interface manager
  G4UImanager* UI = G4UImanager::GetUIpointer();
  G4String scriptName = argv[1];

  if(scriptName != "vis.mac")
  {
      // Batch mode
      G4String command = "/control/execute ";
      UI->ApplyCommand(command+scriptName);
  }
  else
  {
      G4VisManager* visManager = new G4VisExecutive;
      visManager->Initialize();

      UI->ExecuteMacroFile(scriptName);

      delete visManager;
  }
  // Job termination
  delete runManager;

  return 0;
}
