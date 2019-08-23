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

#include "ExExChPrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"
#include "G4ParticleGun.hh"
#include "TMath.h"
#include "G4GeneralParticleSource.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExExChPrimaryGeneratorAction::ExExChPrimaryGeneratorAction(Long64_t eventIDini, ExExChRunAction* runAct, TString inputFilesName) : runAction(runAct)
{
    fParticleGun = new G4ParticleGun(1);
    fParticleGun->SetParticleDefinition(G4ParticleTable::GetParticleTable()->FindParticle("proton"));
    fParticleGun->SetParticleMomentum(270.0*CLHEP::GeV);

    fChain = new TChain("Tree_1");
    fChain->Add(inputFilesName.Data());

    fChain->SetBranchAddress("EventID",   &_Event_ID);
    fChain->SetBranchAddress("X",         &_X);
    fChain->SetBranchAddress("Y",         &_Y);
    fChain->SetBranchAddress("Z",         &_Z);
    fChain->SetBranchAddress("Xp",        &_Xp);
    fChain->SetBranchAddress("Yp",        &_Yp);
    fChain->SetBranchAddress("Mom",       &_Mom);
    fChain->SetBranchAddress("MomX",      &_Mom_X);
    fChain->SetBranchAddress("MomY",      &_Mom_Y);
    fChain->SetBranchAddress("MomZ",      &_Mom_Z);
    fChain->SetBranchAddress("parID",     &_par_ID);
    fChain->SetBranchAddress("Q",         &_Q);
    fChain->SetBranchAddress("name",      &_name);
    fChain->SetBranchAddress("CH",        &_CH);

    nEntries = (fChain->GetEntries());
    G4cout<<"--> Number of entries: "<<nEntries<<G4endl;

    iEntry = eventIDini;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExExChPrimaryGeneratorAction::~ExExChPrimaryGeneratorAction(){
    delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExExChPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    if(iEntry < nEntries)
    {
        fChain->GetEntry(iEntry);

        runAction->_Event_ID_0  = _Event_ID;
        runAction->_X_0         = _X;
        runAction->_Y_0         = _Y;
        runAction->_Z_0         = _Z;
        runAction->_Xp_0        = _Xp;
        runAction->_Yp_0        = _Yp;
        runAction->_Mom_0       = _Mom;
        runAction->_Mom_X_0     = _Mom_X;
        runAction->_Mom_Y_0     = _Mom_Y;
        runAction->_Mom_Z_0     = _Mom_Z;
        runAction->_par_ID_0    = _par_ID;
        runAction->_Q_0         = _Q;
        runAction->_name_0      = _name->c_str();
        runAction->_CH_0        = _CH;

        runAction->_Event_ID_1  = _Event_ID;
        runAction->_X_1         = _X;
        runAction->_Y_1         = _Y;
        runAction->_Z_1         = _Z;
        runAction->_Xp_1        = _Xp;
        runAction->_Yp_1        = _Yp;
        runAction->_Mom_1       = _Mom;
        runAction->_Mom_X_1     = _Mom_X;
        runAction->_Mom_Y_1     = _Mom_Y;
        runAction->_Mom_Z_1     = _Mom_Z;
        runAction->_par_ID_1    = _par_ID;
        runAction->_Q_1         = _Q;
        runAction->_name_1      = _name->c_str();
        runAction->_CH_1        = _CH;

        runAction->_Event_ID_2  = _Event_ID;
        runAction->_X_2         = _X;
        runAction->_Y_2         = _Y;
        runAction->_Z_2         = _Z;
        runAction->_Xp_2        = _Xp;
        runAction->_Yp_2        = _Yp;
        runAction->_Mom_2       = _Mom;
        runAction->_Mom_X_2     = _Mom_X;
        runAction->_Mom_Y_2     = _Mom_Y;
        runAction->_Mom_Z_2     = _Mom_Z;
        runAction->_par_ID_2    = _par_ID;
        runAction->_Q_2         = _Q;
        runAction->_name_2      = _name->c_str();
        runAction->_CH_2        = _CH;

        runAction->tree_0->Fill();

        G4String particlename = _name->c_str();
        G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
        G4ParticleDefinition* particle;

        particle        = particleTable->FindParticle(particlename);

//        if(particle && _Q != 0)//All charged particles except ions
        if(_par_ID == 0 && _CH == 2)//Only primaries
        {            
            G4double mass   = particle->GetPDGMass()/CLHEP::GeV;
            G4double Ekin   = TMath::Sqrt(_Mom*_Mom + mass*mass) - mass;

            fParticleGun->SetParticleDefinition(particle);
            fParticleGun->SetParticleEnergy(Ekin*CLHEP::GeV);
            fParticleGun->SetParticleMomentumDirection(G4ThreeVector(_Mom_X/_Mom,_Mom_Y/_Mom,_Mom_Z/_Mom));
            fParticleGun->SetParticlePosition(G4ThreeVector(_X*CLHEP::m,_Y*CLHEP::m,(-0.007)*CLHEP::m));

            fParticleGun->GeneratePrimaryVertex(anEvent);
        }
        else
        {
            runAction->tree_1->Fill();
        }

        iEntry++;
    }
    else
    {
        G4cout<<" EMPTY EVENT !!! "<<iEntry<<"/"<<nEntries<<G4endl;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
