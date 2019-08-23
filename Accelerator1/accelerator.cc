//my
#include "./src/MagClass.h"
#include "src/Constants.h"

// C++
#include "iostream"
#include "string"
#include "fstream"
#include "vector"
#include "stdlib.h"
#include "time.h"
#include "iomanip"
#include "assert.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "unistd.h"
#include "sys/time.h"

// ROOT
#include "TROOT.h"
#include "TNtuple.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TStyle.h"
#include "TGaxis.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TGraph.h"
#include "TF1.h"
#include "TSystem.h"
#include "TLine.h"
#include "TEllipse.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TPad.h"
#include "TF1.h"
#include "TF2.h"
#include "TGraph2DErrors.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TPolyLine.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TLatex.h"
#include "TPaveStats.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TMath.h"
#include "THStack.h"
#include "TSystem.h"
#include "TBenchmark.h"
#include "TRandom3.h"
#include "TLeaf.h"
#include "TChain.h"
#include "TMultiGraph.h"
#include "TSpline.h"
#include "TVector3.h"

using namespace std;

void function_1(TString output_file_name);
void function_2(TString output_file_name);

void passMagnets(Double_t s, Double_t* coord_x0, Double_t* coord_x, Double_t p, Double_t Charge_C, TGraph* gr_x, TGraph* gr_y, TGraph *gr_xp, TGraph *gr_yp, Bool_t print);
Double_t getGamma(Double_t mass, Double_t pmag);
Double_t getBeta(Double_t gamma);

Int_t main(int argc, char* argv[])
{
    if(argc == 3)
    {
        switch ( atoi(argv[2]) )
        {
        case 1:
          function_1(argv[1]);
          break;
        case 2:
          function_2(argv[1]);
          break;
        default:
          cout<<"--> Nothing to do =)"<<endl;
          break;
        }
    }
    else
    {
        cout<<endl;
        cout<<"--> 1 -- function_1() : single proton trajectory (-300 urad deflection)"<<endl;
        cout<<"--> 2 -- function_2() : particle trajectories"<<endl;
        cout<<endl;
        cout<<"--> ERROR:: Wrong imput parameters number:"<<endl<<
              "--> [0] -- script name"<<endl<<
              "--> [1] -- output filename"<<endl<<
              "--> [2] -- function id"<<endl;
        return -1;

    }

    return 0;
}

void function_1(TString output_file_name)
{
    //-----------------------------------------//
    // Magnets section
    //-----------------------------------------//

    MagClass* magnet = new MagClass();
    const Int_t mtrx_size = magnet->_mtrx_size;

    //-----------------------------------------//

    Double_t* coord_x0          = new Double_t[mtrx_size];
    Double_t* coord_x           = new Double_t[mtrx_size];

    Double_t p = 270.0;                         // [GeV/c]
    Double_t Charge_C   = 1;

    /*x*/     coord_x0[0] = Constants::_beamPositionInitialAtCryPosition;    // [m]
    /*x'*/    coord_x0[1] = Constants::_beamAngleInitialAtCryPosition+Constants::_crystalAngle;// [rad]
    /*y*/     coord_x0[2] = 0.0;                // [m]
    /*y'*/    coord_x0[3] = 0.0;                // [rad]
    /*l*/     coord_x0[4] = 0.0;
    /*dp*/    coord_x0[5] = 0.0;

    TGraph* gr_x = new TGraph();
    TGraph* gr_xp = new TGraph();
    gr_x->SetName("gr_x");
    gr_xp->SetName("gr_xp");
    TGraph* gr_y = new TGraph();
    TGraph* gr_yp = new TGraph();
    gr_y->SetName("gr_y");
    gr_yp->SetName("gr_yp");

    passMagnets(0,coord_x0,coord_x,p,Charge_C,gr_x,gr_y,gr_xp,gr_yp,true);

    TFile* _file = new TFile(output_file_name.Data(),"RECREATE");
    gr_x->Write();
    gr_xp->Write();
    gr_y->Write();
    gr_yp->Write();
    _file->Close();
    cout<<"--> Output file: "<<output_file_name<<endl;
}

void function_2(TString output_file_name)
{
    //-----------------------------------------//
    // Read file
    //-----------------------------------------//

    TTree* tree_0;
    TTree* tree_1;

    Int_t _Event_ID_0;
    Double_t _X_0;
    Double_t _Y_0;
    Double_t _Z_0;
    Double_t _Xp_0;
    Double_t _Yp_0;
    Double_t _Mom_0;
    Double_t _Mom_X_0;
    Double_t _Mom_Y_0;
    Double_t _Mom_Z_0;
    Int_t _par_ID_0;
    Double_t _Q_0;
    string _name_0;
    Int_t _CH_0;

    Int_t _Event_ID_1;
    Double_t _X_1;
    Double_t _Y_1;
    Double_t _Z_1;
    Double_t _Xp_1;
    Double_t _Yp_1;
    Double_t _Mom_1;
    Double_t _Mom_X_1;
    Double_t _Mom_Y_1;
    Double_t _Mom_Z_1;
    Int_t _par_ID_1;
    Double_t _Q_1;
    string _name_1;
    Int_t _CH_1;

    Int_t _Event_ID;
    Double_t _X;
    Double_t _Y;
    Double_t _Z;
    Double_t _Xp;
    Double_t _Yp;
    Double_t _Mom;
    Double_t _Mom_X;
    Double_t _Mom_Y;
    Double_t _Mom_Z;
    Int_t _par_ID;
    Double_t _Q;
    string* _name = new string();
    Int_t _CH;

    tree_0 = new TTree("Tree_0", "A Tree with SPS Data for Sensor Plane 0");
    tree_1 = new TTree("Tree_1", "A Tree with SPS Data for Sensor Plane 1");

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

    TChain* fChain = new TChain("Tree_1");

    fChain->Add("/media/andrii/F492773C92770302/DoubleCrystalSPS_DATA/output_crystal1.root");

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

    Long64_t nEntries = (fChain->GetEntries());
    cout<<"--> Number of entries: "<<nEntries<<endl;

    //-----------------------------------------//
    // Magnets section
    //-----------------------------------------//

    MagClass* magnet = new MagClass();
    const Int_t mtrx_size = magnet->_mtrx_size;

    //-----------------------------------------//

    Double_t* coord_x0_particle          = new Double_t[mtrx_size];
    Double_t* coord_x_particle           = new Double_t[mtrx_size];

    TH2D* h_1 = new TH2D("h_1","XY          [m,m]   on CRY3",2000,-0.1,0.1,2000,-0.1,0.1);
    TH1D* h_2 = new TH1D("h_2","momentum    [GeV/c] on CRY3",330,-30.0,300.0);
    TH1D* h_3 = new TH1D("h_3","thetaX      [rad]   on CRY3",4000000,-4.0,4.0);
    TH1D* h_4 = new TH1D("h_4","thetaY      [rad]   on CRY3",4000000,-4.0,4.0);

    for(Int_t iEntry = 0; iEntry < nEntries; iEntry++)
    {
        fChain->GetEntry(iEntry);

        if(iEntry%1000 == 0)
        {
            printf("\r--> Working: %3.1f %%",100*(Double_t)iEntry/nEntries);
            fflush(stdout);
        }

        _Event_ID_0  = _Event_ID;
        _X_0         = _X;
        _Y_0         = _Y;
        _Z_0         = Constants::_cry2_51652_ua9_pos;
        _Xp_0        = _Xp;
        _Yp_0        = _Yp;
        _Mom_0       = _Mom;
        _Mom_X_0     = _Mom_X;
        _Mom_Y_0     = _Mom_Y;
        _Mom_Z_0     = _Mom_Z;
        _par_ID_0    = _par_ID;
        _Q_0         = _Q;
        _name_0      = _name->c_str();
        _CH_0        = _CH;

        _Event_ID_1  = _Event_ID;
        _X_1         = _X;
        _Y_1         = _Y;
        _Z_1         = Constants::_cry2_51652_ua9_pos;
        _Xp_1        = _Xp;
        _Yp_1        = _Yp;
        _Mom_1       = _Mom;
        _Mom_X_1     = _Mom_X;
        _Mom_Y_1     = _Mom_Y;
        _Mom_Z_1     = _Mom_Z;
        _par_ID_1    = _par_ID;
        _Q_1         = _Q;
        _name_1      = _name->c_str();
        _CH_1        = _CH;

        tree_0->Fill();

        if(_CH != 1)
        {
            tree_1->Fill();
            continue;
        }

        /*x*/     coord_x0_particle[0] = _X;    // [m]
        /*x'*/    coord_x0_particle[1] = _Xp;   // [rad]
        /*y*/     coord_x0_particle[2] = _Y;    // [m]
        /*y'*/    coord_x0_particle[3] = _Yp;   // [rad]
        /*l*/     coord_x0_particle[4] = 0.0;
        /*dp*/    coord_x0_particle[5] = 0.0;

        TGraph* gr_particle_x       = new TGraph();
        TGraph* gr_particle_xp      = new TGraph();
        TGraph* gr_particle_y       = new TGraph();
        TGraph* gr_particle_yp      = new TGraph();
        TString gr_particle_x_name  = "gr_particle_x_";
        TString gr_particle_xp_name = "gr_particle_xp_";
        TString gr_particle_y_name  = "gr_particle_y_";
        TString gr_particle_yp_name = "gr_particle_yp_";
        gr_particle_x_name  += iEntry;
        gr_particle_xp_name += iEntry;
        gr_particle_y_name  += iEntry;
        gr_particle_yp_name += iEntry;
        gr_particle_x->SetName(gr_particle_x_name.Data());
        gr_particle_xp->SetName(gr_particle_xp_name.Data());
        gr_particle_y->SetName(gr_particle_y_name.Data());
        gr_particle_yp->SetName(gr_particle_yp_name.Data());

        passMagnets(0,coord_x0_particle,coord_x_particle,_Mom,_Q,gr_particle_x,gr_particle_y,gr_particle_xp,gr_particle_yp,false);

        h_1->Fill(gr_particle_x->Eval(Constants::_xrph0_51779_ua9_pos),gr_particle_y->Eval(Constants::_xrph0_51779_ua9_pos));
        h_2->Fill(_Mom);
        h_3->Fill(gr_particle_xp->Eval(Constants::_xrph0_51779_ua9_pos));
        h_4->Fill(gr_particle_yp->Eval(Constants::_xrph0_51779_ua9_pos));

        gr_particle_x->Delete();
        gr_particle_y->Delete();
        gr_particle_xp->Delete();
        gr_particle_yp->Delete();

        _X_1         = coord_x_particle[0];
        _Y_1         = coord_x_particle[2];
        _Z_1         = Constants::_xrph0_51779_ua9_pos;
        _Xp_1        = coord_x_particle[1];
        _Yp_1        = coord_x_particle[3];

        Double_t phi    = TMath::ATan(TMath::Tan(_Yp_1)/TMath::Tan(_Xp_1));
        Double_t theta  = TMath::ATan(TMath::Tan(_Xp_1)/TMath::Cos(phi));

        Double_t    ux = TMath::Sin(theta)*TMath::Cos(phi),
                    uy = TMath::Sin(theta)*TMath::Sin(phi),
                    uz = TMath::Cos(theta);

        _Mom_X_1     = _Mom*ux;
        _Mom_Y_1     = _Mom*uy;
        _Mom_Z_1     = _Mom*uz;

        tree_1->Fill();
    }
    cout<<endl;

    TFile* _file = new TFile(output_file_name.Data(),"RECREATE");
    cout<<endl<<"--> Output file name: "<<output_file_name<<endl;
    if(_file->IsZombie()) exit(-1);

    tree_0->Write();
    tree_1->Write();

    h_1->Write();
    h_2->Write();
    h_3->Write();
    h_4->Write();

    _file->Close();

    delete tree_0;
    delete tree_1;
    delete _file;
}

void passMagnets(Double_t s, Double_t* coord_x0, Double_t* coord_x, Double_t p, Double_t Charge_C, TGraph *gr_x, TGraph *gr_y, TGraph *gr_xp, TGraph *gr_yp, Bool_t print)
{
    //-----------------------------------------//
    // Magnets section
    //-----------------------------------------//

    MagClass* magnet = new MagClass();
    const Int_t mtrx_size = magnet->_mtrx_size;
    Int_t order = Constants::_order_transport_matrix;

    Double_t KQ1 = Constants::_grad_quad_1;      // [m-2]
    Double_t QL = Constants::_quadrupole_length; // [m]
    Double_t P0 = Constants::_nominal_momentum;  // [GeV/c]
    Double_t APH = Constants::_aph;              // [m]
    Double_t APV = Constants::_apv;              // [m]

    Double_t DRIFTL0 = Constants::_xrph0_51779_ua9_pos - Constants::_cry2_51652_ua9_pos;   // [m]
    Double_t DRIFTL1 = Constants::_q1_51710_pos-Constants::_cry2_51652_ua9_pos;           // [m]
    Double_t DRIFTL2 = Constants::_xrph0_51779_ua9_pos-Constants::_q1_51710_pos;           // [m]

    //-----------------------------------------//

    Double_t* coord_temp_1_x    = new Double_t[mtrx_size];
    Double_t* coord_temp_2_x    = new Double_t[mtrx_size];

    //-----------------------------------------//
    // Magnets section
    //-----------------------------------------//

    Int_t gr_x_ipoint = 0, gr_y_ipoint = 0;
    Bool_t s_status = kFALSE;

    if(!s_status && s <= 0)
    {
        // INITIAL
        if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_x0[0],coord_x0[1],Constants::_cry2_51652_ua9_pos);
        gr_x->SetPoint(gr_x_ipoint,Constants::_cry2_51652_ua9_pos,coord_x0[0]);
        gr_xp->SetPoint(gr_x_ipoint,Constants::_cry2_51652_ua9_pos,coord_x0[1]);
        gr_y->SetPoint(gr_y_ipoint,Constants::_cry2_51652_ua9_pos,coord_x0[2]);
        gr_yp->SetPoint(gr_y_ipoint,Constants::_cry2_51652_ua9_pos,coord_x0[3]);
        gr_x_ipoint++;
        gr_y_ipoint++;

        s_status = kTRUE;
    }

    if(Constants::_switch_magnets && Charge_C != 0)
    {
        //-----------------------------------------------------------------------------------------------------------------------------//
        if(!s_status && s < Constants::_q1_51710_pos - Constants::_cry2_51652_ua9_pos)
        {
            DRIFTL1 = Constants::_q1_51710_pos - (Constants::_cry2_51652_ua9_pos + s);
            // DRIFT1-S
            if(!magnet->GetNewCoordDrift(DRIFTL1,order,coord_x0,coord_temp_1_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_x0[0],coord_x0[1],Constants::_cry2_51652_ua9_pos+s);
            gr_x->SetPoint(gr_x_ipoint,Constants::_cry2_51652_ua9_pos+s,coord_x0[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_cry2_51652_ua9_pos+s,coord_x0[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_cry2_51652_ua9_pos+s,coord_x0[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_cry2_51652_ua9_pos+s,coord_x0[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;

            s_status = kTRUE;
        }
        else if(s_status)
        {
            // DRIFT1
            if(!magnet->GetNewCoordDrift(DRIFTL1,order,coord_x0,coord_temp_1_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
        }
        if(s_status)
        {
            // QUAD1: DEFOC in X, FOC in Y
            if(!magnet->GetNewCoordQuadrupole(Charge_C*KQ1,p,P0,QL,order,coord_temp_1_x,coord_temp_2_x,APH,APV))
            {if(print) cout<<"## At : "<<Constants::_q1_51710_pos<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_temp_2_x[0],coord_temp_2_x[1],Constants::_q1_51710_pos);
            gr_x->SetPoint(gr_x_ipoint,Constants::_q1_51710_pos,coord_temp_2_x[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_q1_51710_pos,coord_temp_2_x[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_q1_51710_pos,coord_temp_2_x[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_q1_51710_pos,coord_temp_2_x[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;
        }
        //-----------------------------------------------------------------------------------------------------------------------------//
        if(!s_status && s < Constants::_xrph0_51779_ua9_pos - Constants::_cry2_51652_ua9_pos)
        {
            DRIFTL2 = Constants::_xrph0_51779_ua9_pos - (Constants::_cry2_51652_ua9_pos + s);
            // DRIFT2-S
            if(!magnet->GetNewCoordDrift(DRIFTL2,order,coord_temp_2_x,coord_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_x0[0],coord_x0[1],Constants::_cry2_51652_ua9_pos+s);
            gr_x->SetPoint(gr_x_ipoint,Constants::_cry2_51652_ua9_pos+s,coord_x0[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_cry2_51652_ua9_pos+s,coord_x0[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_cry2_51652_ua9_pos+s,coord_x0[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_cry2_51652_ua9_pos+s,coord_x0[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;

            s_status = kTRUE;
        }
        else if(s_status)
        {
            // DRIFT2
            if(!magnet->GetNewCoordDrift(DRIFTL2,order,coord_temp_2_x,coord_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
        }
        //-----------------------------------------------------------------------------------------------------------------------------//
    }
    else
    {
        if(!s_status && s < Constants::_xrph0_51779_ua9_pos - Constants::_cry2_51652_ua9_pos)
        {
            DRIFTL0 = Constants::_xrph0_51779_ua9_pos - (Constants::_cry2_51652_ua9_pos + s);
            // DRIFT0-S
            if(!magnet->GetNewCoordDrift(DRIFTL0,order,coord_x0,coord_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_x0[0],coord_x0[1],Constants::_cry2_51652_ua9_pos+s);
            gr_x->SetPoint(gr_x_ipoint,Constants::_cry2_51652_ua9_pos+s,coord_x0[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_cry2_51652_ua9_pos+s,coord_x0[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_cry2_51652_ua9_pos+s,coord_x0[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_cry2_51652_ua9_pos+s,coord_x0[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;

            s_status = kTRUE;
        }
        else if(s_status)
        {
            // DRIFT0
            if(!magnet->GetNewCoordDrift(DRIFTL0,order,coord_x0,coord_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
        }
    }
    //-----------------------------------------------------------------------------------------------------------------------------//
    if(s_status)
    {
        // FINAL
        if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_x[0],coord_x[1],Constants::_xrph0_51779_ua9_pos);
        gr_x->SetPoint(gr_x_ipoint,Constants::_xrph0_51779_ua9_pos,coord_x[0]);
        gr_xp->SetPoint(gr_x_ipoint,Constants::_xrph0_51779_ua9_pos,coord_x[1]);
        gr_y->SetPoint(gr_y_ipoint,Constants::_xrph0_51779_ua9_pos,coord_x[2]);
        gr_yp->SetPoint(gr_y_ipoint,Constants::_xrph0_51779_ua9_pos,coord_x[3]);
    }
}

Double_t getGamma(Double_t mass, Double_t pmag)
{
    if(mass > 0.0)
    {
        return TMath::Sqrt(1.0 + pmag*pmag/(mass*mass));
    }
    else
    {
        cout<<" ERROR ---> mass <= 0.0"<<endl
           <<" mass = "<<mass<<endl;
        assert(0);
    }
    return -999.0;
}

Double_t getBeta(Double_t gamma)
{
    if(gamma >= 1.0)
    {
        return TMath::Sqrt(1.0 - 1.0/(gamma*gamma));
    }
    else
    {
        cout<<" ERROR ---> gamma < 1"<<endl
           <<" gamma = "<<gamma<<endl;
        assert(0);
    }
    return -999.0;
}

