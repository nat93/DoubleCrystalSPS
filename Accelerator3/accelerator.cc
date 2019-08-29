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
        cout<<"--> 1 -- function_1() : single proton trajectory (-200 urad deflection)"<<endl;
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

    TChain* fChain = new TChain("Tree_2");

    TString inputfileName;
    for(Int_t i = 0; i < 20; i++)
    {
//	inputfileName = "~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_null_accelerator2_crystal2_";
//	inputfileName = "~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_simple_accelerator2_crystal2_";
//	inputfileName = "~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_layers_accelerator2_crystal2_";

//	inputfileName = "~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_null_accelerator2_crystal2_null_";
//	inputfileName = "~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_simple_accelerator2_crystal2_null_";
	inputfileName = "~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_layers_accelerator2_crystal2_null_";

	inputfileName += i;
	inputfileName += ".root";
	cout<<"filename: "<<inputfileName<<endl;

    	fChain->Add(inputfileName.Data());
 }

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

    TH2D* h_1 = new TH2D("h_1","XY          [m,m]   on RP1",2000,-0.1,0.1,2000,-0.1,0.1);
    TH1D* h_2 = new TH1D("h_2","momentum    [GeV/c] on RP1",330,-30.0,300.0);
    TH1D* h_3 = new TH1D("h_3","thetaX      [rad]   on RP1",4000000,-4.0,4.0);
    TH1D* h_4 = new TH1D("h_4","thetaY      [rad]   on RP1",4000000,-4.0,4.0);

    TH2D* h_5 = new TH2D("h_5","XY          [m,m]   on LHC COLL",2000,-0.1,0.1,2000,-0.1,0.1);
    TH1D* h_6 = new TH1D("h_6","momentum    [GeV/c] on LHC COLL",330,-30.0,300.0);
    TH1D* h_7 = new TH1D("h_7","thetaX      [rad]   on LHC COLL",4000000,-4.0,4.0);
    TH1D* h_8 = new TH1D("h_8","thetaY      [rad]   on LHC COLL",4000000,-4.0,4.0);

    TH1D* hSimNew 	= new TH1D("hSimNew","hSimNew",128,0,256*0.055);
    Double_t shiftX = /*MADX-OPTICS*/1.79604 + /*ALIGNMENT*/(36.8 - 28.6) + /*INTERNAL-OFFSET*/2.97 - 1.2; // [mm]

    TFile* _file = new TFile(output_file_name.Data(),"RECREATE");

    for(Int_t iEntry = 0; iEntry < nEntries; iEntry++)
    {
        fChain->GetEntry(iEntry);

        if(iEntry%1000 == 0)
        {
            printf("\r--> Working: %3.1f %%",100*(Double_t)iEntry/nEntries);
            fflush(stdout);
        }

        if(_CH != 4) continue;

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

        if((-1e3)*gr_particle_x->Eval(Constants::_xrph_51937_ua9_pos) - shiftX >= 0)
            hSimNew->Fill((-1e3)*gr_particle_x->Eval(Constants::_xrph_51937_ua9_pos) - shiftX,1);

        h_1->Fill(gr_particle_x->Eval(Constants::_xrph_51937_ua9_pos),gr_particle_y->Eval(Constants::_xrph_51937_ua9_pos));
        h_2->Fill(_Mom);
        h_3->Fill(gr_particle_xp->Eval(Constants::_xrph_51937_ua9_pos));
        h_4->Fill(gr_particle_yp->Eval(Constants::_xrph_51937_ua9_pos));

        h_5->Fill(gr_particle_x->Eval(Constants::_tcsm_51934_pos),gr_particle_y->Eval(Constants::_tcsm_51934_pos));
        h_6->Fill(_Mom);
        h_7->Fill(gr_particle_xp->Eval(Constants::_tcsm_51934_pos));
        h_8->Fill(gr_particle_yp->Eval(Constants::_tcsm_51934_pos));

        gr_particle_x->Delete();
        gr_particle_y->Delete();
        gr_particle_xp->Delete();
        gr_particle_yp->Delete();
    }
    cout<<endl;

    h_1->Write();
    h_2->Write();
    h_3->Write();
    h_4->Write();
    h_5->Write();
    h_6->Write();
    h_7->Write();
    h_8->Write();
    hSimNew->Write();

    _file->Close();

    cout<<"--> Output file: "<<output_file_name<<endl;
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
    Double_t KQ2 = Constants::_grad_quad_2;      // [m-2]
    Double_t KQ3 = Constants::_grad_quad_3;      // [m-2]
    Double_t KQ4 = Constants::_grad_quad_4;      // [m-2]
    Double_t KS1 = Constants::_grad_sext_1;      // [m-3]
    Double_t ADL = Constants::_angle_dipole;     // [rad]
    Double_t QL = Constants::_quadrupole_length; // [m]
    Double_t DL = Constants::_dipole_length;     // [m]
    Double_t SL = Constants::_sextupole_length;  // [m]
    Double_t P0 = Constants::_nominal_momentum;  // [GeV/c]
    Double_t APH = Constants::_aph;              // [m]
    Double_t APV = Constants::_apv;              // [m]

    Double_t DRIFTL0 = Constants::_xrph_52202_ua9_pos - Constants::_cry3_51799_ua9_pos;   // [m]
    Double_t DRIFTL1 = Constants::_q1_51810_pos-Constants::_cry3_51799_ua9_pos;           // [m]
    Double_t DRIFTL2 = Constants::_q2_51910_pos-Constants::_q1_51810_pos;                 // [m]
    Double_t DRIFTL3 = Constants::_xrph_51937_ua9_pos-Constants::_q2_51910_pos;           // [m]
    Double_t DRIFTL4 = Constants::_lsf_52005_pos-Constants::_xrph_51937_ua9_pos;          // [m]
    Double_t DRIFTL5 = Constants::_q3_52010_pos-Constants::_lsf_52005_pos;                // [m]
    Double_t DRIFTL6 = Constants::_mba_52030_pos-(DL/2.0)-Constants::_q3_52010_pos;       // [m]
    Double_t DRIFTL7 = Constants::_mba_52050_pos-DL-Constants::_mba_52030_pos;            // [m]
    Double_t DRIFTL8 = Constants::_mbb_52070_pos-DL-Constants::_mba_52050_pos;            // [m]
    Double_t DRIFTL9 = Constants::_mbb_52090_pos-DL-Constants::_mbb_52070_pos;            // [m]
    Double_t DRIFTL10 = Constants::_q4_52110_pos-(DL/2.0)-Constants::_mbb_52090_pos;       // [m]
    Double_t DRIFTL11 = Constants::_mbb_52130_pos-(DL/2.0)-Constants::_q4_52110_pos;      // [m]
    Double_t DRIFTL12 = Constants::_mbb_52150_pos-DL-Constants::_mbb_52130_pos;           // [m]
    Double_t DRIFTL13 = Constants::_xrph_52202_ua9_pos-(DL/2.0)-Constants::_mbb_52150_pos;// [m]

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
        if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_x0[0],coord_x0[1],Constants::_cry3_51799_ua9_pos);
        gr_x->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos,coord_x0[0]);
        gr_xp->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos,coord_x0[1]);
        gr_y->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos,coord_x0[2]);
        gr_yp->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos,coord_x0[3]);
        gr_x_ipoint++;
        gr_y_ipoint++;

        s_status = kTRUE;
    }

    if(Constants::_switch_magnets && Charge_C != 0)
    {
        //-----------------------------------------------------------------------------------------------------------------------------//
        if(!s_status && s < Constants::_q1_51810_pos - Constants::_cry3_51799_ua9_pos)
        {
            DRIFTL1 = Constants::_q1_51810_pos - (Constants::_cry3_51799_ua9_pos + s);
            // DRIFT1-S
            if(!magnet->GetNewCoordDrift(DRIFTL1,order,coord_x0,coord_temp_1_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_x0[0],coord_x0[1],Constants::_cry3_51799_ua9_pos+s);
            gr_x->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[3]);
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
            // QUAD1: FOC in X, DEFOC in Y
            if(!magnet->GetNewCoordQuadrupole(Charge_C*KQ1,p,P0,QL,order,coord_temp_1_x,coord_temp_2_x,APH,APV))
            {if(print) cout<<"## At : "<<Constants::_q1_51810_pos<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_temp_2_x[0],coord_temp_2_x[1],Constants::_q1_51810_pos);
            gr_x->SetPoint(gr_x_ipoint,Constants::_q1_51810_pos,coord_temp_2_x[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_q1_51810_pos,coord_temp_2_x[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_q1_51810_pos,coord_temp_2_x[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_q1_51810_pos,coord_temp_2_x[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;
        }
        //-----------------------------------------------------------------------------------------------------------------------------//
        if(!s_status && s < Constants::_q2_51910_pos - Constants::_cry3_51799_ua9_pos)
        {
            DRIFTL2 = Constants::_q2_51910_pos - (Constants::_cry3_51799_ua9_pos + s);
            // DRIFT2-S
            if(!magnet->GetNewCoordDrift(DRIFTL2,order,coord_x0,coord_temp_1_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_x0[0],coord_x0[1],Constants::_cry3_51799_ua9_pos+s);
            gr_x->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;

            s_status = kTRUE;
        }
        else if(s_status)
        {
            // DRIFT2
            if(!magnet->GetNewCoordDrift(DRIFTL2,order,coord_temp_2_x,coord_temp_1_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
        }
        if(s_status)
        {
            // QUAD2: FOC in Y, DEFOC in X
            if(!magnet->GetNewCoordQuadrupole(Charge_C*KQ2,p,P0,QL,order,coord_temp_1_x,coord_temp_2_x,APH,APV))
            {if(print) cout<<"## At : "<<Constants::_q2_51910_pos<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_temp_2_x[0],coord_temp_2_x[1],Constants::_q2_51910_pos);
            gr_x->SetPoint(gr_x_ipoint,Constants::_q2_51910_pos,coord_temp_2_x[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_q2_51910_pos,coord_temp_2_x[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_q2_51910_pos,coord_temp_2_x[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_q2_51910_pos,coord_temp_2_x[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;
        }
        //-----------------------------------------------------------------------------------------------------------------------------//
        if(!s_status && s < Constants::_xrph_51937_ua9_pos - Constants::_cry3_51799_ua9_pos)
        {
            DRIFTL3 = Constants::_xrph_51937_ua9_pos - (Constants::_cry3_51799_ua9_pos + s);
            // DRIFT3-S
            if(!magnet->GetNewCoordDrift(DRIFTL3,order,coord_x0,coord_temp_1_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_x0[0],coord_x0[1],Constants::_cry3_51799_ua9_pos+s);
            gr_x->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;

            s_status = kTRUE;
        }
        else if(s_status)
        {
            // DRIFT3
            if(!magnet->GetNewCoordDrift(DRIFTL3,order,coord_temp_2_x,coord_temp_1_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_temp_1_x[0],coord_temp_1_x[1],Constants::_xrph_51937_ua9_pos);
            gr_x->SetPoint(gr_x_ipoint,Constants::_xrph_51937_ua9_pos,coord_temp_1_x[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_xrph_51937_ua9_pos,coord_temp_1_x[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_xrph_51937_ua9_pos,coord_temp_1_x[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_xrph_51937_ua9_pos,coord_temp_1_x[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;
        }
        //-----------------------------------------------------------------------------------------------------------------------------//
        if(!s_status && s < Constants::_lsf_52005_pos - Constants::_cry3_51799_ua9_pos)
        {
            DRIFTL4 = Constants::_lsf_52005_pos - (Constants::_cry3_51799_ua9_pos + s);
            // DRIFT4-S
            if(!magnet->GetNewCoordDrift(DRIFTL4,order,coord_x0,coord_temp_2_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_x0[0],coord_x0[1],Constants::_cry3_51799_ua9_pos+s);
            gr_x->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;

            s_status = kTRUE;
        }
        else if(s_status)
        {
            // DRIFT4
            if(!magnet->GetNewCoordDrift(DRIFTL4,order,coord_temp_1_x,coord_temp_2_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
        }
        if(s_status)
        {
            // SEXT1
            if(!magnet->GetNewCoordSextupole(Charge_C*KS1,p,P0,SL,order,coord_temp_2_x,coord_temp_1_x,APH,APV))
            {if(print) cout<<"## At : "<<Constants::_lsf_52005_pos<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_temp_1_x[0],coord_temp_1_x[1],Constants::_lsf_52005_pos);
            gr_x->SetPoint(gr_x_ipoint,Constants::_lsf_52005_pos,coord_temp_1_x[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_lsf_52005_pos,coord_temp_1_x[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_lsf_52005_pos,coord_temp_1_x[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_lsf_52005_pos,coord_temp_1_x[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;
        }
        //-----------------------------------------------------------------------------------------------------------------------------//
        if(!s_status && s < Constants::_q3_52010_pos - Constants::_cry3_51799_ua9_pos)
        {
            DRIFTL5 = Constants::_q3_52010_pos - (Constants::_cry3_51799_ua9_pos + s);
            // DRIFT5-S
            if(!magnet->GetNewCoordDrift(DRIFTL5,order,coord_x0,coord_temp_2_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_x0[0],coord_x0[1],Constants::_cry3_51799_ua9_pos+s);
            gr_x->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;

            s_status = kTRUE;
        }
        else if(s_status)
        {
            // DRIFT5
            if(!magnet->GetNewCoordDrift(DRIFTL5,order,coord_temp_1_x,coord_temp_2_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
        }
        if(s_status)
        {
            // QUAD3: FOC in X, DEFOC in Y
            if(!magnet->GetNewCoordQuadrupole(Charge_C*KQ3,p,P0,QL,order,coord_temp_2_x,coord_temp_1_x,APH,APV))
            {if(print) cout<<"## At : "<<Constants::_q3_52010_pos<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_temp_1_x[0],coord_temp_1_x[1],Constants::_q3_52010_pos);
            gr_x->SetPoint(gr_x_ipoint,Constants::_q3_52010_pos,coord_temp_1_x[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_q3_52010_pos,coord_temp_1_x[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_q3_52010_pos,coord_temp_1_x[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_q3_52010_pos,coord_temp_1_x[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;
        }
        //-----------------------------------------------------------------------------------------------------------------------------//
        if(!s_status && s < Constants::_q3_52010_pos + DRIFTL6 - Constants::_cry3_51799_ua9_pos)
        {
            DRIFTL6 = Constants::_q3_52010_pos + DRIFTL6 - (Constants::_cry3_51799_ua9_pos + s);
            // DRIFT6-S
            if(!magnet->GetNewCoordDrift(DRIFTL6,order,coord_x0,coord_temp_2_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_x0[0],coord_x0[1],Constants::_cry3_51799_ua9_pos+s);
            gr_x->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;

            s_status = kTRUE;
        }
        else if(s_status)
        {
            // DRIFT6
            if(!magnet->GetNewCoordDrift(DRIFTL6,order,coord_temp_1_x,coord_temp_2_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
        }
        if(s_status)
        {
            // DIPOLE1: BEND & DEFOC in X, FOC in Y
            if(!magnet->GetNewCoordDipole(P0,p,ADL,Charge_C,DL,order,coord_temp_2_x,coord_temp_1_x,APH,APV))
            {if(print) cout<<"## At : "<<Constants::_mba_52030_pos<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_temp_1_x[0],coord_temp_1_x[1],Constants::_mba_52030_pos+DL/2);
            gr_x->SetPoint(gr_x_ipoint,Constants::_mba_52030_pos+DL/2,coord_temp_1_x[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_mba_52030_pos+DL/2,coord_temp_1_x[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_mba_52030_pos+DL/2,coord_temp_1_x[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_mba_52030_pos+DL/2,coord_temp_1_x[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;
        }
        //-----------------------------------------------------------------------------------------------------------------------------//
        if(!s_status && s < Constants::_mba_52030_pos + DL/2 + DRIFTL7 - Constants::_cry3_51799_ua9_pos)
        {
            DRIFTL7 = Constants::_mba_52030_pos + DL/2 + DRIFTL7 - (Constants::_cry3_51799_ua9_pos + s);
            // DRIFT7
            if(!magnet->GetNewCoordDrift(DRIFTL7,order,coord_x0,coord_temp_2_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_x0[0],coord_x0[1],Constants::_cry3_51799_ua9_pos+s);
            gr_x->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;

            s_status = kTRUE;
        }
        else if(s_status)
        {
            // DRIFT7
            if(!magnet->GetNewCoordDrift(DRIFTL7,order,coord_temp_1_x,coord_temp_2_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_temp_2_x[0],coord_temp_2_x[1],Constants::_mba_52030_pos+DL/2+DRIFTL7);
        }
        if(s_status)
        {
            // DIPOLE2: BEND & DEFOC in X, FOC in Y
            if(!magnet->GetNewCoordDipole(P0,p,ADL,Charge_C,DL,order,coord_temp_2_x,coord_temp_1_x,APH,APV))
            {if(print) cout<<"## At : "<<Constants::_mba_52050_pos<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_temp_1_x[0],coord_temp_1_x[1],Constants::_mba_52050_pos+DL/2);
            gr_x->SetPoint(gr_x_ipoint,Constants::_mba_52050_pos+DL/2,coord_temp_1_x[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_mba_52050_pos+DL/2,coord_temp_1_x[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_mba_52050_pos+DL/2,coord_temp_1_x[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_mba_52050_pos+DL/2,coord_temp_1_x[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;
        }
        //-----------------------------------------------------------------------------------------------------------------------------//
        if(!s_status && s < Constants::_mba_52050_pos + DL/2 + DRIFTL8 - Constants::_cry3_51799_ua9_pos)
        {
            DRIFTL8 = Constants::_mba_52050_pos + DL/2 + DRIFTL8 - (Constants::_cry3_51799_ua9_pos + s);
            // DRIFT8
            if(!magnet->GetNewCoordDrift(DRIFTL8,order,coord_x0,coord_temp_2_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_x0[0],coord_x0[1],Constants::_cry3_51799_ua9_pos+s);
            gr_x->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;

            s_status = kTRUE;
        }
        else if(s_status)
        {
            // DRIFT8
            if(!magnet->GetNewCoordDrift(DRIFTL8,order,coord_temp_1_x,coord_temp_2_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_temp_2_x[0],coord_temp_2_x[1],Constants::_mba_52050_pos+DL/2+DRIFTL8);
        }
        if(s_status)
        {
            // DIPOLE3: BEND & DEFOC in X, FOC in Y
            if(!magnet->GetNewCoordDipole(P0,p,ADL,Charge_C,DL,order,coord_temp_2_x,coord_temp_1_x,APH,APV))
            {if(print) cout<<"## At : "<<Constants::_mbb_52070_pos<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_temp_1_x[0],coord_temp_1_x[1],Constants::_mbb_52070_pos+DL/2);
            gr_x->SetPoint(gr_x_ipoint,Constants::_mbb_52070_pos+DL/2,coord_temp_1_x[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_mbb_52070_pos+DL/2,coord_temp_1_x[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_mbb_52070_pos+DL/2,coord_temp_1_x[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_mbb_52070_pos+DL/2,coord_temp_1_x[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;
        }
        //-----------------------------------------------------------------------------------------------------------------------------//
        if(!s_status && s < Constants::_mbb_52070_pos + DL/2 + DRIFTL9 - Constants::_cry3_51799_ua9_pos)
        {
            DRIFTL9 = Constants::_mbb_52070_pos + DL/2 + DRIFTL9 - (Constants::_cry3_51799_ua9_pos + s);
            // DRIFT9-S
            if(!magnet->GetNewCoordDrift(DRIFTL9,order,coord_x0,coord_temp_2_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_x0[0],coord_x0[1],Constants::_cry3_51799_ua9_pos+s);
            gr_x->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;

            s_status = kTRUE;
        }
        else if(s_status)
        {
            // DRIFT9
            if(!magnet->GetNewCoordDrift(DRIFTL9,order,coord_temp_1_x,coord_temp_2_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_temp_2_x[0],coord_temp_2_x[1],Constants::_mbb_52070_pos+DL/2+DRIFTL9);
        }
        if(s_status)
        {
            // DIPOLE4: BEND & DEFOC in X, FOC in Y
            if(!magnet->GetNewCoordDipole(P0,p,ADL,Charge_C,DL,order,coord_temp_2_x,coord_temp_1_x,APH,APV))
            {if(print) cout<<"## At : "<<Constants::_mbb_52090_pos<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_temp_1_x[0],coord_temp_1_x[1],Constants::_mbb_52090_pos+DL/2);
            gr_x->SetPoint(gr_x_ipoint,Constants::_mbb_52090_pos+DL/2,coord_temp_1_x[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_mbb_52090_pos+DL/2,coord_temp_1_x[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_mbb_52090_pos+DL/2,coord_temp_1_x[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_mbb_52090_pos+DL/2,coord_temp_1_x[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;
        }
        //-----------------------------------------------------------------------------------------------------------------------------//
        if(!s_status && s < Constants::_mbb_52090_pos + DL/2 + DRIFTL10 - Constants::_cry3_51799_ua9_pos)
        {
            DRIFTL10 = Constants::_mbb_52090_pos+DL/2+DRIFTL10 - (Constants::_cry3_51799_ua9_pos + s);
            // DRIFT10-S
            if(!magnet->GetNewCoordDrift(DRIFTL10,order,coord_x0,coord_temp_2_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_x0[0],coord_x0[1],Constants::_cry3_51799_ua9_pos+s);
            gr_x->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;

            s_status = kTRUE;
        }
        else if(s_status)
        {
            // DRIFT10
            if(!magnet->GetNewCoordDrift(DRIFTL10,order,coord_temp_1_x,coord_temp_2_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_temp_2_x[0],coord_temp_2_x[1],Constants::_mbb_52090_pos+DL/2+DRIFTL10);
        }
        if(s_status)
        {
            // QUAD4: FOC in Y, DEFOC in X
            if(!magnet->GetNewCoordQuadrupole(Charge_C*KQ4,p,P0,QL,order,coord_temp_2_x,coord_temp_1_x,APH,APV))
            {if(print) cout<<"## At : "<<Constants::_q4_52110_pos<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_temp_1_x[0],coord_temp_1_x[1],Constants::_q4_52110_pos);
            gr_x->SetPoint(gr_x_ipoint,Constants::_q4_52110_pos,coord_temp_1_x[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_q4_52110_pos,coord_temp_1_x[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_q4_52110_pos,coord_temp_1_x[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_q4_52110_pos,coord_temp_1_x[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;
        }
        //-----------------------------------------------------------------------------------------------------------------------------//
        if(!s_status && s < Constants::_q4_52110_pos + DRIFTL11 - Constants::_cry3_51799_ua9_pos)
        {
            DRIFTL11 = Constants::_q4_52110_pos + DRIFTL11 - (Constants::_cry3_51799_ua9_pos + s);
            // DRIFT11-S
            if(!magnet->GetNewCoordDrift(DRIFTL11,order,coord_x0,coord_temp_2_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_x0[0],coord_x0[1],Constants::_cry3_51799_ua9_pos+s);
            gr_x->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;

            s_status = kTRUE;
        }
        else if(s_status)
        {
            // DRIFT11
            if(!magnet->GetNewCoordDrift(DRIFTL11,order,coord_temp_1_x,coord_temp_2_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_temp_2_x[0],coord_temp_2_x[1],Constants::_q4_52110_pos+DRIFTL11);
        }
        if(s_status)
        {
            // DIPOLE5: BEND & DEFOC in X, FOC in Y
            if(!magnet->GetNewCoordDipole(P0,p,ADL,Charge_C,DL,order,coord_temp_2_x,coord_temp_1_x,APH,APV))
            {if(print) cout<<"## At : "<<Constants::_mbb_52130_pos<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_temp_1_x[0],coord_temp_1_x[1],Constants::_mbb_52130_pos+DL/2);
            gr_x->SetPoint(gr_x_ipoint,Constants::_mbb_52130_pos+DL/2,coord_temp_1_x[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_mbb_52130_pos+DL/2,coord_temp_1_x[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_mbb_52130_pos+DL/2,coord_temp_1_x[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_mbb_52130_pos+DL/2,coord_temp_1_x[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;
        }
        //-----------------------------------------------------------------------------------------------------------------------------//
        if(!s_status && s < Constants::_mbb_52130_pos + DL/2 + DRIFTL12 - Constants::_cry3_51799_ua9_pos)
        {
            DRIFTL12 = Constants::_mbb_52130_pos + DL/2 + DRIFTL12 - (Constants::_cry3_51799_ua9_pos + s);
            // DRIFT12-S
            if(!magnet->GetNewCoordDrift(DRIFTL12,order,coord_x0,coord_temp_2_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_x0[0],coord_x0[1],Constants::_cry3_51799_ua9_pos+s);
            gr_x->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;

            s_status = kTRUE;
        }
        else if(s_status)
        {
            // DRIFT12
            if(!magnet->GetNewCoordDrift(DRIFTL12,order,coord_temp_1_x,coord_temp_2_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_temp_2_x[0],coord_temp_2_x[1],Constants::_mbb_52130_pos+DL/2+DRIFTL12);
        }
        if(s_status)
        {
            // DIPOLE6: BEND & DEFOC in X, FOC in Y
            if(!magnet->GetNewCoordDipole(P0,p,ADL,Charge_C,DL,order,coord_temp_2_x,coord_temp_1_x,APH,APV))
            {if(print) cout<<"## At : "<<Constants::_mbb_52150_pos<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_temp_1_x[0],coord_temp_1_x[1],Constants::_mbb_52150_pos+DL/2);
            gr_x->SetPoint(gr_x_ipoint,Constants::_mbb_52150_pos+DL/2,coord_temp_1_x[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_mbb_52150_pos+DL/2,coord_temp_1_x[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_mbb_52150_pos+DL/2,coord_temp_1_x[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_mbb_52150_pos+DL/2,coord_temp_1_x[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;
        }
        //-----------------------------------------------------------------------------------------------------------------------------//
        if(!s_status && s < Constants::_xrph_52202_ua9_pos - Constants::_cry3_51799_ua9_pos)
        {
            DRIFTL13 = Constants::_xrph_52202_ua9_pos - (Constants::_cry3_51799_ua9_pos + s);
            // DRIFT13-S
            if(!magnet->GetNewCoordDrift(DRIFTL13,order,coord_x0,coord_x,APH,APV))
            {if(print) cout<<"## At : "<<Constants::_xrph_52202_ua9_pos<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_x0[0],coord_x0[1],Constants::_cry3_51799_ua9_pos+s);
            gr_x->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[3]);
            gr_x_ipoint++;
            gr_y_ipoint++;

            s_status = kTRUE;
        }
        else if(s_status)
        {
            // DRIFT13
            if(!magnet->GetNewCoordDrift(DRIFTL13,order,coord_temp_1_x,coord_x,APH,APV))
            {if(print) cout<<"## At : "<<Constants::_xrph_52202_ua9_pos<<" [m] ##"<<endl; /*continue;*/}
        }
        //-----------------------------------------------------------------------------------------------------------------------------//
    }
    else
    {
        if(!s_status && s < Constants::_xrph_52202_ua9_pos - Constants::_cry3_51799_ua9_pos)
        {
            DRIFTL0 = Constants::_xrph_52202_ua9_pos - (Constants::_cry3_51799_ua9_pos + s);
            // DRIFT0-S
            if(!magnet->GetNewCoordDrift(DRIFTL0,order,coord_x0,coord_x,APH,APV))
            {if(print) cout<<"## At : "<<"DRIFT"<<" [m] ##"<<endl; /*continue;*/}
            if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_x0[0],coord_x0[1],Constants::_cry3_51799_ua9_pos+s);
            gr_x->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[0]);
            gr_xp->SetPoint(gr_x_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[1]);
            gr_y->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[2]);
            gr_yp->SetPoint(gr_y_ipoint,Constants::_cry3_51799_ua9_pos+s,coord_x0[3]);
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
        if(print) printf("%10.15f , %10.15f , %10.15f\n",coord_x[0],coord_x[1],Constants::_xrph_52202_ua9_pos);
        gr_x->SetPoint(gr_x_ipoint,Constants::_xrph_52202_ua9_pos,coord_x[0]);
        gr_xp->SetPoint(gr_x_ipoint,Constants::_xrph_52202_ua9_pos,coord_x[1]);
        gr_y->SetPoint(gr_y_ipoint,Constants::_xrph_52202_ua9_pos,coord_x[2]);
        gr_yp->SetPoint(gr_y_ipoint,Constants::_xrph_52202_ua9_pos,coord_x[3]);
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

