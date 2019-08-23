#include "RunAction.hh"
#include "G4Run.hh"
#include "Randomize.hh"

RunAction::RunAction()
{
    _outputFileName = "H8_Data_Simulation.root";
    _timer = new G4Timer;
}

RunAction::~RunAction()
{
    delete _timer;
}

void RunAction::BeginOfRunAction(const G4Run*)
{
    G4cout<<G4endl<<"--> Output file name: "<<_outputFileName<<G4endl;
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

void RunAction::EndOfRunAction(const G4Run* )
{
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

