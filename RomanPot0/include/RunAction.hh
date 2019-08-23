#ifndef RunAction_h
#define RunAction_h 1

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

class RunAction: public G4UserRunAction
{
public:
    RunAction();
    ~RunAction();

    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);


    void SetOutputFileName(G4String fileName) {_outputFileName = fileName;}
    G4String GetOutputFileName() { return _outputFileName;}

    TTree* tree_0;
    TTree* tree_1;

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

private:
    G4Timer* _timer;
    G4String _outputFileName;
};

#endif
