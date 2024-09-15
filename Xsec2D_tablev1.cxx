// code utk buat Xsec table utk 2D
// usage: root -l -b 'Xsec2D_tablev1.cxx("h2DNsig_table_.root", "h2Deff_charm.root", "Dstar")'
// kita buat full range, xde skipping2. senang nk kira uncert.
// root -l -b 'Xsec2D_tablev1.cxx("h2D_Nsigtable6_.root", "h2Deff_charm.root", "Dstar", "6_")'
// root -l -b 'Xsec2D_tablev1.cxx("h2D_Nsigtable10all_.root", "h2Deff_charm.root", "Dstar", "10all_")'
//root -l -b 'Xsec2D_tablev1.cxx("h2D_Data10all_final_deltam.root", "h2Deff_deltam_D0Kpi.root", "Dstar", "10all_final_deltam_D0Kpi_")'
//root -l -b 'Xsec2D_tablev1.cxx("h2D_Data10all_final_deltamr.root", "h2Deff_deltamr_charm.root", "Dstar", "10all_final_deltamr_charm_")'
// root -l -b 'Xsec2D_tablev1.cxx("h2D_Data11all_deltamr.root", "h2D_MCD0Kpi_semitight6_deltamrt.root", "Dstar", "11all_deltamr_D0Kpi_")'
// root -l -b 'Xsec2D_tablev1.cxx("h2D_Data15JSON5_deltamr.root", "h2D_MCD0Kpi_split2_deltamrt.root", "Dstar", "data15JSON5_deltamr_D0Kpi_")'

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <memory>
#include <utility>
#include <algorithm>
#include <numeric>
#include <functional>
#include <stdexcept>
#include <type_traits>
#include <array>
#include <vector>
#include <map>
#include <tuple>
#include <cmath>

#include "TROOT.h" 
#include "TH1.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TStyle.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TROOT.h"
#include "TGaxis.h"
#include "TLatex.h"
#include "TBufferFile.h"
#include "TLorentzVector.h"
#include "TPaveStats.h"
#include "TLine.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TColor.h"
#include "TH1F.h"
#include "TPaletteAxis.h"
#include "TEfficiency.h"
#include "TH3.h"

/*
// Method to convert number become string
template <typename Number> std::string toStr(Number inNo, const int prec = -1, const bool fixed = false) {
  std::ostringstream outStr;
  if (fixed)
    outStr << std::fixed;
  if (prec > 0)
    outStr << std::setprecision(prec);

  outStr << inNo;
  return outStr.str();
}

void drawCan(TCanvas* varCan, string outName, string txtfile1, string whichDmeson, string outDir) {
  varCan->SaveAs((outDir + outName + txtfile1 + whichDmeson + ".pdf").c_str() );
  varCan->Close();
}

// Histo Style
void styleHist(TH2D* varHist, Float_t zMin, Float_t zMax, string ploTitle, string xTitle, string yTitle, Float_t markSize, Float_t yMin, Float_t yMax, Float_t xMin, Float_t xMax, Int_t useCol, Float_t yOff, Float_t xOff) {
  // don't want to customize da z range
  if (zMin < zMax) {
    varHist->SetMinimum(zMin);
    varHist->SetMaximum(zMax);
  }
  
  varHist->GetYaxis()->SetTitle(yTitle.c_str());
  varHist->GetXaxis()->SetTitle(xTitle.c_str());
  varHist->SetTitle(ploTitle.c_str());
  varHist->SetMarkerSize(markSize);
  varHist->GetYaxis()->SetRangeUser(yMin, yMax);
  varHist->GetXaxis()->SetRangeUser(xMin, xMax);  
  varHist->SetLineColor(useCol);  
  varHist->GetYaxis()->SetTitleOffset(yOff);
  varHist->GetXaxis()->SetTitleOffset(xOff);
  
  gStyle->SetOptStat(0);
  // put #0 in 0bincontent
  gStyle->SetHistMinimumZero();
}

// Drawing flow
void drawVar(TCanvas* varCan, TH2D* varHist, string drawOpt) {

  varCan->cd();  
  varHist->Draw(drawOpt.c_str() );  
  varCan->Update();
  
  //TPaletteAxis *allpallete;  
  //allpallete = (TPaletteAxis*) varHist->GetListOfFunctions()->FindObject("palette");
  //allpallete->SetX1NDC(0.905);
  //allpallete->SetX2NDC(0.935);
  //allpallete->SetY1NDC(0.1);
  //allpallete->SetY2NDC(0.9);
  
}
*/

void stylePal(TH2D* varHist, TCanvas* varCan, Float_t x1, Float_t x2, Float_t y1, Float_t y2) {

  TPaletteAxis *allpallete;  
  allpallete = (TPaletteAxis*) varHist->GetListOfFunctions()->FindObject("palette");
  allpallete->SetX1NDC(x1);
  allpallete->SetX2NDC(x2);
  allpallete->SetY1NDC(y1);
  allpallete->SetY2NDC(y2);
}

// Canvas Style
void styleCan(TCanvas* varCan, Float_t tMarg, Float_t bMarg, Float_t lMarg, Float_t rMarg) {
  varCan->SetTopMargin(tMarg);
  varCan->SetBottomMargin(bMarg);
  varCan->SetLeftMargin(lMarg);
  varCan->SetRightMargin(rMarg);
}

void Xsec2D_tablev1(const std::string &fileName1,
		    const std::string &fileName2,
		    //const std::string &txtfile1,
		    //const std::string &txtfile2,
		    const std::string &whichDmeson,
		    const std::string &outName) {
  
  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(false);
  TGaxis::SetMaxDigits(2);
  
  //////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////// Place you need to change accordingly ////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////

  // input directory for efficiency
  //string inDir1 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/66plots/";
  //string inDir2 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Eff/plots/new/";
  //string inDir1 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/66plots/310120/";
  //string inDir2 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Eff/fullrange/310120/";
  //string inDir1 = "/home/zulaiha/PhD/Analysis/wow/Xsec/eachpT/";
  //string inDir2 = "/home/zulaiha/PhD/Analysis/wow/Xsec/eachpT/";
  //string inDir2 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/Eff/";
  //string inDir2 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/table/new/";
  //string inDir2 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/table/beauty42/";
  //string inDir2 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/table/semitight4/";
  //string inDir2 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/table/semitight6/";
  //string inDir2 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/table/split2/";
  //string inDir2 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/table/beauty5/";
  //string inDir2 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/table/charm_KK/";
  string inDir2 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/table/beauty7/";

  // directory for Nsignal
  //string inDir1 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/testforAchim/";
  //string inDir1 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/table/";  
  //string inDir1 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/table/data11all/";  
  //string inDir1 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/table/data15JSON5/";  
  //string inDir1 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/table/data0BMB_13/";  
  string inDir1 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/table/data13all/";  
  
  // output directory
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Xsec_plot/new/";
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Xsec_plot/310120/";  
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Xsec_plot/70220/";  
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/eachpT/";
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/testforAchim/Xsec/";
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/testforAchim/Xsec/";
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/new/";
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/";
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/11all_semitight6/";
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/data15JSON5_split2/";
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/0BMB_13_beauty5_dEdxyz2/";
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/0BMB_13_charm_KK/";
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/13all_beauty5_dEdxyz2/";
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/13all_charm_KK/";
  string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/13all_beauty7_dEdxyz2/";

  // create a rootfile
  TFile fout((outDir + "h2DXsec_" + outName +  whichDmeson + ".root").c_str(),"RECREATE");

  // histogram u want to get
  //string var1 = "Nsig_"; // use for data, maybe change?
  string var1 = "N_";
  //string var2 = "effBR_";
  string var2 = "effnerr_";
  
  //////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////// End of place you need to change accordingly //////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////

  
  //////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////// Please don't change anything here ///////////////////////////////////
  //////////////////////////// unless u want to change the algorithm ///////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////

  cout << "**********************************************" <<  endl;
  cout << "**********************************************" <<  endl;
  cout << "reading " << inDir1 << fileName1 << " & " << inDir2 << fileName2 << endl;
  cout << "writing to " << outDir << endl;
  cout << "**********************************************" <<  endl;
  cout << "**********************************************" <<  endl;
  
  //auto inFile1 = std::unique_ptr<TFile>(TFile::Open( (inDir1 + fileName1).c_str() ));
  //auto inFile2 = std::unique_ptr<TFile>(TFile::Open( (inDir2 + fileName2).c_str() ));

  //auto h2D_Nsig = std::unique_ptr<TH2D>(dynamic_cast<TH2D *>((inFile1->Get(var1.c_str() ))->Clone("xxx")));
  //auto h2D_Eff = std::unique_ptr<TH2D>(dynamic_cast<TH2D *>((inFile2->Get(var2.c_str() ))->Clone("yyy")));
  //auto h2D_Xsec = std::unique_ptr<TH2D>(dynamic_cast<TH2D *>(("test", "test", 72, 0., 72.)));  
  //std::unique_ptr<TH2D> h2D_Xsec{new TH2D("test", "test", 72, 0., 72.)};
  
  TFile *inFile1 = new TFile((inDir1 + fileName1).c_str());
  TFile *inFile2 = new TFile((inDir2 + fileName2).c_str());
  
  TH2D *h2D_Nsig = (TH2D*) inFile1->Get(var1.c_str())->Clone("xxx");
  TH2D *h2D_Eff = (TH2D*) inFile2->Get(var2.c_str())->Clone("yyy");
  TH2D *h2D_Effb4 = (TH2D*) inFile2->Get(var2.c_str())->Clone("zzz");
  TH2D *h2D_Xsec = new TH2D("test", "", 6, 0., 3.0, 12, 0, 12.);
  
  for (Int_t ii = 1; ii < 12; ++ii) {
    for (Int_t jj = 1; jj < 7; ++jj) {
  
      h2D_Nsig->GetBinContent(jj, ii);
      h2D_Nsig->GetBinError(jj, ii);
      
      h2D_Eff->GetBinContent(jj, ii);
      h2D_Eff->GetBinError(jj, ii);

      h2D_Effb4->GetBinContent(jj, ii);
      h2D_Effb4->GetBinError(jj, ii);      
      //cout << "value: " << h2D_Nsig->GetBinContent(jj, ii) << endl;
      //cout << "value: " << h2D_Eff->GetBinContent(jj, ii) << endl;
    }
  }

  //h2D_Eff->Scale(700);
  //h2D_Eff->Scale(1750); // ~2.5 times larger stats

  // lumi ffrom Achim for diff.test
  //h2D_Eff->Scale(1750); // _6
  //h2D_Eff->Scale(1490); //_7a & 9
  //h2D_Eff->Scale(850); // _10mu & _10mu2 0.85nb-1
  //h2D_Eff->Scale(520); // _10el2 0.52nb-1
  //h2D_Eff->Scale(3070); // _10all 3.07nb-1
  h2D_Eff->Scale(3000); // _10all_final, 11all 3.00nb-1
  //h2D_Eff->Scale(40200); // data15JSON5 40.2nb-1
  //h2D_Eff->Scale(1630); // data0BMB_13 1.63nb-1 (comapre wit MCbeauty5_dEdxyz2)
  
  // 4 canvas for checking the numbers are correct
  TCanvas *c00 = new TCanvas("c00", "c00", 200, 10, 1000, 800);
  TCanvas *c01 = new TCanvas("c01", "c01", 200, 10, 1000, 800);
  
  c00->Divide(2,2);
  gStyle->SetPalette(kMint);
  TColor::InvertPalette();
  gStyle->SetPaintTextFormat(".3g");
  gStyle->SetOptStat(0);
  gStyle->SetHistMinimumZero();
  
  c00->cd(1);
  h2D_Effb4->Draw("colztexte");

  // print the value of h2D_Eff after scaled
  // to ensure we got a correct value after scaled
  for (Int_t ii = 1; ii < 12; ++ii) {
    for (Int_t jj = 1; jj < 7; ++jj) {  
      std::cout << "kkkk: " << h2D_Eff->GetBinContent(jj, ii) << endl;
    }
  }
  
  c00->cd(2);
  h2D_Eff->Draw("colztexte");
  c00->cd(3);
  h2D_Nsig->Draw("colztexte");

  h2D_Xsec = (TH2D*)h2D_Nsig->Clone();
  h2D_Xsec->GetXaxis()->SetTitle(" ");
  h2D_Xsec->GetYaxis()->SetTitle(" ");
  h2D_Xsec->SetTitle("#sigma D*^{#pm}"); // #pm for our measurement
  h2D_Xsec->Divide(h2D_Eff);
  //h2D_Xsec->Scale(0.5); // ALICE (only D*+)
  h2D_Xsec->GetYaxis()->SetTitle("p_{T} (GeV)");
  h2D_Xsec->GetXaxis()->SetTitle("|y|");
  h2D_Xsec->GetZaxis()->SetTitle("#sigma D*^{#pm} (ub)");

  c00->cd(4);
  h2D_Xsec->Draw("colztexte");

  c00->Update();
  c01->cd();
  styleCan(c01, 0.08, 0.11, 0.08, 0.13);  
  stylePal(h2D_Xsec, c01, 0.88, 0.92, 0.11, 0.92);

  h2D_Xsec->Draw("colztexte");
  
  c01->Update();

  //c00->SaveAs("new/XsecnoBRchecking.pdf");
  //c01->SaveAs("new/XsecnoBR.pdf");
  
  //c00->SaveAs((outDir + "XsecnoBRchecking.pdf").c_str());
  //c01->SaveAs((outDir + "XsecnoBR.pdf").c_str());
  
  c00->SaveAs((outDir + "check_" + outName + whichDmeson + ".pdf").c_str());
  c01->SaveAs((outDir + "Xsectable_" + outName + whichDmeson + ".pdf").c_str());  
  //c00->SaveAs((outDir + "XsecnoBRchecking_compareALICE.pdf").c_str());  

  //c00->SaveAs("new/XsecnoBRchecking_compareALICE.pdf");
  //c01->SaveAs("new/XsecnoBR_compareALICE.pdf");  
  //c00->Update();
  //cout << "Xsec: " <<  hhhh << endl;
  fout.cd();
  h2D_Xsec->Write();  
  gROOT->ProcessLine(".q");
}

// BR from PDG online (latest)
// D*->D0pi = (67.7 +- 0.5)% = 0.677 +- 0.005
// D0->Kpi = (3.95 +- 0.031)% = 0.0395 +- 0.00031
// D* BR = 0.026 or 2.6% (0.68 * 0.039 = 0.0264 +- 0.0729)
