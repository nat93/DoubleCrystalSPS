#include "PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4RandomDirection.hh"
#include "G4Proton.hh"
#include "G4PionPlus.hh"
#include "G4Electron.hh"
#include "TMath.h"
#include "stdio.h"
#include "assert.h"
#include "Constants.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction(RunAction* runAct, TString inputFilesName) : runAction(runAct)
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

    iEntry = 0;
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
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

        runAction->tree_0->Fill();

        G4String particlename = _name->c_str();
        G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
        G4ParticleDefinition* particle;

        particle        = particleTable->FindParticle(particlename);

//        if(particle && _Q != 0)//All charged particles except ions
        if(_par_ID == 0 && _CH == 1)//Only primaries
        {
            G4double mass   = particle->GetPDGMass()/CLHEP::GeV;
            G4double Ekin   = TMath::Sqrt(_Mom*_Mom + mass*mass) - mass;

            fParticleGun->SetParticleDefinition(particle);
            fParticleGun->SetParticleEnergy(Ekin*CLHEP::GeV);
            fParticleGun->SetParticleMomentumDirection(G4ThreeVector(_Mom_X/_Mom,_Mom_Y/_Mom,_Mom_Z/_Mom));
            fParticleGun->SetParticlePosition(G4ThreeVector(_X*CLHEP::m,_Y*CLHEP::m,Constants::beam_pos_z));

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
