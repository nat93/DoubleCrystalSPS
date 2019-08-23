#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4VParticleChange.hh"
#include "G4ParticleChange.hh"
#include "G4TransportationManager.hh"
#include "G4Navigator.hh"
#include "G4Transform3D.hh"
#include "Constants.hh"
#include "TMath.h"

SteppingAction::SteppingAction(RunAction* runAct) : runAction(runAct)
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step *step)
{
    G4Track* track = step->GetTrack();

    G4StepPoint*          prePoint  = step->GetPreStepPoint();
    G4VPhysicalVolume*    prePV     = prePoint->GetPhysicalVolume();

    G4ThreeVector coord     = prePoint->GetPosition();
    G4ThreeVector p         = track->GetMomentum();
    G4double momentum       = TMath::Sqrt(p.x()*p.x() + p.y()*p.y() + p.z()*p.z());
    G4double theta_x        = TMath::PiOver2() - TMath::ACos(p.x()/momentum);
    G4double theta_y        = TMath::PiOver2() - TMath::ACos(p.y()/momentum);
    G4int parentID          = track->GetParentID();

    if(parentID == 0 && prePoint->GetStepStatus() == fGeomBoundary && prePV->GetName().contains("phantom_1"))
    {
        runAction->_X_1         = coord.x()/m;
        runAction->_Y_1         = coord.y()/m;
        runAction->_Xp_1        = theta_x/rad;
        runAction->_Yp_1        = theta_y/rad;
        runAction->_Mom_1       = momentum/GeV;
        runAction->_Mom_X_1     = p.x()/GeV;
        runAction->_Mom_Y_1     = p.y()/GeV;
        runAction->_Mom_Z_1     = p.z()/GeV;
        runAction->_CH_1        = 2;
    }
}
