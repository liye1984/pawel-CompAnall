#define CompAnaII_cxx
#include "CompAnaII.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH1F.h>
#include <THStack.h>
#include <TObject.h>
#include <TF1.h>
#include <TColor.h>
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

void CompAnaII::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L CompAnaII.C
//      Root > CompAnaII t
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



  double delx, dely, rmin, rmin0 = 0.;
  double phi, phi0 = 180., dphi = 180.;
  
  const Int_t emode = 1;
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;

//	BLACK & WHITE Color scheme
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
  gStyle->SetLabelFont(52,"XY");
  gStyle->SetLabelSize(0.035,"XY");
  gStyle->SetTitleFont(42,"XY");
  
  TCanvas *c0 = new TCanvas("c0","Cluster Separation - All Events",798,35,600,600);  
  c0->SetFillColor(0);  
  c0->SetFrameFillColor(255);  
  c0->SetBorderMode(0); 
  
  TCanvas *c10 = new TCanvas("c10","Elasticity",0,35,600,600);  
  c10->SetFillColor(0);  
  c10->SetFrameFillColor(255);  
  c10->SetBorderMode(0);      
  
  TCanvas *c20 = new TCanvas("c20","Elasticity",30,35,600,600);  
  c20->SetFillColor(0);  
  c20->SetFrameFillColor(255);  
  c20->SetBorderMode(0); 

  TCanvas *c30 = new TCanvas("c30","Elasticity vs CTime",60,35,600,600);  
  c30->SetFillColor(0);  
  c30->SetFrameFillColor(255);  
  c30->SetBorderMode(0);  

  TCanvas *c40 = new TCanvas("c40","Opening Angle Target Position",90,35,600,600);  
  c40->SetFillColor(0);  
  c40->SetFrameFillColor(255);  
  c40->SetBorderMode(0);  
  
  TCanvas *c50 = new TCanvas("c50","Energy Difference",120,35,600,600);  
  c50->SetFillColor(0);  
  c50->SetFrameFillColor(255);  
  c50->SetBorderMode(0);    
  
  TCanvas *c60 = new TCanvas("c60","Energy Difference",150,35,600,600);  
  c60->SetFillColor(0);  
  c60->SetFrameFillColor(255);  
  c60->SetBorderMode(0);    

  TCanvas *c70 = new TCanvas("c70","Elasticity vs Energy Difference",180,35,600,600);  
  c70->SetFillColor(0);  
  c70->SetFrameFillColor(255);  
  c70->SetBorderMode(0);      

  TCanvas *c80 = new TCanvas("c80","Separation Distance",210,35,600,600);  
  c80->SetFillColor(0);  
  c80->SetFrameFillColor(255);  
  c80->SetBorderMode(0);           

  TH1F *helas0 = new TH1F("helas0","Elasticity:  E_{0} - (E_{1} + E_{2})",250,-1.0,4.0);
  TH1F *htdif0 = new TH1F("htdif0","Coincidence Time",300,-15,25);
  TH1F *hopnz0 = new TH1F("hopnz0","Distance To Target (Opening Angle Based)",400,0,1000);
  TH1F *hdele0 = new TH1F("hdele0","Energy Difference: E_{0} - E_{cal}",300,-2.,4.);
  TH1F *hcopl0 = new TH1F("hcopl0","Coplanarity: #phi_{e^{-}} - #phi_{#gamma}",280,120.,240.);
  TH1F *hrmin0 = new TH1F("hrmin0","Separation Distance",250,0,50);
  TH2F *hdydx0 = new TH2F("hdydx0","Separation Between Clusters: #Deltay VS. #Deltax - EXPERIMENT",320,-32,32,320,-32,32);
  TH2F *hdedt0 = new TH2F("hdedt0","Elasticity vs Coincidence Time",320,-15,25,300,-0.5,1.5);
  TH2F *heloz0 = new TH2F("heloz0","Elasticity vs Distance from Target",320,0,1000,300,-0.5,1.5);
  
  TH1F *helas1 = new TH1F("helas1","Elasticity:  E_{0} - (E_{1} + E_{2})",250,-1.0,4.0);
  TH1F *htdif1 = new TH1F("htdif1","Coincidence Time",300,-15,25);
  TH1F *hopnz1 = new TH1F("hopnz1","Distance To Target (Opening Angle Based)",400,0,1000);
  TH1F *hdele1 = new TH1F("hdele1","Energy Difference: E_{0} - E_{cal}",300,-2.,4.);
  TH1F *hcopl1 = new TH1F("hcopl1","Coplanarity: #phi_{e^{-}} - #phi_{#gamma}",280,120.,240.);
  TH1F *hrmin1 = new TH1F("hrmin1","Separation Distance",250,0,50);
  TH2F *hdydx1 = new TH2F("hdydx1","Separation Between Clusters: #Deltay VS. #Deltax - EXPERIMENT",320,-32,32,320,-32,32);
   

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
            
		double ev = jentry;
		for (int i=1; i<=5; i++)  { 
			ev = ev/10.;
			if (ev < 10) break; 
		}
		if (int(ev) == ev && ev != 0) {
			cout << "   " << jentry <<" events analyzed" << endl;
		} 
            
      if (tid < 40) {
      delx = x2 - x1;
      dely = y2 - y1;
	  rmin = sqrt(delx*delx+dely*dely);
	  phi = fabs(fabs((atan2(y2,x2)-atan2(y1,x1))*r2d));
      if (rmin > rmin0 && fabs(phi-180)< 20) hdedt0->Fill(tdiff,eg-(e1+e2));
      if (fabs(tdiff) < 5 && rmin > rmin0 && fabs(phi-phi0)< dphi) htdif0->Fill(tdiff);
      if (fabs(tdiff) < 5 && rmin > rmin0 && fabs(phi-phi0)< dphi) hopnz0->Fill(OpenZ(ientry));
      if (fabs(tdiff) < 5 && rmin > rmin0 && fabs(phi-phi0)< dphi) helas0->Fill(eg-(e1+e2));
      if (fabs(tdiff) < 5 && rmin > rmin0 && fabs(phi-phi0)< dphi) hcopl0->Fill(phi);
      if (fabs(tdiff) < 5 && rmin > rmin0 && fabs(phi-phi0)< dphi) hrmin0->Fill(rmin);
      if (fabs(tdiff) < 5 && rmin > rmin0 && fabs(phi-phi0)< dphi) hdydx0->Fill(x2-x1,y2-y1);
      if (fabs(tdiff) < 5 && rmin > rmin0 && fabs(phi-phi0)< dphi) hdele0->Fill(delE(ientry,emode));
      if (fabs(tdiff) < 5 && rmin > rmin0 && fabs(phi-phi0)< dphi) heloz0->Fill(OpenZ(ientry),eg-(e1+e2));
      
      if (fabs(tdiff) > 5 && rmin > rmin0 && fabs(phi-phi0)< dphi) htdif1->Fill(tdiff);
      if (fabs(tdiff) > 5 && rmin > rmin0 && fabs(phi-phi0)< dphi) hopnz1->Fill(OpenZ(ientry));
      if (fabs(tdiff) > 5 && rmin > rmin0 && fabs(phi-phi0)< dphi) helas1->Fill(eg-(e1+e2));
      if (fabs(tdiff) > 5 && rmin > rmin0 && fabs(phi-phi0)< dphi) hcopl1->Fill(phi);
      if (fabs(tdiff) > 5 && rmin > rmin0 && fabs(phi-phi0)< dphi) hrmin1->Fill(rmin);
      if (fabs(tdiff) > 5 && rmin > rmin0 && fabs(phi-phi0)< dphi) hdydx1->Fill(x2-x1,y2-y1);
      if (fabs(tdiff) > 5 && rmin > rmin0 && fabs(phi-phi0)< dphi) hdele1->Fill(delE(ientry,emode));
	  }
   }
   c0->cd(); 
  	hdydx0->Draw("colz");
  	gPad->Update();
  	
  	TPaletteAxis *mypalette = (TPaletteAxis*)hdydx0->GetListOfFunctions()->FindObject("palette");
  	mypalette->SetX1NDC(0.910); 
  	mypalette->SetX2NDC(0.935); 
  	mypalette->SetLabelFont(52); 
 	mypalette->SetLabelSize(0.028);
 	
  	hdydx0->GetXaxis()->SetTitle("#Deltax - Distance between clusters (cm)"); 
  	hdydx0->GetYaxis()->SetTitle("#Deltay - Distance between clusters (cm)"); 
 	hdydx0->GetYaxis()->SetTitleOffset(1.1); 
 	hdydx0->SetStats(0);
 	
   c30->cd();
  	hdedt0->SetStats(0);
	hdedt0->Draw("colz");
  	gPad->Update();
  	mypalette = (TPaletteAxis*)hdedt0->GetListOfFunctions()->FindObject("palette");
  	mypalette->SetX1NDC(0.910); 
  	mypalette->SetX2NDC(0.935); 
  	mypalette->SetLabelFont(52); 
 	mypalette->SetLabelSize(0.028);
 	/*
  	gPad->SetLeftMargin(0.090);
  	gPad->SetRightMargin(0.135);   
  	gPad->SetTopMargin(0.075);   
  	gPad->SetBottomMargin(0.125);   
  	gPad->SetBorderMode(0); 
  	gStyle->SetLineWidth(0.5);
  	*/
  	
   c70->cd();
  	heloz0->SetStats(0);
	heloz0->Draw("colz");
  	gPad->Update();
  	mypalette = (TPaletteAxis*)heloz0->GetListOfFunctions()->FindObject("palette");
  	mypalette->SetX1NDC(0.910); 
  	mypalette->SetX2NDC(0.935); 
  	mypalette->SetLabelFont(52); 
 	mypalette->SetLabelSize(0.028);
 	/*
  	gPad->SetLeftMargin(0.090);
  	gPad->SetRightMargin(0.135);   
  	gPad->SetTopMargin(0.075);   
  	gPad->SetBottomMargin(0.125);   
  	gPad->SetBorderMode(0); 
  	gStyle->SetLineWidth(0.5);
  	*/
  	
   c10->cd();
	helas0->Draw();
	helas1->Draw("same");
    
  	gPad->SetLeftMargin(0.090);
  	gPad->SetRightMargin(0.065);   
  	gPad->SetTopMargin(0.075);   
  	gPad->SetBottomMargin(0.125);   
  	gPad->SetBorderMode(0); 
  	gStyle->SetLineWidth(0.5);
  	helas0->SetStats(0);
	helas0->GetXaxis()->SetTitle("Elasticity: E_{0} - (E_{1} + E_{2}) (GeV)");
  	helas0->SetFillColor(kGreen-10);
  	helas1->SetFillColor(kGreen-8);
  	
   c20->cd();
  	gPad->SetLeftMargin(0.090);
  	gPad->SetRightMargin(0.065);   
  	gPad->SetTopMargin(0.075);   
  	gPad->SetBottomMargin(0.125);   
  	gPad->SetBorderMode(0); 
  	gStyle->SetLineWidth(0.5);
  	htdif0->SetStats(0);
  	htdif0->GetXaxis()->SetTitle("Coincidence Time (ns)");
  	htdif0->SetFillColor(kGreen-10);
  	htdif1->SetFillColor(kGreen-8);
	htdif0->Draw();
	htdif1->Draw("same");
  	
   c40->cd();
  	gPad->SetLeftMargin(0.090);
  	gPad->SetRightMargin(0.065);   
  	gPad->SetTopMargin(0.075);   
  	gPad->SetBottomMargin(0.125);   
  	gPad->SetBorderMode(0); 
  	gStyle->SetLineWidth(0.5);
  	hopnz0->SetStats(0);
  	hopnz0->GetXaxis()->SetTitle("z - Distance To Target (cm)");
  	hopnz0->SetFillColor(kGreen-10);
  	hopnz1->SetFillColor(kGreen-8);
	hopnz0->Draw();
	hopnz1->Draw("same");
  	
   c50->cd();
  	gPad->SetLeftMargin(0.090);
  	gPad->SetRightMargin(0.065);   
  	gPad->SetTopMargin(0.075);   
  	gPad->SetBottomMargin(0.125);   
  	gPad->SetBorderMode(0); 
  	gStyle->SetLineWidth(0.5);
  	hdele0->SetStats(0);
  	hdele0->GetXaxis()->SetTitle("#DeltaE = E_{0} - E_{cal} - Energy Difference  (GeV)");
  	hdele0->SetFillColor(kGreen-10);
  	hdele1->SetFillColor(kGreen-8);
	hdele0->Draw();
	hdele1->Draw("same");
  	
   c60->cd();
  	gPad->SetLeftMargin(0.090);
  	gPad->SetRightMargin(0.065);   
  	gPad->SetTopMargin(0.075);   
  	gPad->SetBottomMargin(0.125);   
  	gPad->SetBorderMode(0); 
  	gStyle->SetLineWidth(0.5);
  	hcopl0->SetStats(0);
  	hcopl0->GetXaxis()->SetTitle( "#Delta#phi = #phi_{e^{-}} - #phi_{#gamma} - Azimuthal Angle Difference (deg)" ); 
  	hcopl0->GetXaxis()->SetTitle("");
  	hcopl0->SetFillColor(kGreen-10);
  	hcopl1->SetFillColor(kGreen-8);
	hcopl0->Draw();
	hcopl1->Draw("same");
  	
   c80->cd();
  	gPad->SetLeftMargin(0.090);
  	gPad->SetRightMargin(0.065);   
  	gPad->SetTopMargin(0.075);   
  	gPad->SetBottomMargin(0.125);   
  	gPad->SetBorderMode(0); 
  	gStyle->SetLineWidth(0.5);
  	hrmin0->SetStats(0);
  	hrmin0->GetXaxis()->SetTitle( "#Delta#phi = #phi_{e^{-}} - #phi_{#gamma} - Azimuthal Angle Difference (deg)" ); 
  	hrmin0->GetXaxis()->SetTitle("");
  	hrmin0->SetFillColor(kGreen-10);
  	hrmin1->SetFillColor(kGreen-8);
	hrmin0->Draw();
	hrmin1->Draw("same");
}
