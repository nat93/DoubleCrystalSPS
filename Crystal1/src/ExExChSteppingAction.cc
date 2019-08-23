#include "ExExChSteppingAction.hh"
#include "ExExChDetectorConstruction.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4VParticleChange.hh"
#include "G4ParticleChange.hh"
#include "G4TransportationManager.hh"
#include "G4Navigator.hh"
#include "G4Transform3D.hh"
#include "TMath.h"

ExExChSteppingAction::ExExChSteppingAction(ExExChRunAction* runAct) : runAction(runAct)
{}

ExExChSteppingAction::~ExExChSteppingAction()
{}

void ExExChSteppingAction::UserSteppingAction(const G4Step *step)
{
    G4Track* track = step->GetTrack();

    G4StepPoint*          prePoint  = step->GetPreStepPoint();
    G4VPhysicalVolume*    prePV     = prePoint->GetPhysicalVolume();

    G4ThreeVector coord     = prePoint->GetPosition();
    G4ThreeVector p         = track->GetMomentum();
    G4double momentum       = TMath::Sqrt(p.x()*p.x() + p.y()*p.y() + p.z()*p.z());
    G4double theta_x        = TMath::PiOver2() - TMath::ACos(p.x()/momentum);
    G4double theta_y        = TMath::PiOver2() - TMath::ACos(p.y()/momentum);
    G4double charge         = track->GetParticleDefinition()->GetPDGCharge();
    G4int parentID          = track->GetParentID();
    G4String particleName   = track->GetParticleDefinition()->GetParticleName();

    if(prePoint->GetStepStatus() == fGeomBoundary && prePV->GetName().contains("phantom_0") && p.z() > 0)
    {
        runAction->_X_0         = coord.x()/m;
        runAction->_Y_0         = coord.y()/m;
        runAction->_Z_0         = coord.z()/m;
        runAction->_Xp_0        = theta_x/rad;
        runAction->_Yp_0        = theta_y/rad;
        runAction->_Mom_0       = momentum/GeV;
        runAction->_Mom_X_0     = p.x()/GeV;
        runAction->_Mom_Y_0     = p.y()/GeV;
        runAction->_Mom_Z_0     = p.z()/GeV;
        runAction->_par_ID_0    = parentID;
        runAction->_Q_0         = charge;
        runAction->_name_0      = particleName;
        runAction->_CH_0        = 0;

        runAction->tree_0->Fill();
    }

    if(prePoint->GetStepStatus() == fGeomBoundary && prePV->GetName().contains("phantom_1"))
    {
        runAction->_X_1         = coord.x()/m;
        runAction->_Y_1         = coord.y()/m;
        runAction->_Z_1         = coord.z()/m;
        runAction->_Xp_1        = theta_x/rad;
        runAction->_Yp_1        = theta_y/rad;
        runAction->_Mom_1       = momentum/GeV;
        runAction->_Mom_X_1     = p.x()/GeV;
        runAction->_Mom_Y_1     = p.y()/GeV;
        runAction->_Mom_Z_1     = p.z()/GeV;
        runAction->_par_ID_1    = parentID;
        runAction->_Q_1         = charge;
        runAction->_name_1      = particleName;
        runAction->_CH_1        = 1;

        runAction->tree_1->Fill();       

//        track->SetTrackStatus(fStopAndKill);
    }
}
