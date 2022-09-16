#include <iostream>
#include <string>
#include <fstream>
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TCut.h"
#include <TRandom3.h>
#include <vector>
#include "TGraph.h"
#include "TLegend.h"
#include "TMath.h"

using namespace std;

void macro(string NEUTFile="nuis_out", string InputDirectory="", string OutputDirectory="" )
{

  //Making plots nicer
  gROOT->ForceStyle(1); gStyle->SetPadTopMargin(0.07); gStyle->SetPadRightMargin(0.05); gStyle->SetPadLeftMargin(0.15); gStyle->SetPadBottomMargin(0.16); gStyle->SetLabelSize(0.06,"xyz"); gStyle->SetTitleSize(0.06,"xyz"); gStyle->SetTitleOffset(0.9,"x"); gStyle->SetTitleOffset(1.1,"y"); gStyle->SetTitleOffset(0.9,"z"); gStyle->SetStatX(0.8); gStyle->SetStatW(0.2); gStyle->SetStatY(0.85); gStyle->SetStatH(0.1); gStyle->SetOptStat(0); gStyle->SetHistLineWidth(3); gStyle->SetPadTickX(1); gStyle->SetPadTickY(1); gStyle->SetPadGridX(kTRUE); gStyle->SetPadGridY(kTRUE);


  //Defining output path for PNG and output file name for ROOT file
  string PNGOutputFolderName, ROOTOutputFileName;
  ROOTOutputFileName=Form("%s/ROOT/NEUTFile_%s.root", OutputDirectory.c_str(), NEUTFile.c_str());
  PNGOutputFolderName=Form("%s/PNGs/%s", OutputDirectory.c_str(), NEUTFile.c_str());

  //Defining input file
  // CRPA HT XSec
  char* NEUTInputFileName1;
  NEUTInputFileName1 = Form("%s/%s.root", InputDirectory.c_str(), NEUTFile.c_str());
  TFile *NEUTInputFile1 = new TFile(NEUTInputFileName1);
  TH1F *Flux= (TH1F*)NEUTInputFile1->Get("FlatTree_FLUX");


  TTree *NEUTInputTree = (TTree*)NEUTInputFile1->Get("Hits");
  int PDG;
  double energy;
  int fEvent;
  int fParentID;
  double fPx;
  double fPy;
  double fPz;
  double fX;
  double fY;
  double fZ;
int fTrackID;
  string fprocess;
  Char_t particle;
  double time;

  NEUTInputTree->SetBranchAddress("PDG", &PDG);
  NEUTInputTree->SetBranchAddress("fEvent", &fEvent);
  NEUTInputTree->SetBranchAddress("energy", &energy);
  NEUTInputTree->SetBranchAddress("fParentID", &fParentID);
  NEUTInputTree->SetBranchAddress("fPx", &fPx);
  NEUTInputTree->SetBranchAddress("fPy", &fPy);
  NEUTInputTree->SetBranchAddress("fPz", &fPz);
  NEUTInputTree->SetBranchAddress("fX", &fX);
  NEUTInputTree->SetBranchAddress("fY", &fY);
  NEUTInputTree->SetBranchAddress("fZ", &fZ);
  NEUTInputTree->SetBranchAddress("fTrackID", &fTrackID);
  NEUTInputTree->SetBranchAddress("fprocess", &fprocess);
  NEUTInputTree->SetBranchAddress("particle", &particle);
  NEUTInputTree->SetBranchAddress("time", &time);

  int NEventsToLoopOver = NEUTInputTree->GetEntries(); // 100000
  cout << "Looping over " << NEventsToLoopOver << " events..." << endl;
  cout << endl;

  TH2F *h2 = new TH2F("h2", "h2", 100, -2000, 2000, 100, -2000, 2050);

  vector<vector<int>> PDGVector;

  int currentEvent = 0;

  //Loop over events in tree
  for (int EventIt=0; EventIt < NEventsToLoopOver; EventIt++)
  {
    NEUTInputTree->GetEntry(EventIt);
    cout << "Event " << EventIt << endl;
    cout << fEvent << endl;
    if(fEvent != currentEvent)
    {
      currentEvent = fEvent;
      h2->Reset();
    }
    cout << fParentID << endl;
    if(fParentID == 0)
    {
	    cout << "fX: " << fZ << endl;
      h2->Fill(fX, fZ);
    }


  }//End for loop


 cout << " --------------------------------------------------------- " << endl;
 cout << " --------------------------------------------------------- " << endl;
  //////////////////////////////////////////////////////////
  // --------------- OUTPUT ----------------------------- //
  //////////////////////////////////////////////////////////
  //Open ROOT output file to save histograms
  TFile *ROOTOutputFile = new TFile(ROOTOutputFileName.c_str(), "RECREATE");
  ROOTOutputFile->Close();


  TCanvas *cCanvas2= new TCanvas("cCanvas_AngleLepton","cCanvas_AngleLepton",1000,800);
  h2->SetTitle("Funny HIstogram");
  h2->GetXaxis()->SetTitle("Cos#theta");
  h2->Draw("COLZ");
  cCanvas2->SaveAs(Form("%s/h_AngleLepton.png",PNGOutputFolderName.c_str()));
  delete cCanvas2;

  NEUTInputFile1->Close();
//
}
