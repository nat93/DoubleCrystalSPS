//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//

#include "ExExChRunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "ExExChAnalysis.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExExChRunAction::ExExChRunAction(): G4UserRunAction(){
//    G4RunManager::GetRunManager()->SetPrintProgress(1);
    
//    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
//    G4cout << "Using " << analysisManager->GetType() << G4endl;
    
//    // Create directories
//    analysisManager->SetVerboseLevel(1);
//    analysisManager->SetFirstHistoId(1);
    
//    // Creating ntuple
//    analysisManager->CreateNtuple("ExExChTree", "Angles and Positions");
//    analysisManager->CreateNtupleDColumn("angXin");
//    analysisManager->CreateNtupleDColumn("angYin");
//    analysisManager->CreateNtupleDColumn("posXin");
//    analysisManager->CreateNtupleDColumn("posYin");
//    analysisManager->CreateNtupleDColumn("angXout");
//    analysisManager->CreateNtupleDColumn("angYout");
//    analysisManager->FinishNtuple();

    _outputFileName = "H8_Data_Simulation.root";
    _timer = new G4Timer;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExExChRunAction::~ExExChRunAction(){
//    delete G4AnalysisManager::Instance();

    delete _timer;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExExChRunAction::BeginOfRunAction(const G4Run* /*run*/){
//    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
//    G4String fileName = "ExExCh";
//    analysisManager->OpenFile(fileName);

    _timer->Start();

    tree_0 = new TTree("Tree_0", "A Tree with H8 Data for Sensor Plane 0");
    tree_1 = new TTree("Tree_1", "A Tree with H8 Data for Sensor Plane 1");

    tree_0->Branch("EventID",   &_Event_ID_0);
    tree_0->Branch("X",         &_X_0);
    tree_0->Branch("Y",         &_Y_0);
    tree_0->Branch("Z",         &_Z_0);
    tree_0->Branch("Xp",        &_Xp_0);
    tree_0->Branch("Yp",        &_Yp_0);
    tree_0->Branch("Mom",       &_Mom_0);
    tree_0->Branch("MomX",      &_Mom_X_0);
    tree_0->Branch("MomY",      &_Mom_Y_0);
    tree_0->Branch("MomZ",      &_Mom_Z_0);
    tree_0->Branch("parID",     &_par_ID_0);
    tree_0->Branch("Q",         &_Q_0);
    tree_0->Branch("name",      &_name_0);
    tree_0->Branch("CH",        &_CH_0);

    tree_1->Branch("EventID",   &_Event_ID_1);
    tree_1->Branch("X",         &_X_1);
    tree_1->Branch("Y",         &_Y_1);
    tree_1->Branch("Z",         &_Z_1);
    tree_1->Branch("Xp",        &_Xp_1);
    tree_1->Branch("Yp",        &_Yp_1);
    tree_1->Branch("Mom",       &_Mom_1);
    tree_1->Branch("MomX",      &_Mom_X_1);
    tree_1->Branch("MomY",      &_Mom_Y_1);
    tree_1->Branch("MomZ",      &_Mom_Z_1);
    tree_1->Branch("parID",     &_par_ID_1);
    tree_1->Branch("Q",         &_Q_1);
    tree_1->Branch("name",      &_name_1);
    tree_1->Branch("CH",        &_CH_1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExExChRunAction::EndOfRunAction(const G4Run* /*run*/)
{
//    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
//    analysisManager->Write();
//    analysisManager->CloseFile();
    
    G4cout<<G4endl<<"--> Output file name: "<<_outputFileName<<G4endl;
    TFile* _hfile = new TFile(_outputFileName, "RECREATE");
    if(_hfile->IsZombie()) exit(-1);
    tree_0->Write();
    tree_1->Write();
    _hfile->Close();

    _timer->Stop();

    delete tree_0;
    delete tree_1;
    delete _hfile;
    G4cout<<G4endl<<G4endl<<"Time: "<<*_timer<<G4endl<<G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
