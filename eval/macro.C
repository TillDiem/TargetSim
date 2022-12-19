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
  gROOT->ForceStyle(1); gStyle->SetPadTopMargin(0.07); gStyle->SetPadRightMargin(0.15); gStyle->SetPadLeftMargin(0.15); gStyle->SetPadBottomMargin(0.16); gStyle->SetLabelSize(0.06,"xyz"); gStyle->SetTitleSize(0.06,"xyz"); gStyle->SetTitleOffset(0.9,"x"); gStyle->SetTitleOffset(1.1,"y"); gStyle->SetTitleOffset(0.9,"z"); gStyle->SetStatX(0.8); gStyle->SetStatW(0.2); gStyle->SetStatY(0.85); gStyle->SetStatH(0.1); gStyle->SetOptStat(0); gStyle->SetHistLineWidth(3); gStyle->SetPadTickX(1); gStyle->SetPadTickY(1); gStyle->SetPadGridX(kTRUE); gStyle->SetPadGridY(kTRUE);
  string PNGOutputFolderName, ROOTOutputFileName;
  ROOTOutputFileName=Form("%s/ROOT/NEUTFile_%s.root", OutputDirectory.c_str(), NEUTFile.c_str());
  PNGOutputFolderName=Form("%s/PNGs/%s", OutputDirectory.c_str(), NEUTFile.c_str());

  	std::string G4InputFileName = "output.root";
	TFile * G4InputFile = new TFile(G4InputFileName.c_str());

	TTree *G4InputTree = (TTree*)G4InputFile->Get("event_tree");

	double energy_deposit;
	vector <double> *hit_start_x = nullptr;
	vector <double> *hit_start_y = nullptr;
	vector <double> *hit_start_z = nullptr;
	vector <double> *hit_start_t = nullptr;
	vector <double> *hit_energy_deposit = nullptr;
	vector <double> *hit_length = nullptr;
  	vector<double> *particle_pdg_code = nullptr;

	std::vector< int >    * particle_track_id= 0;
	std::vector< int >    * particle_parent_track_id= 0;
	std::vector< double > * particle_mass= 0;
	std::vector< double > * particle_charge= 0;
	std::vector< int >    * particle_process_key= 0;
	std::vector< int >    * particle_total_occupancy= 0;
  	vector<double> *hit_track_id= nullptr;
  	vector<double> *hit_pdg_code= nullptr;
	int number_particles;


	G4InputTree->SetBranchAddress("energy_deposit", &energy_deposit);
	G4InputTree->SetBranchAddress("hit_start_x", &hit_start_x);
	G4InputTree->SetBranchAddress("hit_start_y", &hit_start_y);
	G4InputTree->SetBranchAddress("hit_start_z", &hit_start_z);
	G4InputTree->SetBranchAddress("hit_length", &hit_length);
	G4InputTree->SetBranchAddress("hit_start_t", &hit_start_t);
	G4InputTree->SetBranchAddress("hit_pdg_code", &hit_pdg_code);
std::vector< int >    * particle_track_id_ = 0;
std::vector< int >    * particle_parent_track_id_ = 0;
std::vector< int >    * particle_pdg_code_ = 0;
std::vector< double > * particle_mass_ = 0;
std::vector< double > * particle_charge_ = 0;
std::vector< int >    * particle_process_key_ = 0;
std::vector< int >    * particle_total_occupancy_ = 0;
G4InputTree->SetBranchAddress("hit_energy_deposit", &hit_energy_deposit);
	G4InputTree->SetBranchAddress("hit_length", &hit_length);
  	G4InputTree->SetBranchAddress("hit_track_id", &hit_track_id);

  	G4InputTree->SetBranchAddress("particle_pdg_code", &particle_pdg_code);


	G4InputTree->SetBranchAddress("particle_track_id", &particle_track_id);
        G4InputTree->SetBranchAddress("particle_parent_track_id", &particle_parent_track_id);
        G4InputTree->SetBranchAddress("particle_pdg_code", &particle_pdg_code);
        G4InputTree->SetBranchAddress("particle_mass", &particle_mass);
        G4InputTree->SetBranchAddress("particle_charge", &particle_charge);
        G4InputTree->SetBranchAddress("particle_process_key", &particle_process_key);
        G4InputTree->SetBranchAddress("particle_total_occupancy", &particle_total_occupancy);

	G4InputTree->SetBranchAddress("number_particles", &number_particles);


	int NEventsToLoopOver = G4InputTree->GetEntries(); // 100000


	TH2F * h2 = new TH2F("h2", "h2", 101, -3, 3, 101, -3, 3);

	for(int EventIt = 0; EventIt < NEventsToLoopOver; EventIt++){
		G4InputTree->GetEntry(EventIt);
		TVector3 earlyy;
		TVector3 latee;
		double early = 100000;
		double late = -1;


		cout << " ------------------ Event " << EventIt << " ------------------ " << endl;
		for(int i = 0; i < hit_start_x->size(); i++){
			cout << "PDG: " << hit_pdg_code->at(i) << "  TrackID: " << hit_track_id->at(i) << endl;
			if( hit_track_id->at(i) == 1){
				if(hit_start_t->at(i) < early){
					early = hit_start_t->at(i);
					earlyy.SetXYZ(hit_start_x->at(i), hit_start_y->at(i), hit_start_z->at(i));
				}
				if(hit_start_t->at(i) > late){
					late = hit_start_t->at(i);
					latee.SetXYZ(hit_start_x->at(i), hit_start_y->at(i), hit_start_z->at(i));
				}
			}
		}
		int bin_e = h2->FindBin(earlyy.X(), earlyy.Z());
		cout << "earlyy: " << earlyy.X() << " " << earlyy.Y() << " " << earlyy.Z() << endl;
		int bin_l = h2->FindBin(latee.X(), latee.Z());
		h2->SetBinContent(bin_l, h2->GetBinContent(bin_l) + 1);


		h2->SetBinContent(bin_e, h2->GetBinContent(bin_e) + 1);
		int bin = h2->FindBin(earlyy.X(), earlyy.Z());
		cout << h2->GetBinContent(bin) << endl;

		cout << bin_e << endl;


	}

/* 	for (int EventIt=0; EventIt < NEventsToLoopOver; EventIt++) */
/* 	{ */
/* 		//if(EventIt!=1894) continue; */
/* 		std::cout << "Event: " << EventIt << std::endl; */
/* 		G4InputTree->GetEntry(EventIt); */

/* 		std::vector<int> TrackIDs; */


/* 		TVector3 early; */
/* 		TVector3 late; */
/* 		double earliest = 100000; */

/* 		double latest = -1; */

/* 		for(int npartIt = 0; npartIt < number_particles; npartIt++) */
/* 		{ */
/* 			if(particle_pdg_code->at(npartIt) == 2112) */
/* 			{ */
/* 				TrackIDs.push_back(particle_track_id->at(npartIt)); */
/* 			} */
/* 		} */


/* 		for(int hitIt = 0; hitIt < hit_start_x->size(); hitIt++){ */
/* 			int trackID = hit_track_id->at(hitIt); */
/* 			cout << trackID << endl; */

/* 			//check if trackID is in TrackIDs */
/* 			bool found = false; */
/* 			for(int TrackIt = 0; TrackIt < TrackIDs.size(); TrackIt++){ */
/* 				if(TrackIDs[TrackIt] == trackID){ */
/* 					found = true; */
/* 					h2->Fill(hit_start_x->at(hitIt), hit_start_z->at(hitIt)); */
/* 				} */
/* 			} */
/* 			/1* if(trackID==1){ *1/ */
/* 			/1* 	/2* if(hit_start_t->at(hitIt)<earliest){ *2/ *1/ */
/* 			/1* 	/2* 	earliest = hit_start_t->at(hitIt); *2/ *1/ */
/* 			/1* 	/2* 	early.SetXYZ(hit_start_x->at(hitIt), hit_start_y->at(hitIt), hit_start_z->at(hitIt)); *2/ *1/ */
/* 			/1* 	/2* } *2/ *1/ */
/* 			/1* 	/2* if(hit_start_t->at(hitIt)>latest){ *2/ *1/ */
/* 			/1* 	/2* 	latest = hit_start_t->at(hitIt); *2/ *1/ */
/* 			/1* 	/2* 	late.SetXYZ(hit_start_x->at(hitIt), hit_start_y->at(hitIt), hit_start_z->at(hitIt)); *2/ *1/ */
/* 			/1* 	/2* } *2/ *1/ */

/* 			/1* } *1/ */
/* 		} */


/* /1* 		cout << early.X() << " " << early.Y() << " " << early.Z() << endl; *1/ */
/* /1* 		cout << late.X() << " " << late.Y() << " " << late.Z() << endl; *1/ */
/* /1* 		cout << earliest << " " << latest << endl; *1/ */

/* 		cout << " ------------------------------------- " << endl; */

/* 		//h2->Fill(early.X(), early.Z()); */
/* 		//h2->Fill(late.X(), late.Z()); */

/* 	} */




		TCanvas * c1 = new TCanvas("c1", "c1", 800, 800);
		h2->GetZaxis()->SetRangeUser(0, 100);
		h2->Draw("colz");
		c1->SaveAs("test.png");



 cout << " --------------------------------------------------------- " << endl;
 cout << " --------------------------------------------------------- " << endl;
  //////////////////////////////////////////////////////////
  // --------------- OUTPUT ----------------------------- //
  //////////////////////////////////////////////////////////
  /* //Open ROOT output file to save histograms */
  /* TFile *ROOTOutputFile = new TFile(ROOTOutputFileName.c_str(), "RECREATE"); */
  /* ROOTOutputFile->Close(); */


  /* TCanvas *cCanvas1= new TCanvas("cCanvas_AngleLepton","cCanvas_AngleLepton",1000,800); */
  /* h1->SetTitle("PDG Produced"); */
  /* h1->GetXaxis()->SetTitle("PDG Code"); */
  /* h1->Draw("HIST"); */
  /* cCanvas1->SaveAs(Form("%s/h_PDG.png",PNGOutputFolderName.c_str())); */
  /* delete cCanvas1; */

  /* NEUTInputFile1->Close(); */
//
}
