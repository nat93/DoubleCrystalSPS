#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4PhysicalConstants.hh"
#include "RunAction.hh"
#include "globals.hh"
#include "TROOT.h"
#include "TChain.h"
#include <iostream>
#include <sstream>

using namespace std;

class G4GeneralParticleSource;
class G4Event;
class G4ParticleGun;
class RunAction;

class PrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction
{
public:
    PrimaryGeneratorAction(RunAction*, TString inputFilesName);
    virtual ~PrimaryGeneratorAction();

    void GeneratePrimaries(G4Event* anEvent);

private:
    G4ParticleGun* fParticleGun;
    RunAction* runAction;

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

#endif


