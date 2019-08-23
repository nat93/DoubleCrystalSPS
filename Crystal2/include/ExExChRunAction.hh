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

#ifndef ExExChRunAction_h
#define ExExChRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4PhysicalConstants.hh"
#include "G4Timer.hh"

#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1.h"

using namespace std;

class G4Run;

class ExExChRunAction : public G4UserRunAction
{
public:
    ExExChRunAction();
    virtual ~ExExChRunAction();
    
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

    void SetOutputFileName(G4String fileName) {_outputFileName = fileName;}
    G4String GetOutputFileName() { return _outputFileName;}

    TTree* tree_0;
    TTree* tree_1;
    TTree* tree_2;

    G4int _Event_ID_0;
    G4double _X_0;
    G4double _Y_0;
    G4double _Z_0;
    G4double _Xp_0;
    G4double _Yp_0;
    G4double _Mom_0;
    G4double _Mom_X_0;
    G4double _Mom_Y_0;
    G4double _Mom_Z_0;
    G4int _par_ID_0;
    G4double _Q_0;
    string _name_0;
    G4int _CH_0;

    G4int _Event_ID_1;
    G4double _X_1;
    G4double _Y_1;
    G4double _Z_1;
    G4double _Xp_1;
    G4double _Yp_1;
    G4double _Mom_1;
    G4double _Mom_X_1;
    G4double _Mom_Y_1;
    G4double _Mom_Z_1;
    G4int _par_ID_1;
    G4double _Q_1;
    string _name_1;
    G4int _CH_1;

    G4int _Event_ID_2;
    G4double _X_2;
    G4double _Y_2;
    G4double _Z_2;
    G4double _Xp_2;
    G4double _Yp_2;
    G4double _Mom_2;
    G4double _Mom_X_2;
    G4double _Mom_Y_2;
    G4double _Mom_Z_2;
    G4int _par_ID_2;
    G4double _Q_2;
    string _name_2;
    G4int _CH_2;

private:
    G4Timer* _timer;
    G4String _outputFileName;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

