//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Mar  7 23:15:12 2015 by ROOT version 5.34/18
// from TTree cmpt_ntuple/3 particles' phy info
// found on file: comptonII.root
//////////////////////////////////////////////////////////

#ifndef CompAnaII_h
#define CompAnaII_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class CompAnaII {
public :
  const double pi = 3.141592654;
  const double d2r = 3.141592654/180.;
  const double r2d = 180./3.141592654;
  const double me = 0.000511; 
  
  const double zTgt = 705.0;  
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

   CompAnaII(TTree *tree=0);
   virtual ~CompAnaII();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual Double_t OpenZ(Long64_t entry);
   virtual Double_t delE (Long64_t entry, Int_t mode);
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef CompAnaII_cxx
CompAnaII::CompAnaII(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("comptonII.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("comptonII.root");
      }
      f->GetObject("cmpt_ntuple",tree);

   }
   Init(tree);
}

CompAnaII::~CompAnaII()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t CompAnaII::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t CompAnaII::LoadTree(Long64_t entry)
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

void CompAnaII::Init(TTree *tree)
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

Bool_t CompAnaII::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void CompAnaII::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t CompAnaII::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}



Double_t CompAnaII::OpenZ(Long64_t entry) {
	
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

Double_t CompAnaII::delE (Long64_t entry, Int_t mode) {
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
  return (eg - egamma);
}
#endif // #ifdef CompAnaII_cxx
