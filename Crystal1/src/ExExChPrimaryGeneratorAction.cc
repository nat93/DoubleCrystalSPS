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

ExExChPrimaryGeneratorAction::ExExChPrimaryGeneratorAction()
{
    fParticleGun = new G4ParticleGun(1);
    fParticleGun->SetParticleDefinition(G4ParticleTable::GetParticleTable()->FindParticle("proton"));
    fParticleGun->SetParticleMomentum(270.0*CLHEP::GeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExExChPrimaryGeneratorAction::~ExExChPrimaryGeneratorAction()
{
    delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExExChPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    //    --> BEAMX_CRYSTAL2 =
    //    --> BEAMXp_CRYSTAL2 = 4.88183e-05
    //    --> dX = 0.1 [mm]
    //    --> SigmaXp = 2.28283 [urad] or 14.6744 [urad]
    //    --> SigmaY = 0.476921 [mm]
    //    --> SigmaYp = 14.6247 [urad]

    G4double Xpos = -0.00244892 + 0.0001*(G4UniformRand()-0.5);
    G4double Ypos = G4RandGauss::shoot(0.,              0.000476921);
    G4double Xang = G4RandGauss::shoot(48.8183e-06,     14.6744e-06);//2.28283e-06);
    G4double Yang = G4RandGauss::shoot(0.,              14.6247e-06);

    G4double phi    = TMath::ATan(TMath::Tan(Yang)/TMath::Tan(Xang));
    G4double theta  = TMath::ATan(TMath::Tan(Xang)/TMath::Cos(phi));

    G4double    ux = TMath::Sin(theta)*TMath::Cos(phi),
                uy = TMath::Sin(theta)*TMath::Sin(phi),
                uz = TMath::Cos(theta);

    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux,uy,uz));
    fParticleGun->SetParticlePosition(G4ThreeVector(Xpos*CLHEP::meter,Ypos*CLHEP::meter,(-0.0035)*CLHEP::meter));

    fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
