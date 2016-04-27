#define ComptAna_cxx
#include "ComptAna.h"
#include <TH1.h>
#include <TH1F.h>
#include <TH2.h>
#include <THStack.h>
#include <TObject.h>
#include <TF1.h>
#include <TStyle.h>
#include <TColor.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TPaveText.h>
#include <TPaletteAxis.h>
#include <TLatex.h>
#include <TLegend.h> 
#include <TLine.h> 
#include <TEllipse.h> 
#include <TArrow.h> 
#include <TText.h> 
#include <string.h>
#include <sstream>
#include <iostream>
#include <fstream>

void ComptAna::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L ComptAna.C
//      Root > ComptAna t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
//
  
  ofstream outs1;
  ofstream outs2;
  Bool_t epsOK = false;
  Bool_t pngOK = false;
  Bool_t pdfOK = false;

  const Int_t NRGBs = 5;
  const Int_t NCont = 255;

//   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
//   Double_t red[NRGBs]   = { 1.00, 0.84, 0.61, 0.34, 0.00 };
//   Double_t green[NRGBs] = { 1.00, 0.84, 0.61, 0.34, 0.00 };
//   Double_t blue[NRGBs]  = { 1.00, 0.84, 0.61, 0.34, 0.00 };

  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };

  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);

  gStyle->SetNumberContours(NCont);  

  Int_t itc = 15;
  string itc_str;
//   stringstream ConvertStream;
//   ConvertStream << itc;
//   ConvertStream >> itc_str;   
   
  Bool_t inTCounter = false;
  Bool_t intime = true;
  //~ Bool_t intime = false ;
  string label;
  if (intime) {
    label = "dat-all";
  } else {
    label = "out-of-time-dat-all";
  }

  Int_t tclow  = 2*itc-1;
  Int_t tchigh = 2*itc;

  double rmin, dely, delx;
  double phi;
  static const Int_t mode = 5;

  TLatex latex;
  latex.SetNDC();
  latex.SetTextFont(42); 
  latex.SetTextSize(0.040); 
  latex.SetTextColor(1);        

  if (itc < 10) {
    itc_str = "0" + itc_str;
  }

  gStyle->SetLabelFont(52,"XY");
  gStyle->SetLabelSize(0.035,"XY");
  gStyle->SetTitleFont(42,"XY");

  TCanvas *c0 = new TCanvas("c0","Cluster Separation - All Events",798,35,600,600);  
  c0->SetFillColor(0);  
  c0->SetFrameFillColor(255);  
  c0->SetBorderMode(0);  
  TCanvas *c1 = new TCanvas("c1","Cluster Separation - in Time",848,70,600,600);  
  c1->SetFillColor(0);  
  c1->SetFrameFillColor(255);  
  c1->SetBorderMode(0);    
  TCanvas *c2 = new TCanvas("c2","Cluster Separation - in Plane",898,105,600,600);  
  c2->SetFillColor(0);  
  c2->SetFrameFillColor(255);  
  c2->SetBorderMode(0);  
  TCanvas *c3 = new TCanvas("c3","Cluster Separation - in Acceptance",948,140,600,600);  
  c3->SetFillColor(0);  
  c3->SetFrameFillColor(255);  
  c3->SetBorderMode(0);    
  TCanvas *c4 = new TCanvas("c4","Cluster Separation - Elastic",998,175,600,600);  
  c4->SetFillColor(0);  
  c4->SetFrameFillColor(255);  
  c4->SetBorderMode(0);    
  TCanvas *c6 = new TCanvas("c6","Cluster Separation - in Target",1098,245,600,600);  
  c6->SetFillColor(0);  
  c6->SetFrameFillColor(255);  
  c6->SetBorderMode(0);  
  TCanvas *c7 = new TCanvas("c7","Cluster Separation - in Energy",1148,280,600,600);  
  c7->SetFillColor(0);  
  c7->SetFrameFillColor(255);  
  c7->SetBorderMode(0);    
  TCanvas *c8 = new TCanvas("c8","Cluster Separation - Publication Plot",1198,315,600,600);   
  c8->SetFillColor(0);   
  c8->SetFrameFillColor(0);   
  c8->SetBorderMode(0);      
  TCanvas *c9 = new TCanvas("c9","#DeltaE VS. Z - Publication Plot",1218,350,600,600);   
  c9->SetFillColor(0);   
  c9->SetFrameFillColor(0);   
  c9->SetBorderMode(0);         
  TCanvas *c01 = new TCanvas("c01","Z VS. Elasticity - Publication Plot",1218,385,600,600);   
  c01->SetFillColor(0);   
  c01->SetFrameFillColor(0);   
  c01->SetBorderMode(0); 
  
  TCanvas *c02 = new TCanvas("c02","Cluster Position",1218,385,600,600);   
  c02->SetFillColor(0);   
  c02->SetFrameFillColor(0);   
  c02->SetBorderMode(0); 
  
  TCanvas *c03 = new TCanvas("c03","Module ID",1218,385,600,600);   
  c03->SetFillColor(0);   
  c03->SetFrameFillColor(0);   
  c03->SetBorderMode(0); 

  TCanvas *c10 = new TCanvas("c10","Elasticity",70,35,600,600);  
  c10->SetFillColor(0);  
  c10->SetFrameFillColor(255);  
  c10->SetBorderMode(0);     
  TCanvas *c11 = new TCanvas("c11","Distance to Target",100,135,600,600);  
  c11->SetFillColor(0);  
  c11->SetFrameFillColor(255);  
  c11->SetBorderMode(0);          
  TCanvas *c12 = new TCanvas("c12","Cluster Separation",130,235,600,600);  
  c12->SetFillColor(0);  
  c12->SetFrameFillColor(255);  
  c12->SetBorderMode(0);         
  TCanvas *c14 = new TCanvas("c14","Energy Difference",160,335,600,600);  
  c14->SetFillColor(0);  
  c14->SetFrameFillColor(255);  
  c14->SetBorderMode(0);           
  TCanvas *c15 = new TCanvas("c15","Coplanarity",190,435,600,600);  
  c15->SetFillColor(0);  
  c15->SetFrameFillColor(255);  
  c15->SetBorderMode(0);                
  TCanvas *c16 = new TCanvas("c16","z cut",220,535,600,600);  
  c16->SetFillColor(0);  
  c16->SetFrameFillColor(255);  
  c16->SetBorderMode(0);                 
  TCanvas *c17 = new TCanvas("c17","dE cut",300,535,600,600);  
  c17->SetFillColor(0);  
  c17->SetFrameFillColor(255);  
  c17->SetBorderMode(0);                
  TCanvas *c18 = new TCanvas("c18","dt cut",380,535,600,600);  
  c18->SetFillColor(0);  
  c18->SetFrameFillColor(255);  
  c18->SetBorderMode(0);                 
  TCanvas *c19 = new TCanvas("c19","d#phi cut",460,535,600,600);  
  c19->SetFillColor(0);  
  c19->SetFrameFillColor(255);  
  c19->SetBorderMode(0);               
  TCanvas *c20 = new TCanvas("c20","Rmin cut",540,535,600,600);  
  c20->SetFillColor(0);  
  c20->SetFrameFillColor(255);  
  c20->SetBorderMode(0);          
              
  TCanvas *c21 = new TCanvas("c21","Elasticity Fits",0,35,800,1100);  
  c21->SetFillColor(0);  
  c21->SetFrameFillColor(255);  
  c21->SetBorderMode(0);
  c21->Divide(3,6,0.0001,0.0001);          

//   gPad->SetRightMargin(0.05);   
//   gPad->SetTopMargin(0.125);   
//   gPad->SetBottomMargin(0.125);   
//   gPad->SetBorderMode(0); 

  TH2F *hdydx0 = new TH2F("hdydx0","Cluster Separation: #Deltay VS. #Deltax - No Cuts",320,-32,32,320,-32,32);
  TH2F *hdydx1 = new TH2F("hdydx1","Cluster Separation: #Deltay VS. #Deltax - In Time",320,-32,32,320,-32,32);
  TH2F *hdydx2 = new TH2F("hdydx2","Cluster Separation: #Deltay VS. #Deltax - In Plane",320,-32,32,320,-32,32);
  TH2F *hdydx3 = new TH2F("hdydx3","Cluster Separation: #Deltay VS. #Deltax - In Acceptance",320,-32,32,320,-32,32);
  TH2F *hdydx4 = new TH2F("hdydx4","Cluster Separation: #Deltay VS. #Deltax - In Separation",320,-32,32,320,-32,32);
  TH2F *hy1x1 = new TH2F("hy1x1","Cluster Positions - EXPERIMENT",320,-16,16,320,-16,16);
  TH2F *hy2x2 = new TH2F("hy2x2","Cluster Positions - EXPERIMENT",320,-16,16,320,-16,16);
  //~ TH2F *hid0 = new TH2F("hid0","Modules IDs - EXPERIMENT",2160,999.5,2160.5,121,1659.5,1780.5);
  TH2F *hdydx6 = new TH2F("hdydx6","Cluster Separation: #Deltay VS. #Deltax - In Target",320,-32,32,320,-32,32);
  TH2F *hdydx7 = new TH2F("hdydx7","Cluster Separation: #Deltay VS. #Deltax - In Energy",320,-32,32,320,-32,32); 
  TH2F *hdydx8 = new TH2F("hdydx8","Cluster Separation: #Deltay VS. #Deltax - EXPERIMENT",320,-40,40,320,-40,40); 
 
  TH2F *hdEdZ0 = new TH2F("hdEdZ0","#DeltaE & Z Cuts in #DeltaE-Z Plane - Coincidence",320,500,950,320,-3.0,3.0); 
  TH2F *helaz0 = new TH2F("helaz0","Z VS. Elasticity - Coincidence",320,-1.0,2.0,320,200,1200); 

  TH1F *htdiff0 = new TH1F("htdiff0","Coincidence Time",100,-20.,30.);

  THStack *helass = new THStack("helass","");
  TH1F *helas0 = new TH1F("helas0","Elasticity:  E_{0} - (E_{1} + E_{2})",300,-0.5,1.5);
  helass->Add(helas0);
  TH1F *helas1 = new TH1F("helas1","Elasticity:  E_{0} - (E_{1} + E_{2})",300,-0.5,1.5);
  helass->Add(helas1);
  TH1F *helas2 = new TH1F("helas2","Elasticity:  E_{0} - (E_{1} + E_{2})",300,-0.5,1.5);
  helass->Add(helas2);
  TH1F *helas3 = new TH1F("helas3","Elasticity:  E_{0} - (E_{1} + E_{2})",300,-0.5,1.5);
  helass->Add(helas3);
  TH1F *helas4 = new TH1F("helas4","Elasticity:  E_{0} - (E_{1} + E_{2})",300,-0.5,1.5);
  helass->Add(helas4);
  TH1F *helas5 = new TH1F("helas5","Elasticity:  E_{0} - (E_{1} + E_{2})",300,-0.5,1.5);
  helass->Add(helas5);
  TH1F *helas6 = new TH1F("helas6","Elasticity:  E_{0} - (E_{1} + E_{2})",300,-0.5,1.5);
  helass->Add(helas6);
  TH1F *helas7 = new TH1F("helas7","Elasticity:  E_{0} - (E_{1} + E_{2})",300,-0.5,1.5);
  helass->Add(helas7);

  THStack *hopnzs = new THStack("hopnzs","");
  TH1F *hopnz0 = new TH1F("hopnz0","Distance To Target (Opening Angle Based)",300,100,1000);
  hopnzs->Add(hopnz0);
  TH1F *hopnz1 = new TH1F("hopnz1","Distance To Target (Opening Angle Based)",300,100,1000);
  hopnzs->Add(hopnz1);
  TH1F *hopnz2 = new TH1F("hopnz2","Distance To Target (Opening Angle Based)",300,100,1000);
  hopnzs->Add(hopnz2);
  TH1F *hopnz3 = new TH1F("hopnz3","Distance To Target (Opening Angle Based)",300,100,1000);
  hopnzs->Add(hopnz3);
  TH1F *hopnz4 = new TH1F("hopnz4","Distance To Target (Opening Angle Based)",300,100,1000);
  hopnzs->Add(hopnz4);
  TH1F *hopnz5 = new TH1F("hopnz5","Distance To Target (Opening Angle Based)",300,100,1000);
  hopnzs->Add(hopnz5);
  TH1F *hopnz6 = new TH1F("hopnz6","Distance To Target (Opening Angle Based)",300,100,1000);
  hopnzs->Add(hopnz6);
  TH1F *hopnz7 = new TH1F("hopnz7","Distance To Target (Opening Angle Based)",300,100,1000);
  hopnzs->Add(hopnz7);  
  TH1F *hopnz8 = new TH1F("hopnz8","Distance To Target (Opening Angle Based)",300,400,1000);  

  THStack *hrmins = new THStack("hrmins","");
  TH1F *hrmin0 = new TH1F("hrmin0","Separation Between Clusters",300,5.0,40.0);
  hrmins->Add(hrmin0);
  TH1F *hrmin1 = new TH1F("hrmin1","Separation Between Clusters",300,5.0,40.0);
  hrmins->Add(hrmin1);
  TH1F *hrmin2 = new TH1F("hrmin2","Separation Between Clusters",300,5.0,40.0);
  hrmins->Add(hrmin2);
  TH1F *hrmin3 = new TH1F("hrmin3","Separation Between Clusters",300,5.0,40.0);
  hrmins->Add(hrmin3);
  TH1F *hrmin4 = new TH1F("hrmin4","Separation Between Clusters",300,5.0,40.0);
  hrmins->Add(hrmin4);
  TH1F *hrmin5 = new TH1F("hrmin5","Separation Between Clusters",300,5.0,40.0);
  hrmins->Add(hrmin5);
  TH1F *hrmin6 = new TH1F("hrmin6","Separation Between Clusters",300,5.0,40.0);
  hrmins->Add(hrmin6); 
  TH1F *hrmin7 = new TH1F("hrmin7","Separation Between Clusters",300,5.0,40.0);
  hrmins->Add(hrmin7);  
  TH1F *hrmin8 = new TH1F("hrmin8","Separation Between Clusters",300,5.0,40.0);

  THStack *hdeles = new THStack("hdeles","");
  TH1F *hdele0 = new TH1F("hdele0","Energy Difference: E_{0} - E_{cal}",300,-3.,3.);
  hdeles->Add(hdele0);
  TH1F *hdele1 = new TH1F("hdele1","Energy Difference: E_{0} - E_{cal}",300,-3.,3.);
  hdeles->Add(hdele1);
  TH1F *hdele2 = new TH1F("hdele2","Energy Difference: E_{0} - E_{cal}",300,-3.,3.);
  hdeles->Add(hdele2);
  TH1F *hdele3 = new TH1F("hdele3","Energy Difference: E_{0} - E_{cal}",300,-3.,3.);
  hdeles->Add(hdele3);
  TH1F *hdele4 = new TH1F("hdele4","Energy Difference: E_{0} - E_{cal}",300,-3.,3.);
  hdeles->Add(hdele4);
  TH1F *hdele5 = new TH1F("hdele5","Energy Difference: E_{0} - E_{cal}",300,-3.,3.);
  hdeles->Add(hdele5);
  TH1F *hdele6 = new TH1F("hdele6","Energy Difference: E_{0} - E_{cal}",300,-3.,3.);
  hdeles->Add(hdele6);
  TH1F *hdele7 = new TH1F("hdele7","Energy Difference: E_{0} - E_{cal}",300,-3.,3.);
  hdeles->Add(hdele7);
  TH1F *hdele8 = new TH1F("hdele8","Energy Difference: E_{0} - E_{cal}",300,-3.,3.);

  THStack *hcopls = new THStack("hcopls","");
  TH1F *hcopl0 = new TH1F("hcopl0","Coplanarity: #phi_{e^{-}} - #phi_{#gamma}",280,120.,240.);
  hcopls->Add(hcopl0);
  TH1F *hcopl1 = new TH1F("hcopl1","Coplanarity: #phi_{e^{-}} - #phi_{#gamma}",280,120.,240.);
  hcopls->Add(hcopl1);
  TH1F *hcopl2 = new TH1F("hcopl2","Coplanarity: #phi_{e^{-}} - #phi_{#gamma}",280,120.,240.);
  hcopls->Add(hcopl2);
  TH1F *hcopl3 = new TH1F("hcopl3","Coplanarity: #phi_{e^{-}} - #phi_{#gamma}",280,120.,240.);
  hcopls->Add(hcopl3);
  TH1F *hcopl4 = new TH1F("hcopl4","Coplanarity: #phi_{e^{-}} - #phi_{#gamma}",280,120.,240.);
  hcopls->Add(hcopl4);
  TH1F *hcopl5 = new TH1F("hcopl5","Coplanarity: #phi_{e^{-}} - #phi_{#gamma}",280,120.,240.);
  hcopls->Add(hcopl5);
  TH1F *hcopl6 = new TH1F("hcopl6","Coplanarity: #phi_{e^{-}} - #phi_{#gamma}",280,120.,240.);
  hcopls->Add(hcopl6);
  TH1F *hcopl7 = new TH1F("hcopl7","Coplanarity: #phi_{e^{-}} - #phi_{#gamma}",280,120.,240.);
  hcopls->Add(hcopl7);

  THStack *hrots = new THStack("hrots","stacked Separation Slices histograms");
  TH1F *hrot01 = new TH1F( "hrot01", "Slice 1",  250, 10,35);
  hrots->Add(hrot01);
  TH1F *hrot02 = new TH1F( "hrot02", "Slice 2",  250, 10,35);
  hrots->Add(hrot02);
  TH1F *hrot03 = new TH1F( "hrot03", "Slice 3",  250, 10,35);
  hrots->Add(hrot03);
  TH1F *hrot04 = new TH1F( "hrot04", "Slice 4",  250, 10,35);
  hrots->Add(hrot04);
  TH1F *hrot05 = new TH1F( "hrot05", "Slice 5",  250, 10,35);
  hrots->Add(hrot05);
  TH1F *hrot06 = new TH1F( "hrot06", "Slice 6",  250, 10,35);
  hrots->Add(hrot06);
  TH1F *hrot07 = new TH1F( "hrot07", "Slice 7",  250, 10,35);
  hrots->Add(hrot07);
  TH1F *hrot08 = new TH1F( "hrot08", "Slice 8",  250, 10,35);
  hrots->Add(hrot08);
  TH1F *hrot09 = new TH1F( "hrot09", "Slice 9",  250, 10,35);
  hrots->Add(hrot09);
  TH1F *hrot10 = new TH1F( "hrot10", "Slice 10", 100, -0.5,1.5);
  hrots->Add(hrot10);
  TH1F *hrot11 = new TH1F( "hrot11", "Slice 11", 100, -0.5,1.5);
  hrots->Add(hrot11);
  TH1F *hrot12 = new TH1F( "hrot12", "Slice 12", 100, -0.5,1.5);
  hrots->Add(hrot12);
  TH1F *hrot13 = new TH1F( "hrot13", "Slice 13", 100, -0.5,1.5);
  hrots->Add(hrot13);
  TH1F *hrot14 = new TH1F( "hrot14", "Slice 14", 100, -0.5,1.5);
  hrots->Add(hrot14);
  TH1F *hrot15 = new TH1F( "hrot15", "Slice 15", 100, -0.5,1.5);
  hrots->Add(hrot15);
  TH1F *hrot16 = new TH1F( "hrot16", "Slice 16", 100, -0.5,1.5);
  hrots->Add(hrot16);
  TH1F *hrot17 = new TH1F( "hrot17", "Slice 17", 100, -0.5,1.5);
  hrots->Add(hrot17);
  TH1F *hrot18 = new TH1F( "hrot18", "Slice 18", 100, -0.5,1.5);
  hrots->Add(hrot18);

  THStack *htids = new THStack("htids","stacked T Counter Elasticity histograms");
  TH1F *htid01 = new TH1F( "htid01", "T Counter 1",  120, -0.3,0.9);
  htids->Add(htid01);
  TH1F *htid02 = new TH1F( "htid02", "T Counter 2",  120, -0.3,0.9);
  htids->Add(htid02);
  TH1F *htid03 = new TH1F( "htid03", "T Counter 3",  120, -0.3,0.9);
  htids->Add(htid03);
  TH1F *htid04 = new TH1F( "htid04", "T Counter 4",  120, -0.3,0.9);
  htids->Add(htid04);
  TH1F *htid05 = new TH1F( "htid05", "T Counter 5",  120, -0.3,0.9);
  htids->Add(htid05);
  TH1F *htid06 = new TH1F( "htid06", "T Counter 6",  120, -0.3,0.9);
  htids->Add(htid06);
  TH1F *htid07 = new TH1F( "htid07", "T Counter 7",  120, -0.3,0.9);
  htids->Add(htid07);
  TH1F *htid08 = new TH1F( "htid08", "T Counter 8",  120, -0.3,0.9);
  htids->Add(htid08);
  TH1F *htid09 = new TH1F( "htid09", "T Counter 9",  120, -0.3,0.9);
  htids->Add(htid09);
  TH1F *htid10 = new TH1F( "htid10", "T Counter 10", 120, -0.3,0.9);
  htids->Add(htid10);
  TH1F *htid11 = new TH1F( "htid11", "T Counter 11", 120, -0.3,0.9);
  htids->Add(htid11);
  TH1F *htid12 = new TH1F( "htid12", "T Counter 12", 120, -0.3,0.9);
  htids->Add(htid12);
  TH1F *htid13 = new TH1F( "htid13", "T Counter 13", 120, -0.3,0.9);
  htids->Add(htid13);
  TH1F *htid14 = new TH1F( "htid14", "T Counter 14", 120, -0.3,0.9);
  htids->Add(htid14);
  TH1F *htid15 = new TH1F( "htid15", "T Counter 15", 120, -0.3,0.9);
  htids->Add(htid15);
  TH1F *htid16 = new TH1F( "htid16", "T Counter 16", 120, -0.3,0.9);
  htids->Add(htid16);
  TH1F *htid17 = new TH1F( "htid17", "T Counter 17", 120, -0.3,0.9);
  htids->Add(htid17);
  TH1F *htid18 = new TH1F( "htid18", "T Counter 18", 120, -0.3,0.9);
  htids->Add(htid18);

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
	//~ for (Long64_t jentry=0; jentry<100000;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    double ev = jentry;
    for (int i=1; i<=5; i++)  { 
      ev = ev/10.;
      if (ev < 10) break; 
    }
    if (int(ev) == ev && ev != 0) {
      cout << "   " << jentry <<" events analyzed" << endl;
    } 

    if (itc < 38) {
      inTCounter = tid == tclow || tid == tchigh;
    } else {
      inTCounter = tid == tclow;
    }

	if (fabs(id2-1703)<=1 ||
		fabs(id2-1737)<=1 ||
		fabs(id2-1771)<=1) continue;
		
	if (fabs(id1-1703)<=1 ||
		fabs(id1-1737)<=1 ||
		fabs(id1-1771)<=1) continue;

	//~ if (!inTCounter) continue;

    if (intime) htdiff0->Fill(tdiff);

    if (tCut(ientry,intime) < 0) continue;

    if (!intime) htdiff0->Fill(tdiff);
    hopnz0->Fill(openZ(ientry));
    helas0->Fill(eg-(e1+e2));
    hdydx0->Fill((x2-x1),(y2-y1));
    rmin = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    hrmin0->Fill(rmin);
    hdele0->Fill(delE(ientry,mode));
    phi = fabs(fabs((atan2(y2,x2)-atan2(y1,x1))*r2d));
    hcopl0->Fill(phi);
    
    hy1x1->Fill(x1,y1);
    hy2x2->Fill(x2,y2);
 
    if ((tCut(ientry,intime) > 0)) hdydx8->Fill((x2-x1),(y2-y1)); 

    if ((tCut(ientry,intime) > 0) && 
	(phiCut(ientry) > 0) && 
	(fidCut(ientry) > 0) &&
	(rminCut(ientry) > 0) &&
	(deCut(ientry,mode) > 0)) hopnz8->Fill(openZ(ientry)); 

    if ((tCut(ientry,intime) > 0) && 
	(phiCut(ientry) > 0) && 
	(fidCut(ientry) > 0)) hrmin8->Fill(rmin); 

    if ((tCut(ientry,intime) > 0) && 
	(phiCut(ientry) > 0) && 
	(fidCut(ientry) > 0) &&
	(rminCut(ientry) > 0) &&
	(zCut(ientry) > 0)) hdele8->Fill(delE(ientry,mode)); 

    if ((tCut(ientry,intime) > 0) && 
	(phiCut(ientry) > 0) && 
	(fidCut(ientry) > 0) &&
	(rminCut(ientry) > 0)) hdEdZ0->Fill(openZ(ientry),delE(ientry,mode)); 

    if ((tCut(ientry,intime) > 0) && 
	(phiCut(ientry) > 0) && 
	(fidCut(ientry) > 0) &&
	(rminCut(ientry) > 0) &&
	(deCut(ientry,mode) > 0)) helaz0->Fill(eg-(e1+e2),openZ(ientry)); 

    hopnz1->Fill(openZ(ientry));
    helas1->Fill(eg-(e1+e2));
    hdydx1->Fill((x2-x1),(y2-y1));
    rmin = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    hrmin1->Fill(rmin);
    hdele1->Fill(delE(ientry,mode));
    phi = fabs(fabs((atan2(y2,x2)-atan2(y1,x1))*r2d));
    hcopl1->Fill(phi);

    if (phiCut(ientry) < 0) continue;
    hopnz2->Fill(openZ(ientry));
    helas2->Fill(eg-(e1+e2));
    hdydx2->Fill((x2-x1),(y2-y1));
    rmin = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    hrmin2->Fill(rmin);
    hdele2->Fill(delE(ientry,mode));
    phi = fabs(fabs((atan2(y2,x2)-atan2(y1,x1))*r2d));
    hcopl2->Fill(phi);

    if (fidCut(ientry) < 0) continue;
    hopnz3->Fill(openZ(ientry));
    helas3->Fill(eg-(e1+e2));
    hdydx3->Fill((x2-x1),(y2-y1));
    rmin = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    hrmin3->Fill(rmin);
    hdele3->Fill(delE(ientry,mode));
    phi = fabs(fabs((atan2(y2,x2)-atan2(y1,x1))*r2d));
    hcopl3->Fill(phi);

    if (rminCut(ientry) < 0) continue;
    dely = y2 - y1;
    delx = x2 - x1;
    rmin = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    hopnz4->Fill(openZ(ientry));
    helas4->Fill(eg-(e1+e2));
    hdydx4->Fill((x2-x1),(y2-y1));
    hrmin4->Fill(rmin);
    hdele4->Fill(delE(ientry,mode));
    phi = fabs(fabs((atan2(y2,x2)-atan2(y1,x1))*r2d));
    hcopl4->Fill(phi);

    if (zCut(ientry) < 0) continue;
    hopnz6->Fill(openZ(ientry));
    helas6->Fill(eg-(e1+e2));
    hdydx6->Fill((x2-x1),(y2-y1));
    rmin = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    hrmin6->Fill(rmin);
    hdele6->Fill(delE(ientry,mode));
    phi = fabs(fabs((atan2(y2,x2)-atan2(y1,x1))*r2d));
    hcopl6->Fill(phi);

    if (deCut(ientry,mode) < 0) continue;
    hopnz7->Fill(openZ(ientry));
    helas7->Fill(eg-(e1+e2));
    hdydx7->Fill((x2-x1),(y2-y1));
    rmin = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    hrmin7->Fill(rmin);
    hdele7->Fill(delE(ientry,mode));
    phi = fabs(fabs((atan2(y2,x2)-atan2(y1,x1))*r2d));
    hcopl7->Fill(phi);

    Double_t elast = eg-(e1+e2);

    if (0) {
    switch ((Int_t)tid) {
    case 1: htid01->Fill(elast+0.00580652);
      break;
    case 2: htid01->Fill(elast+0.00580652);
      break;
    case 3: htid02->Fill(elast+0.00293427);
      break;
    case 4: htid02->Fill(elast+0.00293427);
      break;
    case 5: htid03->Fill(elast+0.00186145);
      break;
    case 6: htid03->Fill(elast+0.00186145);
      break;
    case 7: htid04->Fill(elast-7.68004e-05);
      break;
    case 8: htid04->Fill(elast-7.68004e-05);
      break;
    case 9: htid05->Fill(elast-0.000115216);
      break;
    case 10: htid05->Fill(elast-0.000115216);
      break;
    case 11: htid06->Fill(elast-0.000639396);
      break;
    case 12: htid06->Fill(elast-0.000639396);
      break;
    case 13: htid07->Fill(elast-0.000781168);
      break;
    case 14: htid07->Fill(elast-0.000781168);
      break;
    case 15: htid08->Fill(elast-0.0017261);
      break;
    case 16: htid08->Fill(elast-0.0017261);
      break;
    case 17: htid09->Fill(elast-0.00148353);
      break;
    case 18: htid09->Fill(elast-0.00148353);
      break;
    case 19: htid10->Fill(elast-0.000545306);
      break;
    case 20: htid10->Fill(elast-0.000545306);
      break;
    case 21: htid11->Fill(elast-0.000524352);
      break;
    case 22: htid11->Fill(elast-0.000524352);
      break;
    case 23: htid12->Fill(elast+0.00106577);
      break;
    case 24: htid12->Fill(elast+0.00106577);
      break;
    case 25: htid13->Fill(elast+0.00129699);
      break;
    case 26: htid13->Fill(elast+0.00129699);
      break;
    case 27: htid14->Fill(elast+0.00275169);
      break;
    case 28: htid14->Fill(elast+0.00275169);
      break;
    case 29: htid15->Fill(elast+0.0022084);
      break;
    case 30: htid15->Fill(elast+0.0022084);
      break;
    case 31: htid16->Fill(elast+0.00363396);
      break;
    case 32: htid16->Fill(elast+0.00363396);
      break;
    case 33: htid17->Fill(elast+0.00282482);
      break;
    case 34: htid17->Fill(elast+0.00282482);
      break;
    case 35: htid18->Fill(elast+0.00138291);
      break;
    case 36: htid18->Fill(elast+0.00138291);
      break;
    }
   } else {
	//Double_t eshift = -0.019;
    //switch ((Int_t)tid) {
    //case 1: htid01->Fill(elast+0.0436869-eshift);
      //break;
    //case 2: htid02->Fill(elast+0.0435222-eshift);
      //break;
    //case 3: htid03->Fill(elast+0.043274-eshift);
      //break;
    //case 4: htid04->Fill(elast+0.0410391-eshift);
      //break;
    //case 5: htid05->Fill(elast+0.0407392-eshift);
      //break;
    //case 6: htid06->Fill(elast+0.0404459-eshift);
      //break;
    //case 7: htid07->Fill(elast+0.0393751-eshift);
      //break;
    //case 8: htid08->Fill(elast+0.0388285-eshift);
      //break;
    //case 9: htid09->Fill(elast+0.0379375-eshift);
      //break;
    //case 10: htid10->Fill(elast+0.0380293-eshift);
      //break;
    //case 11: htid11->Fill(elast+0.036785-eshift);
      //break;
    //case 12: htid12->Fill(elast+0.0357159-eshift);
      //break;
    //case 13: htid13->Fill(elast+0.0353413-eshift);
      //break;
    //case 14: htid14->Fill(elast+0.034416-eshift);
      //break;
    //case 15: htid15->Fill(elast+0.0341646-eshift);
      //break;
    //case 16: htid16->Fill(elast+0.0334312-eshift);
      //break;
    //case 17: htid17->Fill(elast+0.0325564-eshift);
      //break;
    //case 18: htid18->Fill(elast+0.0316376-eshift);
      //break;
    Double_t eshift = -0.019;
    switch ((Int_t)tid) {
    case 1: htid01->Fill(elast+0.0551758);
      break;			 
    case 2: htid02->Fill(elast+0.0623301);
      break;			 
    case 3: htid03->Fill(elast+0.0620057);
      break;			 
    case 4: htid04->Fill(elast+0.0599143);
      break;			 
    case 5: htid05->Fill(elast+0.0594017);
      break;			 
    case 6: htid06->Fill(elast+0.0594132);
      break;			 
    case 7: htid07->Fill(elast+0.0578676);
      break;			 
    case 8: htid08->Fill(elast+0.0577198);
      break;			 
    case 9: htid09->Fill(elast+0.0570370);
      break;			 
    case 10: htid10->Fill(elast+0.0568170);
      break;			 
    case 11: htid11->Fill(elast+0.0557148);
      break;			 
    case 12: htid12->Fill(elast+0.0546758);
      break;			 
    case 13: htid13->Fill(elast+0.0543217);
      break;			 
    case 14: htid14->Fill(elast+0.0533901);
      break;			 
    case 15: htid15->Fill(elast+0.0530006);
      break;			 
    case 16: htid16->Fill(elast+0.0525619);
      break;			 
    case 17: htid17->Fill(elast+0.0515202);
      break;			 
    case 18: htid18->Fill(elast+0.0504658);
	  break;
    }
   }
    
    if (abs(dely/delx*r2d)<10) hrot01->Fill(rmin);
    if (abs(dely/delx*r2d-30)<10) hrot02->Fill(rmin);
    if (abs(dely/delx*r2d-50)<10) hrot03->Fill(rmin);
    if (abs(dely/delx*r2d-70)<10) hrot04->Fill(rmin);
    if (abs(dely/delx*r2d-90)<10) hrot05->Fill(rmin);
    if (abs(dely/delx*r2d-110)<10) hrot06->Fill(rmin);
    if (abs(dely/delx*r2d-130)<10) hrot07->Fill(rmin);
    if (abs(dely/delx*r2d-150)<10) hrot08->Fill(rmin);
    if (abs(dely/delx*r2d-170)<10) hrot09->Fill(rmin);
    if (abs(dely/delx*r2d-10)<10) hrot10->Fill(rmin);
    if (abs(dely/delx*r2d-10)<10) hrot11->Fill(rmin);
    if (abs(dely/delx*r2d-10)<10) hrot12->Fill(rmin);
    if (abs(dely/delx*r2d-10)<10) hrot13->Fill(rmin);
    if (abs(dely/delx*r2d-10)<10) hrot14->Fill(rmin);
    if (abs(dely/delx*r2d-10)<10) hrot15->Fill(rmin);
    if (abs(dely/delx*r2d-10)<10) hrot16->Fill(rmin);
    if (abs(dely/delx*r2d-10)<10) hrot17->Fill(rmin);
    if (abs(dely/delx*r2d-10)<10) hrot18->Fill(rmin);
   
  }

  c1->cd();
  hdydx1->Draw("colz");
  gPad->Update();

  TPaletteAxis *mypalette = (TPaletteAxis*)hdydx1->GetListOfFunctions()->FindObject("palette");

  mypalette->SetX1NDC(0.910);
  mypalette->SetX2NDC(0.935);
  mypalette->SetLabelFont(52);
  mypalette->SetLabelSize(0.028);
  
  hdydx1->SetStats(0);

  hdydx1->GetXaxis()->SetTitle("#Deltax - Distance between clusters (cm)");
  hdydx1->GetYaxis()->SetTitle("#Deltay - Distance between clusters (cm)");

  hdydx1->GetYaxis()->SetTitleOffset(1.1);
  hdydx1->Draw("colz");

  const char *format = "dydx-intime-%s-tcs.%s";
  Print(c1,format,label,"eps",epsOK);
  Print(c1,format,label,"png",pngOK);
  Print(c1,format,label,"pdf",pdfOK);

  c2->cd();
  hdydx2->Draw("colz");
  gPad->Update();

  mypalette = (TPaletteAxis*)hdydx2->GetListOfFunctions()->FindObject("palette");

  mypalette->SetX1NDC(0.910);
  mypalette->SetX2NDC(0.935);
  mypalette->SetLabelFont(52);
  mypalette->SetLabelSize(0.028);
  
  hdydx2->SetStats(0);

  hdydx2->GetXaxis()->SetTitle("#Deltax - Distance between clusters (cm)");
  hdydx2->GetYaxis()->SetTitle("#Deltay - Distance between clusters (cm)");

  hdydx2->GetYaxis()->SetTitleOffset(1.1);
  hdydx2->Draw("colz"); 

  format = "dydx-inPlane-%s-tcs.%s";
  Print(c2,format,label,"eps",epsOK); 
  Print(c2,format,label,"png",pngOK); 
  Print(c2,format,label,"pdf",pdfOK); 
  
  c3->cd(); 
  hdydx3->Draw("colz"); 
  gPad->Update(); 
 
  mypalette = (TPaletteAxis*)hdydx3->GetListOfFunctions()->FindObject("palette"); 
 
  mypalette->SetX1NDC(0.910); 
  mypalette->SetX2NDC(0.935); 
  mypalette->SetLabelFont(52); 
  mypalette->SetLabelSize(0.028); 
   
  hdydx3->SetStats(0); 
 
  hdydx3->GetXaxis()->SetTitle("#Deltax - Distance between clusters (cm)"); 
  hdydx3->GetYaxis()->SetTitle("#Deltay - Distance between clusters (cm)"); 
 
  hdydx3->GetYaxis()->SetTitleOffset(1.1); 
  hdydx3->Draw("colz");   

  format = "dydx-inAccept-%s-tcs.%s";
  Print(c3,format,label,"eps",epsOK); 
  Print(c3,format,label,"png",pngOK); 
  Print(c3,format,label,"pdf",pdfOK); 
 
  c4->cd(); 
  hdydx4->Draw("colz"); 
  gPad->Update(); 
 
  mypalette = (TPaletteAxis*)hdydx4->GetListOfFunctions()->FindObject("palette"); 
 
  mypalette->SetX1NDC(0.910); 
  mypalette->SetX2NDC(0.935); 
  mypalette->SetLabelFont(52); 
  mypalette->SetLabelSize(0.028); 
   
  hdydx4->SetStats(0); 
 
  hdydx4->GetXaxis()->SetTitle("#Deltax - Distance between clusters (cm)"); 
  hdydx4->GetYaxis()->SetTitle("#Deltay - Distance between clusters (cm)"); 
 
  hdydx4->GetYaxis()->SetTitleOffset(1.1); 
  hdydx4->Draw("colz");   

  format = "dydx-inRmin-%s-tcs.%s";
  Print(c4,format,label,"eps",epsOK); 
  Print(c4,format,label,"png",pngOK); 
  Print(c4,format,label,"pdf",pdfOK); 
 
  c6->cd(); 
  hdydx6->Draw("colz"); 
  gPad->Update(); 
 
  mypalette = (TPaletteAxis*)hdydx6->GetListOfFunctions()->FindObject("palette"); 
 
  mypalette->SetX1NDC(0.910); 
  mypalette->SetX2NDC(0.935); 
  mypalette->SetLabelFont(52); 
  mypalette->SetLabelSize(0.028); 
   
  hdydx6->SetStats(0); 
 
  hdydx6->GetXaxis()->SetTitle("#Deltax - Distance between clusters (cm)"); 
  hdydx6->GetYaxis()->SetTitle("#Deltay - Distance between clusters (cm)"); 
 
  hdydx6->GetYaxis()->SetTitleOffset(1.1); 
  hdydx6->Draw("colz");  

  format = "dydx-inTarget-%s-tcs.%s";
  Print(c6,format,label,"eps",epsOK);    
  Print(c6,format,label,"png",pngOK);    
  Print(c6,format,label,"pdf",pdfOK);    
 
  c7->cd(); 
  hdydx7->Draw("colz"); 
  gPad->Update(); 
 
  mypalette = (TPaletteAxis*)hdydx7->GetListOfFunctions()->FindObject("palette"); 
 
  mypalette->SetX1NDC(0.910); 
  mypalette->SetX2NDC(0.935); 
  mypalette->SetLabelFont(52); 
  mypalette->SetLabelSize(0.028); 
   
  hdydx7->SetStats(0); 
 
  hdydx7->GetXaxis()->SetTitle("#Deltax - Distance between clusters (cm)"); 
  hdydx7->GetYaxis()->SetTitle("#Deltay - Distance between clusters (cm)"); 
 
  hdydx7->GetYaxis()->SetTitleOffset(1.1); 
  hdydx7->Draw("colz");   

  format = "dydx-inEnergy-%s-tcs.%s";
  Print(c7,format,label,"eps",epsOK);     
  Print(c7,format,label,"png",pngOK);     
  Print(c7,format,label,"pdf",pdfOK);
  
  c8->cd();   
  hdydx8->SetMinimum(3);  
  hdydx8->SetMaximum(200);  
  hdydx8->Draw("col"); 
  gPad->Update();  
  
//   mypalette = (TPaletteAxis*)hdydx8->GetListOfFunctions()->FindObject("palette");  
  
//   mypalette->SetX1NDC(0.910);  
//   mypalette->SetX2NDC(0.935);  
//   mypalette->SetLabelFont(52);  
//   mypalette->SetLabelSize(0.028);  
    
  hdydx8->SetStats(0);  
  
  hdydx8->GetXaxis()->SetTitle("#Deltax - Distance between clusters (cm)");  
  hdydx8->GetYaxis()->SetTitle("#Deltay - Distance between clusters (cm)");  
  
  hdydx8->GetYaxis()->SetTitleOffset(1.1);  
  hdydx8->Draw("col");   
 
  TEllipse *circ = new TEllipse(0.0, 0.0, 18.0, 18.0); 
  circ->SetLineColor(0); 
  circ->SetLineWidth(2); 
  circ->SetFillStyle(0); 
  circ->Draw();   
 
  TLine *line1 = new TLine(18.0, -40.0, -18.0, 40.0); 
  //~ line1->SetLineColor(0); 
  //~ line1->SetLineWidth(2); 
  //~ line1->Draw();   
  //~ 
  //~ TLine *line2 = new TLine(-18.0, -40.0, 18.0, 40.0); 
  //~ line2->SetLineColor(0); 
  //~ line2->SetLineWidth(2); 
  //~ line2->Draw(); 
 
  TText *ctext1 = new TText(-38.0, -32.0, "Compton"); 
  ctext1->SetTextSize(0.04);
  ctext1->Draw(); 
  ctext1 = new TText(-36.0, -35.0, "Events"); 
  ctext1->SetTextSize(0.04);
  ctext1->Draw(); 
     
  //~ ctext1 = new TText(26.0, 35.0, "Pair"); 
  //~ ctext1->SetTextSize(0.04);
  //~ ctext1->Draw(); 
  //~ ctext1 = new TText(20.0, 32.0, "Production"); 
  //~ ctext1->SetTextSize(0.04);
  //~ ctext1->Draw(); 
  //~ ctext1 = new TText(24.0, 29.0, "Events"); 
  //~ ctext1->SetTextSize(0.04);
  //~ ctext1->Draw(); 
  
  TArrow *carrow1 = new TArrow(-30.0, -28.0, -20.0, -10.0, 0.015, "|>"); 
  carrow1->SetFillColor(1); 
  carrow1->SetLineWidth(3); 
  carrow1->Draw(); 
 
  carrow1 = new TArrow(-30.0, -28.0, 20.0, 0.0, 0.015, "|>"); 
  carrow1->SetFillColor(1); 
  carrow1->SetLineWidth(3); 
  carrow1->Draw(); 
 
  //~ carrow1 = new TArrow(22.0, 25.0, 2.0, -15.0, 0.015, "|>"); 
  //~ carrow1->SetFillColor(1); 
  //~ carrow1->SetLineWidth(3); 
  //~ carrow1->Draw(); 
  //~ 
  //~ carrow1 = new TArrow(22.0, 25.0, 5.0, 22.0, 0.015, "|>"); 
  //~ carrow1->SetFillColor(1); 
  //~ carrow1->SetLineWidth(3); 
  //~ carrow1->Draw();    

  format = "dydx-evSelection-%s-tcs.%s";
  Print(c8,format,label,"eps",epsOK);     
  Print(c8,format,label,"png",pngOK);     
  Print(c8,format,label,"pdf",pdfOK);  
 
  c0->cd(); 
  hdydx0->Draw("colz"); 
  gPad->Update(); 
 
  mypalette = (TPaletteAxis*)hdydx0->GetListOfFunctions()->FindObject("palette"); 
 
  mypalette->SetX1NDC(0.910); 
  mypalette->SetX2NDC(0.935); 
  mypalette->SetLabelFont(52); 
  mypalette->SetLabelSize(0.028); 
   
  hdydx0->SetStats(0); 
 
  hdydx0->GetXaxis()->SetTitle("#Deltax - Distance between clusters (cm)"); 
  hdydx0->GetYaxis()->SetTitle("#Deltay - Distance between clusters (cm)"); 
 
  hdydx0->GetYaxis()->SetTitleOffset(1.1); 
  hdydx0->Draw("colz"); 

  format = "dydx-noCuts-%s-tcs.%s";
  Print(c0,format,label,"eps",epsOK);  
  Print(c0,format,label,"png",pngOK);  
  Print(c0,format,label,"pdf",pdfOK);  

  gStyle->SetLabelSize(0.03,"XY");    
 
  c9->cd(); 
  hdEdZ0->Draw("colz"); 
  gPad->Update(); 
 
  mypalette = (TPaletteAxis*)hdEdZ0->GetListOfFunctions()->FindObject("palette"); 
 
  mypalette->SetX1NDC(0.910); 
  mypalette->SetX2NDC(0.935); 
  mypalette->SetLabelFont(52); 
  mypalette->SetLabelSize(0.028); 
   
  hdEdZ0->SetStats(0); 
 
  hdEdZ0->GetXaxis()->SetTitle("Z - Distance to Target (opening angle based)  (cm)"); 
  hdEdZ0->GetYaxis()->SetTitle("#DeltaE = E_{0} - E_{cal} - Energy Difference  (GeV)"); 
 
  hdEdZ0->GetYaxis()->SetTitleOffset(1.1); 
  hdEdZ0->Draw("colz");   

  line1 = new TLine(500.0, 1.0, 950.0, 1.0); 
  line1->SetLineColor(1); 
  line1->SetLineWidth(3); 
  line1->Draw();   

  line1 = new TLine(500.0, -1.0, 950.0, -1.0); 
  line1->SetLineColor(1); 
  line1->SetLineWidth(3); 
  line1->Draw();   

  line1 = new TLine(zTgt-zcut, -3.0, zTgt-zcut, 3.0); 
  line1->SetLineColor(1); 
  line1->SetLineWidth(3); 
  line1->Draw();   

  line1 = new TLine(zTgt+zcut, -3.0, zTgt+zcut, 3.0); 
  line1->SetLineColor(1); 
  line1->SetLineWidth(3); 
  line1->Draw();
  
  format = "dEdZ-cuts-%s-tcs.%s";
  Print(c9,format,label,"eps",epsOK);     
  Print(c9,format,label,"png",pngOK);     
  Print(c9,format,label,"pdf",pdfOK);      
     
  c01->cd(); 
  gPad->SetLeftMargin(0.135);
  helaz0->Draw("colz"); 
  gPad->Update(); 
 
  mypalette = (TPaletteAxis*)helaz0->GetListOfFunctions()->FindObject("palette"); 
 
  mypalette->SetX1NDC(0.910); 
  mypalette->SetX2NDC(0.935); 
  mypalette->SetLabelFont(52); 
  mypalette->SetLabelSize(0.028); 
   
  helaz0->SetStats(0); 
 
  helaz0->GetXaxis()->SetTitle("Elasticity: E_{0} - (E_{1} + E_{2}) (GeV)"); 
  helaz0->GetYaxis()->SetTitle("Z - Distance to Target (opening angle based)  (cm)"); 
  
  helaz0->SetMaximum(100); 
  helaz0->GetYaxis()->SetTitleOffset(1.55); 
  helaz0->Draw("colz");   

  line1 = new TLine(-1.0, zTgt-zcut,  2.0, zTgt-zcut); 
  line1->SetLineColor(1); 
  line1->SetLineWidth(2); 
  line1->Draw();   

  line1 = new TLine(-1.0, zTgt+zcut, 2.0, zTgt+zcut); 
  line1->SetLineColor(1); 
  line1->SetLineWidth(2); 
  line1->Draw();   
  
  format = "elast-z-%s-tcs.%s";
  Print(c01,format,label,"eps",epsOK);     
  Print(c01,format,label,"png",pngOK);     
  Print(c01,format,label,"pdf",pdfOK);   
  
  c02->cd(); 
  gPad->SetLeftMargin(0.135);
  hy1x1->Draw("colz"); 
  gPad->Update(); 
 
  mypalette = (TPaletteAxis*)hy1x1->GetListOfFunctions()->FindObject("palette"); 
 
  mypalette->SetX1NDC(0.910); 
  mypalette->SetX2NDC(0.935); 
  mypalette->SetLabelFont(52); 
  mypalette->SetLabelSize(0.028); 
   
  hy1x1->SetStats(0); 
 
  hy1x1->GetXaxis()->SetTitle("x Position - High E Cluster (cm)"); 
  hy1x1->GetYaxis()->SetTitle("y Position - High E Cluster (cm)"); 
  
  hy1x1->SetMaximum(100); 
  hy1x1->GetYaxis()->SetTitleOffset(1.55); 
  hy1x1->Draw("colz");   

  format = "y1x1-%s-tcs.%s";
  Print(c02,format,label,"eps",epsOK);     
  Print(c02,format,label,"png",pngOK);     
  Print(c02,format,label,"pdf",pdfOK=true);   
   
  
  c03->cd(); 
  gPad->SetLeftMargin(0.135);
  hy2x2->Draw("colz"); 
  gPad->Update(); 
 
  mypalette = (TPaletteAxis*)hy2x2->GetListOfFunctions()->FindObject("palette"); 
 
  mypalette->SetX1NDC(0.910); 
  mypalette->SetX2NDC(0.935); 
  mypalette->SetLabelFont(52); 
  mypalette->SetLabelSize(0.028); 
   
  hy2x2->SetStats(0); 
 
  hy2x2->GetXaxis()->SetTitle("x Position - Low E Cluster  (cm)"); 
  hy2x2->GetYaxis()->SetTitle("y Position - Low E Cluster 2 (cm)"); 
  
  hy2x2->SetMaximum(100); 
  hy2x2->GetYaxis()->SetTitleOffset(1.55); 
  hy2x2->Draw("colz");   

  format = "y2x2-%s-tcs.%s";
  Print(c03,format,label,"eps",epsOK);     
  Print(c03,format,label,"png",pngOK);     
  Print(c03,format,label,"pdf",pdfOK=true);   
  
  c10->cd();
  gPad->SetLeftMargin(0.090);
  gPad->SetRightMargin(0.065);   
  gPad->SetTopMargin(0.075);   
  gPad->SetBottomMargin(0.125);   
  gPad->SetBorderMode(0); 
  gStyle->SetLineWidth(0.5);
  helas0->SetStats(0);
  helas0->SetFillColor(kGreen+4);
  helas1->SetFillColor(kGreen+3);
  helas2->SetFillColor(kGreen+2);
  helas3->SetFillColor(kGreen+1);
  helas4->SetFillColor(kGreen);
  helas5->SetFillColor(kGreen-6);
  helas6->SetFillColor(kGreen-8);
  helas7->SetFillColor(kGreen-10);
  helas7->SetTitleSize(0.035,"X");
  helas7->GetXaxis()->SetTitle("Elasticity: E_{0} - (E_{1} + E_{2}) (GeV)");
  helass->Draw("nostack");

  latex.DrawLatex(0.465,0.035,"Elasticity: E_{0} - (E_{1} + E_{2})  (GeV)");  
	cout << "\n===>>> IN TIME: " << intime << "\n" << endl;
  TLegend *legend;
  if (intime) legend = new TLegend(0.650,0.650,0.920,0.915);
  if (!intime) legend = new TLegend(0.110,0.650,0.390,0.915);
  legend->SetTextFont(52);
  legend->AddEntry(helas0,"All Events","f");
  legend->AddEntry(helas1,"Coincidence","f");
  legend->AddEntry(helas2,"+ Coplanarity","f");
  legend->AddEntry(helas3,"+ Fiducial","f");
  legend->AddEntry(helas4,"+ R minimum","f");
  //~ legend->AddEntry(helas5,"+ no Pair Bgrd","f");
  legend->AddEntry(helas6,"+ z Target","f");
  legend->AddEntry(helas7,"+ Energy Diff.","f");
  legend->Draw();

  format = "elast-cut-progress-%s-tcs.%s"; 
  Print(c10,format,label,"eps",epsOK);
  Print(c10,format,label,"png",pngOK);
  Print(c10,format,label,"pdf",pdfOK);

  c11->cd();
  gPad->SetLeftMargin(0.090);
  gPad->SetRightMargin(0.05);   
  gPad->SetTopMargin(0.075);   
  gPad->SetBottomMargin(0.125);   
  gPad->SetBorderMode(0);  
  hopnz0->SetStats(0);
  hopnz0->SetFillColor(kGreen+4);
  hopnz1->SetFillColor(kGreen+3);
  hopnz2->SetFillColor(kGreen+2);
  hopnz3->SetFillColor(kGreen+1);
  hopnz4->SetFillColor(kGreen);
  hopnz5->SetFillColor(kGreen-6);
  hopnz6->SetFillColor(kGreen-8);
  hopnz7->SetFillColor(kGreen-10);
  hopnz7->SetTitleSize(0.035,"X");
  hopnz7->GetXaxis()->SetTitle("z - Distance To Target (cm)");
  hopnzs->Draw("nostack");

  latex.DrawLatex(0.155,0.035,"Z - Distance to Target (opening angle based)  (cm)");  

  legend = new TLegend(0.110,0.650,0.390,0.915);
  legend->SetTextFont(52);
  legend->AddEntry(hopnz0,"All Events","f");
  legend->AddEntry(hopnz1,"Coincidence","f");
  legend->AddEntry(hopnz2,"+ Coplanarity","f");
  legend->AddEntry(hopnz3,"+ Fiducial","f");
  legend->AddEntry(hopnz4,"+ R minimum","f");
  //~ legend->AddEntry(hopnz5,"+ no Pair Bgrd","f");
  legend->AddEntry(hopnz6,"+ z Target","f");
  legend->AddEntry(hopnz7,"+ Energy Diff.","f");
  legend->Draw();

  format = "zTgt-cut-progress-%s-tcs.%s"; 
  Print(c11,format,label,"eps",epsOK);
  Print(c11,format,label,"png",pngOK);
  Print(c11,format,label,"pdf",pdfOK);

  c12->cd();
  gPad->SetLeftMargin(0.090);
  gPad->SetRightMargin(0.065);   
  gPad->SetTopMargin(0.075);   
  gPad->SetBottomMargin(0.125);   
  gPad->SetBorderMode(0);  
  hrmin0->SetStats(0);
  hrmin0->SetFillColor(kGreen+4);
  hrmin1->SetFillColor(kGreen+3);
  hrmin2->SetFillColor(kGreen+2);
  hrmin3->SetFillColor(kGreen+1);
  hrmin4->SetFillColor(kGreen);
  hrmin5->SetFillColor(kGreen-6);
  hrmin6->SetFillColor(kGreen-8);
  hrmin7->SetFillColor(kGreen-10);
  hrmin7->SetTitleSize(0.055,"X");
  hrmin7->GetXaxis()->SetTitle("R - Separation between Clusters  (cm)");
  hrmins->Draw("nostack");

  latex.DrawLatex(0.325,0.035,"R - Separation between Clusters  (cm)");  

  legend = new TLegend(0.650,0.650,0.920,0.915);
  legend->SetTextFont(52);
  legend->AddEntry(hrmin0,"All Events","f");
  legend->AddEntry(hrmin1,"Coincidence","f");
  legend->AddEntry(hrmin2,"+ Coplanarity","f");
  legend->AddEntry(hrmin3,"+ Fiducial","f");
  legend->AddEntry(hrmin4,"+ R minimum","f");
  //~ legend->AddEntry(hrmin5,"+ no Pair Bgrd","f");
  legend->AddEntry(hrmin6,"+ z Target","f");
  legend->AddEntry(hrmin7,"+ Energy Diff.","f");
  legend->Draw();

  format = "csep-cut-progress-%s-tcs.%s"; 
  Print(c12,format,label,"eps",epsOK);
  Print(c12,format,label,"png",pngOK);
  Print(c12,format,label,"pdf",pdfOK);

  c14->cd();
  gPad->SetLeftMargin(0.090);
  gPad->SetRightMargin(0.065);   
  gPad->SetTopMargin(0.075);   
  gPad->SetBottomMargin(0.125);   
  gPad->SetBorderMode(0);  
  hdele0->SetStats(0);
  hdele0->SetFillColor(kGreen+4);
  hdele1->SetFillColor(kGreen+3);
  hdele2->SetFillColor(kGreen+2);
  hdele3->SetFillColor(kGreen+1);
  hdele4->SetFillColor(kGreen);
  hdele5->SetFillColor(kGreen-6);
  hdele6->SetFillColor(kGreen-8);
  hdele7->SetFillColor(kGreen-10);
  hdele7->SetTitleSize(0.055,"X");
  hdele7->GetXaxis()->SetTitle("");
  hdeles->Draw("nostack");

  latex.DrawLatex(0.300,0.035,"#DeltaE = E_{0} - E_{cal} - Energy Difference  (GeV)");  

  if (intime) legend = new TLegend(0.650,0.650,0.920,0.915);
  if (!intime) legend = new TLegend(0.110,0.650,0.390,0.915);
  legend->SetTextFont(52);
  legend->AddEntry(hdele0,"All Events","f");
  legend->AddEntry(hdele1,"Coincidence","f");
  legend->AddEntry(hdele2,"+ Coplanarity","f");
  legend->AddEntry(hdele3,"+ Fiducial","f");
  legend->AddEntry(hdele4,"+ R minimum","f");
  //~ legend->AddEntry(hdele5,"+ no Pair Bgrd","f");
  legend->AddEntry(hdele6,"+ z Target","f");
  legend->AddEntry(hdele7,"+ Energy Diff.","f");
  legend->Draw();

  format = "delE-cut-progress-%s-tcs.%s"; 
  Print(c14,format,label,"eps",epsOK);
  Print(c14,format,label,"png",pngOK);
  Print(c14,format,label,"pdf",pdfOK);

  c15->cd();
  gPad->SetLeftMargin(0.090);
  gPad->SetRightMargin(0.065);   
  gPad->SetTopMargin(0.075);   
  gPad->SetBottomMargin(0.125);   
  gPad->SetBorderMode(0);  
  hcopl0->SetStats(0);
  hcopl0->SetFillColor(kGreen+4);
  hcopl1->SetFillColor(kGreen+3);
  hcopl2->SetFillColor(kGreen+2);
  hcopl3->SetFillColor(kGreen+1);
  hcopl4->SetFillColor(kGreen);
  hcopl5->SetFillColor(kGreen-6);
  hcopl6->SetFillColor(kGreen-8);
  hcopl7->SetFillColor(kGreen-10);
  hcopl7->SetTitleSize(0.055,"X");
  hcopl7->GetXaxis()->SetTitle("");
  hcopls->Draw("nostack");

  latex.DrawLatex(0.215,0.035,"#Delta#phi = #phi_{e^{-}} - #phi_{#gamma} - Azimuthal Angle Difference (deg)");  

  legend = new TLegend(0.650,0.650,0.920,0.915);
  legend->SetTextFont(52);
  legend->AddEntry(hcopl0,"All Events","f");
  legend->AddEntry(hcopl1,"Coincidence","f");
  legend->AddEntry(hcopl2,"+ Coplanarity","f");
  legend->AddEntry(hcopl3,"+ Fiducial","f");
  legend->AddEntry(hcopl4,"+ R minimum","f");
  //~ legend->AddEntry(hcopl5,"+ no Pair Bgrd","f");
  legend->AddEntry(hcopl6,"+ z Target","f");
  legend->AddEntry(hcopl7,"+ Energy Diff.","f");
  legend->Draw();  

  format = "inplane-cut-progress-%s-tcs.%s"; 
  Print(c15,format,label,"eps",epsOK);
  Print(c15,format,label,"png",pngOK);
  Print(c15,format,label,"pdf",pdfOK);

  c16->cd();
  gPad->SetLeftMargin(0.090);
  gPad->SetRightMargin(0.065);   
  gPad->SetTopMargin(0.075);   
  gPad->SetBottomMargin(0.125);   
  gPad->SetBorderMode(0);    

  hopnz8->SetStats(0);
  hopnz8->SetFillColor(5);
  hopnz8->SetLineColor(4);
  hopnz8->SetLineWidth(1);
  hopnz8->SetLabelSize(0.0275,"XY");
  hopnz8->SetLabelOffset(0.0075,"X");
  hopnz8->SetTitleSize(0.045,"X");
  hopnz8->SetTitleOffset(1.15);
  hopnz8->GetXaxis()->SetTitle( "z - Distance To Target (cm)" ); 
  hopnz8->Draw();  

  y1 = 4000.0; 
  y2 = 25.0;

  if (!intime) {
     y1 = 120.0; 
     y2 = 5.0;
  }
  carrow1 = new TArrow(zTgt-zcut, y1, zTgt-zcut, y2, 0.015, "|>"); 
  carrow1->SetFillColor(1); 
  carrow1->SetLineWidth(3); 
  carrow1->Draw();

  y1 = 4000.0;
  y2 = 25.0;

  if (!intime) {
     y1 = 120.0; 
     y2 = 5.0;
  }
  carrow1 = new TArrow(zTgt+zcut, y1, zTgt+zcut, y2, 0.015, "|>"); 
  carrow1->SetFillColor(1); 
  carrow1->SetLineWidth(3); 
  carrow1->Draw();  
 
  latex.DrawLatex(0.125,0.35,"Cut Width: 4#sigma");  

  format = "z-cut-width-%s-tcs.%s"; 
  Print(c16,format,label,"eps",epsOK);
  Print(c16,format,label,"png",pngOK);
  Print(c16,format,label,"pdf",pdfOK);

  c17->cd();
  gPad->SetLeftMargin(0.090);
  gPad->SetRightMargin(0.065);   
  gPad->SetTopMargin(0.1);   
  gPad->SetBottomMargin(0.125);   
  gPad->SetBorderMode(0);    

  hdele8->SetStats(0);
  hdele8->SetFillColor(5);
  hdele8->SetLineColor(4);
  hdele8->SetLineWidth(1);
  hdele8->SetLabelSize(0.0275,"XY");
  hdele8->SetLabelOffset(0.0075,"X");
  hdele8->SetTitleSize(0.045,"X");
  hdele8->SetTitleOffset(1.15);
  hdele8->GetXaxis()->SetTitle( "#DeltaE = E_{0} - E_{cal} - Energy Difference  (GeV)" ); 
  hdele8->Draw();  

  x1 = -1.0; 
  y1 = 3000.0; 
  x2 = -1.0; 
  y2 = 25.0;

  if (!intime) {
     y1 = 120.0; 
     y2 = 5.0;
  }
  carrow1 = new TArrow(x1, y1, x2, y2, 0.015, "|>"); 
  carrow1->SetFillColor(1); 
  carrow1->SetLineWidth(3); 
  carrow1->Draw(); 

  x1 = 1.0; 
  y1 = 3000.0; 
  x2 = 1.0; 
  y2 = 25.0;

  if (!intime) {
     y1 = 120.0; 
     y2 = 5.0;
  }
  carrow1 = new TArrow(x1, y1, x2, y2, 0.015, "|>"); 
  carrow1->SetFillColor(1); 
  carrow1->SetLineWidth(3); 
  carrow1->Draw();   

  latex.DrawLatex(0.125,0.35,"Cut Width: 3#sigma");  

  format = "de-cut-width-%s-tcs.%s"; 
  Print(c17,format,label,"eps",epsOK);
  Print(c17,format,label,"png",pngOK);
  Print(c17,format,label,"pdf",pdfOK);

  c18->cd();
  gPad->SetLeftMargin(0.090);
  gPad->SetRightMargin(0.065);   
  gPad->SetTopMargin(0.1);   
  gPad->SetBottomMargin(0.125);   
  gPad->SetBorderMode(0);    

  htdiff0->SetStats(0);
  htdiff0->SetFillColor(5);
  htdiff0->SetLineColor(4);
  htdiff0->SetLineWidth(1);
  htdiff0->SetLabelSize(0.0275,"XY");
  htdiff0->SetLabelOffset(0.0075,"X");
  htdiff0->SetTitleSize(0.045,"X");
  htdiff0->SetTitleOffset(1.15);
  htdiff0->GetXaxis()->SetTitle( "Coincidence Time (ns)" ); 
  htdiff0->Draw(); 

  y1 = 80000.0; 
  y2 = 25.0;

  if (!intime) {
     y1 = 600.0; 
     y2 = 5.0;
  }
  carrow1 = new TArrow(tdiff0-tcut, y1, tdiff0-tcut, y2, 0.015, "|>"); 
  carrow1->SetFillColor(1); 
  carrow1->SetLineWidth(3); 
  carrow1->Draw();

  y1 = 80000.0; 
  y2 = 25.0;

  if (!intime) {
     y1 = 600.0; 
     y2 = 5.0;
  }
  carrow1 = new TArrow(tdiff0+tcut, y1, tdiff0+tcut, y2, 0.015, "|>"); 
  carrow1->SetFillColor(1); 
  carrow1->SetLineWidth(3); 
  carrow1->Draw();      

  latex.DrawLatex(0.125,0.35,"Cut Width: 5#sigma");  

  format = "dt-cut-width-%s-tcs.%s"; 
  Print(c18,format,label,"eps",epsOK);
  Print(c18,format,label,"png",pngOK);
  Print(c18,format,label,"pdf",pdfOK);

  c19->cd();
  gPad->SetLeftMargin(0.090);
  gPad->SetRightMargin(0.065);   
  gPad->SetTopMargin(0.1);   
  gPad->SetBottomMargin(0.125);   
  gPad->SetBorderMode(0);    

  hcopl1->SetStats(0);
  hcopl1->SetFillColor(5);
  hcopl1->SetLineColor(4);
  hcopl1->SetLineWidth(1);
  hcopl1->SetLabelSize(0.0275,"XY");
  hcopl1->SetLabelOffset(0.0075,"X");
  hcopl1->SetTitleSize(0.045,"X");
  hcopl1->SetTitleOffset(1.15);
  hcopl1->GetXaxis()->SetTitle( "#Delta#phi = #phi_{e^{-}} - #phi_{#gamma} - Azimuthal Angle Difference (deg)" ); 
  hcopl1->Draw();
  
  y1 = 10000.0; 
  y2 = 25.0;

  if (!intime) {
     y1 = 800.0; 
     y2 = 5.0;
  }
  carrow1 = new TArrow(phi0-phicut, y1, phi0-phicut, y2, 0.015, "|>"); 
  carrow1->SetFillColor(1); 
  carrow1->SetLineWidth(3); 
  carrow1->Draw();

  y1 = 10000.0; 
  y2 = 25.0;

  if (!intime) {
     y1 = 800.0; 
     y2 = 5.0;
  }
  carrow1 = new TArrow(phi0+phicut, y1, phi0+phicut, y2, 0.015, "|>"); 
  carrow1->SetFillColor(1); 
  carrow1->SetLineWidth(3); 
  carrow1->Draw();      

  latex.DrawLatex(0.125,0.35,"Cut Width: 6#sigma");  

  format = "dphi-cut-width-%s-tcs.%s"; 
  Print(c19,format,label,"eps",epsOK);
  Print(c19,format,label,"png",pngOK);
  Print(c19,format,label,"pdf",pdfOK);

  c20->cd();
  gPad->SetLeftMargin(0.090);
  gPad->SetRightMargin(0.065);   
  gPad->SetTopMargin(0.1);   
  gPad->SetBottomMargin(0.125);   
  gPad->SetBorderMode(0);    

  hrmin8->SetStats(0);
  hrmin8->SetFillColor(5);
  hrmin8->SetLineColor(4);
  hrmin8->SetLineWidth(1);
  hrmin8->SetLabelSize(0.0275,"XY");
  hrmin8->SetLabelOffset(0.0075,"X");
  hrmin8->SetTitleSize(0.045,"X");
  hrmin8->SetTitleOffset(1.15);
  hrmin8->GetXaxis()->SetTitle( "R - Separation between Clusters  (cm)" ); 
  hrmin8->Draw();

  y1 = 5000.0; 
  y2 = 25.0;

  if (!intime) {
     y1 = 200.0; 
     y2 = 5.0;
  }
  carrow1 = new TArrow(minSep, y1, minSep, y2, 0.015, "|>"); 
  carrow1->SetFillColor(1); 
  carrow1->SetLineWidth(3); 
  carrow1->Draw();

  latex.DrawLatex(0.125,0.35,"R_{min} = 16 cm");  

  format = "rmin-cut-width-%s-tcs.%s"; 
  Print(c20,format,label,"eps",epsOK);
  Print(c20,format,label,"png",pngOK);
  Print(c20,format,label,"pdf",pdfOK);

  c21->cd();
  gPad->SetLeftMargin(0.075);
  gPad->SetRightMargin(0.05);   
  gPad->SetTopMargin(0.125);  
  gPad->SetBorderMode(0);     
 
  latex.SetTextSize(0.10); 

  TF1 *dgauss = new TF1( "dgauss", "gaus(0) + gaus(3)", -5., 10.);  
  dgauss->SetParNames("C_{0}","T_{0}","#sigma_{0}","C_{tail}","T_{tail}","#sigma_{tail}");
  Double_t height, centroid; 
  Double_t E0 = 0.0; 
  Int_t  maxBin;
  TF1 *fit;

  format = "elast-%s-tcs.%s"; 
  const char *fitFormat = "E_{0} = %2.1f MeV"; 
  const char *fileName1 = "elast-fits-%s.dat"; 
  char fitLabel[32];
  char outFile1[32];

  sprintf(outFile1,fileName1,label.c_str());  
  outs1.open( outFile1 );
  if (outs1.fail())
    cerr << "*****ERROR: cannot use "<<outFile1<<" for output!!*****" << endl;

  Int_t itchan = 1;
  TIter htidf = htids->GetHists();
  while (TH1F *hist = (TH1F*)htidf.Next()) {
    c21->cd(itchan);
    gPad->SetBorderMode(0);
    gPad->SetFrameFillColor(255);   
    gPad->SetBottomMargin(0.175); 
    height = hist->GetMaximum();
    maxBin = hist->GetMaximumBin();
    centroid = hist->GetBinCenter(maxBin);
    dgauss->SetParameters( 0.9*height, centroid, 0.15, 0.1*height, centroid+0.25, 0.25);
    //dgauss->SetParameters( height, centroid-0.025, 0.15, 0.1*height, centroid+0.25, 0.25);
    if (hist->GetSum() > 0) {
      hist->Fit("dgauss");
      fit = hist->GetFunction("dgauss");
      fit->SetLineWidth(1.5);
      E0 = fit->GetParameter(1);
    }
    sprintf(fitLabel,fitFormat,E0*1000.); 

    outs1 << "   " <<  E0 << endl;

    hist->SetStats(0);
    hist->SetFillColor(5);
    hist->SetLineColor(4);
    hist->SetLineWidth(1);
    hist->SetLabelSize(0.0375,"XY");
    hist->SetLabelOffset(0.0075,"X");
    hist->SetTitleSize(0.075,"X");
    hist->SetTitleOffset(1.15);
    hist->GetXaxis()->SetTitle( "Elasticity: E_{0} - (E_{1} + E_{2}) (GeV)" ); 
    hist->Draw();
    latex.DrawLatex(0.400,0.735,fitLabel);

    itchan++;
  }
  
  c21->cd(12);
  gPad->SetBorderMode(0);

  Print(c21,format,label,"eps",epsOK);
  Print(c21,format,label,"png",pngOK); 
  Print(c21,format,label,"pdf",pdfOK);

  outs1.close();

  const char *fileName2 = "elast-noent-%s.dat"; 
  char outFile2[32];

  sprintf(outFile2,fileName2,label.c_str());  
  outs2.open( outFile2 );
  if (outs2.fail())
    cerr << "*****ERROR: cannot use "<<outFile2<<" for output!!*****" << endl;  

  Double_t norm0 = helas0->GetSum();
  Double_t norm = helas0->GetSum();
  cout << norm << endl;
  TIter helasn = helass->GetHists();
  while (TH1F *hist = (TH1F*)helasn.Next()) { 
    Double_t nev = hist->GetSum();
    Double_t eff0 = nev/norm0;
    Double_t deff0 = eff0*sqrt(norm0/(nev*(nev+norm0)));
    Double_t eff = nev/norm;
    Double_t deff = eff*sqrt(norm/(nev*(nev+norm)));
    outs2 << "  " << eff0  << " " << deff0 << " " << eff  << " " << deff << endl;
    norm = nev;
    cout << norm << endl;
 }
  outs2.close();
}
