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
//Make plots not extremly ugly
  gROOT->ForceStyle(1); gStyle->SetPadTopMargin(0.07); gStyle->SetPadRightMargin(0.05); gStyle->SetPadLeftMargin(0.15); gStyle->SetPadBottomMargin(0.16); gStyle->SetLabelSize(0.06,"xyz"); gStyle->SetTitleSize(0.06,"xyz"); gStyle->SetTitleOffset(0.9,"x"); gStyle->SetTitleOffset(1.1,"y"); gStyle->SetTitleOffset(0.9,"z"); gStyle->SetStatX(0.8); gStyle->SetStatW(0.2); gStyle->SetStatY(0.85); gStyle->SetStatH(0.1); gStyle->SetOptStat(0); gStyle->SetHistLineWidth(3); gStyle->SetPadTickX(1); gStyle->SetPadTickY(1); gStyle->SetPadGridX(kTRUE); gStyle->SetPadGridY(kTRUE);
  string PNGOutputFolderName, ROOTOutputFileName;
  ROOTOutputFileName=Form("%s/ROOT/NEUTFile_%s.root", OutputDirectory.c_str(), NEUTFile.c_str());
  PNGOutputFolderName=Form("%s/PNGs/%s", OutputDirectory.c_str(), NEUTFile.c_str());

  char* NEUTInputFileName1;
  NEUTInputFileName1 = Form("%s/%s.root", InputDirectory.c_str(), NEUTFile.c_str());
  TFile *NEUTInputFile1 = new TFile(NEUTInputFileName1);

  TTree *NEUTInputTree = (TTree*)NEUTInputFile1->Get("HitData");
  int PDG;
  int fEvent;
  int fTrackID;

  NEUTInputTree->SetBranchAddress("hit_pdg_code", &PDG);
  NEUTInputTree->SetBranchAddress("Event", &fEvent);
  NEUTInputTree->SetBranchAddress("hit_track_id", &fTrackID);

  int NEventsToLoopOver = NEUTInputTree->GetEntries(); // 100000
  cout << "Looping over " << NEventsToLoopOver << " events..." << endl;
  cout << endl;


  vector<int> Track_ID ;
  vector<int> PDG_Codes;

  Track_ID.push_back(-999);
  PDG_Codes.push_back(-999);

  TH1I *h1 = new TH1I("PDG", "PDG",445, -222, 222);
  int currentEvent = 0;

  //Loop over events in tree
  for (int EventIt=0; EventIt < NEventsToLoopOver; EventIt++)
  {
    NEUTInputTree->GetEntry(EventIt);

    // Check if a new particle gun was fired
    if(fEvent != currentEvent)
    {
	cout << "New Event" << endl;
	// Fill the PDG Values
	for(int i = 0; i < PDG_Codes.size(); i++)
	{
		// We are only interested in the Pi0 and Pi+-
		if(abs(PDG_Codes[i])==211 || PDG_Codes[i]==111 || PDG_Codes[i]==221)
		{
			h1->Fill(PDG_Codes[i]);
		}
	}
      currentEvent = fEvent;
      Track_ID.clear();
      PDG_Codes.clear();
      cout << "Reset" << endl;
      Track_ID.push_back(fTrackID);
      PDG_Codes.push_back(PDG);
    }

    // Check if the current track ID was already seend
    if(find(Track_ID.begin(), Track_ID.end(), fTrackID) != Track_ID.end())
    {
      // Do nothing
    }
    else
    {
      Track_ID.push_back(fTrackID);
      PDG_Codes.push_back(PDG);
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


  TCanvas *cCanvas1= new TCanvas("cCanvas_AngleLepton","cCanvas_AngleLepton",1000,800);
  h1->SetTitle("PDG Produced");
  h1->GetXaxis()->SetTitle("PDG Code");
  h1->Draw("HIST");
  cCanvas1->SaveAs(Form("%s/h_PDG.png",PNGOutputFolderName.c_str()));
  delete cCanvas1;

  NEUTInputFile1->Close();
//
}
