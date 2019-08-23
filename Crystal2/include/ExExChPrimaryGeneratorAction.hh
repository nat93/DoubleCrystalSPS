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
// --------------------------------------------------------------
//

#ifndef ExExChPrimaryGeneratorAction_h
#define ExExChPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "ExExChRunAction.hh"
#include "globals.hh"
#include "TROOT.h"
#include "TChain.h"
#include <iostream>
#include <sstream>

using namespace std;

class G4GeneralParticleSource;
class G4Event;
class ExExChDetectorConstruction;
class G4ParticleGun;
class ExExChRunAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ExExChPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    ExExChPrimaryGeneratorAction(Long64_t eventIDini, ExExChRunAction*, TString inputFilesName);
    virtual ~ExExChPrimaryGeneratorAction();
    
    void GeneratePrimaries(G4Event*);
    void extractIntegerWords(string str);

private:
    G4ParticleGun* fParticleGun;
    ExExChRunAction* runAction;

    Long64_t nEntries;
    Long64_t iEntry;

    TChain* fChain;
    G4int _Event_ID;
    G4double _X;
    G4double _Y;
    G4double _Z;
    G4double _Xp;
    G4double _Yp;
    G4double _Mom;
    G4double _Mom_X;
    G4double _Mom_Y;
    G4double _Mom_Z;
    G4int _par_ID;
    G4double _Q;
    string* _name = new string();
    G4int _CH;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


