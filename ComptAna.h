//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Mar  9 09:57:09 2015 by ROOT version 5.34/18
// from TTree cmpt_ntuple/3 particles' phy info
// found on file: comptonII.root
//////////////////////////////////////////////////////////

#ifndef ComptAna_h
#define ComptAna_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TCanvas.h>
#include <iostream>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class ComptAna {
public :
  const double pi = 3.141592654;
  const double d2r = 3.141592654/180.;
  const double r2d = 180./3.141592654;
  const double me = 0.000511;
  
  const double tdiff0 = 3.0;
  const double tcut = 9.0;
  const double phi0 = 180.;
  const double phicut = 30.;
  const double minSep = 16.0;
  const double inX = 4.154;
  const double outX = 33.232;
  const double inY = 4.150;
  const double outY = 33.200;
  const double ccSlope = 2.21635;  
  const double zTgt = 705.0;  /* zTgt = 705.0*/
  const double zcut = 125.0;   
  const double decut = 1.0;   

  Bool_t inTime;
  Bool_t inAcceptance;
  Bool_t inPlane;
  Bool_t inRmin;
  Bool_t inTarget;
  Bool_t inEnergy;
  
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         run;
   Float_t         evn;
   Float_t         tid;
   Float_t         tdiff;
   Float_t         eg;
   Float_t         e1;
   Float_t         x1;
   Float_t         y1;
   Float_t         e2;
   Float_t         x2;
   Float_t         y2;
   Float_t         id1;
   Float_t         id2;
   Float_t         typ1;
   Float_t         typ2;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_evn;   //!
   TBranch        *b_tid;   //!
   TBranch        *b_tdiff;   //!
   TBranch        *b_eg;   //!
   TBranch        *b_e1;   //!
   TBranch        *b_x1;   //!
   TBranch        *b_y1;   //!
   TBranch        *b_e2;   //!
   TBranch        *b_x2;   //!
   TBranch        *b_y2;   //!
   TBranch        *b_id1;   //!
   TBranch        *b_id2;   //!
   TBranch        *b_typ1;   //!
   TBranch        *b_typ2;   //!

   ComptAna(TTree *tree=0);
   virtual ~ComptAna();
   virtual Int_t    zCut(Long64_t entry);
   virtual Int_t    tCut(Long64_t entry, Bool_t inCut);
   virtual Int_t    phiCut(Long64_t entry);
   virtual Int_t    fidCut(Long64_t entry);
   virtual Int_t    rminCut(Long64_t entry);
   virtual Int_t    deCut(Long64_t entry, Int_t mode);
   virtual Double_t delE(Long64_t entry, Int_t mode);
   virtual Double_t openZ(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void     Print(TCanvas *c, const char *format, string label, string ext, Bool_t mode);
};

#endif

#ifdef ComptAna_cxx
ComptAna::ComptAna(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("comptonIIMC.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("comptonIIMC.root");
      }
      f->GetObject("cmpt_ntuple",tree);

   }
   Init(tree);
}

ComptAna::~ComptAna()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ComptAna::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ComptAna::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void ComptAna::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("evn", &evn, &b_evn);
   fChain->SetBranchAddress("tid", &tid, &b_tid);
   fChain->SetBranchAddress("tdiff", &tdiff, &b_tdiff);
   fChain->SetBranchAddress("eg", &eg, &b_eg);
   fChain->SetBranchAddress("e1", &e1, &b_e1);
   fChain->SetBranchAddress("x1", &x1, &b_x1);
   fChain->SetBranchAddress("y1", &y1, &b_y1);
   fChain->SetBranchAddress("e2", &e2, &b_e2);
   fChain->SetBranchAddress("x2", &x2, &b_x2);
   fChain->SetBranchAddress("y2", &y2, &b_y2);
   fChain->SetBranchAddress("id1", &id1, &b_id1);
   fChain->SetBranchAddress("id2", &id2, &b_id2);
   fChain->SetBranchAddress("typ1", &typ1, &b_typ1);
   fChain->SetBranchAddress("typ2", &typ2, &b_typ2);
   Notify();
}

Bool_t ComptAna::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ComptAna::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

Int_t ComptAna::tCut(Long64_t entry, Bool_t inCut)
{
  inTime = false;
  
  if (inCut) inTime = fabs(tdiff-tdiff0) < tcut;
  if (!inCut) inTime = fabs(tdiff-tdiff0) > tcut;
  
  if ( inTime ) {
    return 1;
  } else {
    return -1;
  }
}

Double_t ComptAna::openZ(Long64_t entry) {
	
  double z;
  double a = 1.0 - (0.5109989e-3*eg)/e1/e2;
  double b = (x1*x1*x2*x2 + x1*x1*y2*y2 + y1*y1*x2*x2 + y1*y1*y2*y2);
  double c = (x1*x1 + y1*y1 + x2*x2 + y2*y2);
  double d = (x1*x1*x2*x2 + y1*y1*y2*y2 + 2*x1*x2*y1*y2);
  double e = x1*x2 + y1*y2;
  double A = a*a - 1;
  double B = a*a*c - 2*e;
  double C = a*a*b - d;
  double t = (- B - sqrt(B*B - 4*A*C))/2./A;
  if (t >= 0) {
    z = sqrt(t);
  } else {
    z = -100.;
  }
  return z;
}

Int_t ComptAna::zCut(Long64_t entry)
{   
  inTarget = false;
  inTarget = fabs(openZ(entry)-zTgt) < zcut;
  
  if ( inTarget ) {
    return 1;
  } else {
    return -1;
  }
}

Int_t ComptAna::phiCut(Long64_t entry)
{   
  inPlane = false;
  inPlane = fabs(fabs((atan2(y2,x2)-atan2(y1,x1))*r2d)-phi0)<phicut;
  
  if ( inPlane ) {
    return 1;
  } else {
    return -1;
  }
}

Int_t ComptAna::fidCut(Long64_t entry)
{   
  inAcceptance = false;
  inAcceptance = ((fabs(x1)>inX || fabs(y1)>inY) && (fabs(x1)<outX && fabs(y1)<outY))&&
    ((fabs(x2)>inX || fabs(y2)>inY) && (fabs(x2)<outX && fabs(y2)<outY));
  
  if ( inAcceptance ) {
    return 1;
  } else {
    return -1;
  }
}

Int_t ComptAna::rminCut(Long64_t entry)
{   
  inRmin = false;
  inRmin = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)) > minSep;
  
  if ( inRmin ) {
    return 1;
  } else {
    return -1;
  }
}

Int_t ComptAna::deCut(Long64_t entry, Int_t mode)
{   
  inEnergy = false;
  inEnergy = fabs(delE(entry,mode)) < decut;

  if ( inEnergy ) {
    return 1;
  } else {
    return -1;
  }
}

Double_t ComptAna::delE (Long64_t entry, Int_t mode)
{
  double t1, t2;
  double r1, r2;
  double cospsi;
  double tan1, tan2;
  double cos1, cos2;
  double ecalc1, ecalc2;
  double egamma = -100.0;

  t1 = sqrt(x1 * x1 + y1 * y1);
  t2 = sqrt(x2 * x2 + y2 * y2);
  r1 = sqrt(t1 * t1 + zTgt * zTgt);
  r2 = sqrt(t2 * t2 + zTgt * zTgt);
  cospsi = (x1 * x2 + y1 * y2 + zTgt * zTgt) / r1 / r2;
  tan1 = t1 / zTgt;
  tan2 = t2 / zTgt;
  cos1 = sqrt(1. / (1. + tan1 * tan1));
  cos2 = sqrt(1. / (1. + tan2 * tan2));
  ecalc1 = eg / (1. + eg / me * (1-cos1));
  ecalc2 = eg / (1. + eg / me * (1-cos2));

  switch (mode) {
  case 0: egamma = e1 * e2 * (1.0 - cospsi) / me;
    break;
  case 1: egamma = e1 * (1 + t1 / t2);
    break;
  case 2: egamma = e2 * (1 + t2 / t1);
    break;
  case 3: egamma = e1 * e1 * (t1 / t2) * (1.0 - cospsi) / me;
    break;
  case 4: egamma = e2 * e2 * (t2 / t1) * (1.0 - cospsi) / me;
    break;
  case 5: egamma = me * (1 + t1 / t2) * (1 + t1 / t2) / (t1 / t2) / (1.0 - cospsi);
    break;
  case 6: egamma = eg - (e1 - ecalc1);
    break;
  case 7: egamma = eg - (e2 - ecalc2);
    break;
  }
  return eg - egamma;
}

void ComptAna::Print(TCanvas *c, const char *format, string label, string ext, Bool_t mode)
{
  char fileName[128]; 
  sprintf(fileName,format,label.c_str(),ext.c_str()); 
  if (mode) c->Print(fileName);
}
#endif // #ifdef ComptAna_cxx
