// This is macro to make double differential plot
// for combine plot
// can be use for dstar and d0
// pt vs rap, 10(yaxis)  * 5 (xaxis)
// usage:root -l -b 'ptrapbinDmesoncombine.cc("<outName>w/o.pdf", "<fileName1>.root", "<fileName2>.root")'
// utk yaxis, dia akan ikut scale mana yg kita plot dl
// try utk plot tanpa axis
// root -l -b 'ptrapbinDmesoncombinev3.cc("ref2Dmassplot", "MuDhistos4_MC10_MBcharm_JSON5.root", "MuDhistos4_MC10_MBcharm_JSON5.root")'
// try guna second method: (follow ptrapbinDmesoncombinev3) instead follow Eff_calc_DDv6
// usage: root -l -b 'NsigDDv4.cc("aaaa", "new/MuDhistos4_MC10_MBcharm_JSON5.root")' // or NsigplotMC
// data: root -l -b 'NsigDDv4.cc("NsigplotData", "0BRAnMBRAnB.root")'
// version that added the calculation Nsignal
// same as v4 but for testing diff method
// root -l -b 'NsigDDv5.cc("Nsig66all", "multiData_JSON5.root")'
// root -l -b 'NsigDDv5.cc("Nsig66all_10mu2", "MuDhistostest2010_10mu2.root")'
// root -l -b 'NsigDDv5.cc("Nsig66all_13all_deltamr", "MuDhistostest2010_13all.root")'

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

//#include "/home/nuha/root/macros/tdrstyle.C"

using namespace std;

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
/*
// Parameters u want to include in your styling
void styleHist(TH1F* varHist, Float_t useCol, string ploTitle, Float_t yMin) {

  varHist->SetLineColor(useCol);
  varHist->SetTitle(ploTitle.c_str());
  varHist->SetMinimum(yMin);
  //varHist->GetYaxis()->SetRangeUser(yMin, varHist->GetMaximum());
}
*/
void styleHist(TH1F* varHist, Float_t useCol, Float_t yMin, Int_t filSty, Int_t marSty, Float_t marSiz, Float_t linWid, Float_t yOff, Float_t xOff, string ploTitle, string yTitle, string xTitle,  Float_t ylabSiz, Float_t xlabSiz, Float_t ySiz, Float_t xSiz, Int_t statHist, Int_t linSt/*, Float_t yMax, Float_t xmin, Float_t xmax*/) {

  varHist->SetLineColor(useCol);
  //varHist->SetTitle(ploTitle.c_str());
  varHist->SetMinimum(yMin);
  //varHist->GetYaxis()->SetRangeUser(yMin, varHist->GetMaximum());
   varHist->SetFillStyle(filSty);
  varHist->SetMarkerColor(useCol);
  varHist->SetMarkerStyle(marSty);
  varHist->SetMarkerSize(marSiz);
  varHist->SetLineColor(useCol);
  varHist->SetLineWidth(linWid);
  varHist->GetYaxis()->SetTitleOffset(yOff);
  varHist->GetXaxis()->SetTitleOffset(xOff);
  varHist->SetTitle(ploTitle.c_str());
  varHist->GetYaxis()->SetTitle(yTitle.c_str());
  varHist->GetXaxis()->SetTitle(xTitle.c_str());
  varHist->GetYaxis()->SetLabelSize(ylabSiz);
  varHist->GetXaxis()->SetLabelSize(xlabSiz);
  varHist->GetYaxis()->SetTitleSize(ySiz);
  varHist->GetXaxis()->SetTitleSize(xSiz);
  varHist->SetStats(statHist);  
  varHist->SetLineStyle(linSt);
  //varHist->SetMaximum(yMax);
  
  //varHist->GetXaxis()->SetRangeUser(xmin, xmax);  
}

void styleGraph(TGraphErrors* varGraph, Float_t useColor, Float_t colorAlpha, Int_t fillStyle, Int_t markStyle, Float_t markSize, Int_t lineStyle, Int_t lineWidth/*, Float_t yMin, Float_t yMax, Float_t xMin, Float_t xMax*/) {
  
  varGraph->SetFillColorAlpha(useColor, colorAlpha);
  varGraph->SetMarkerColor(useColor);
  varGraph->SetLineColor(useColor);
  varGraph->SetFillStyle(fillStyle);
  varGraph->SetMarkerStyle(markStyle);
  varGraph->SetMarkerSize(markSize);
  varGraph->SetLineStyle(lineStyle);
  varGraph->SetLineWidth(lineWidth);
  // for graphs histograms are just to draw the frame
  // if it has an error then that would draw a line at 0
  // at least until ROOT 6.14.02 this bug is there
  //varGraph->GetHistogram()->Sumw2(false);
  //varGraph->GetHistogram()->SetMinimum(yMin);
  //varGraph->GetHistogram()->SetMaximum(yMax);
  //varGraph->GetXaxis()->SetLimits(xMin, xMax);  
}

void styleGraph(TGraphAsymmErrors* varGraph, Float_t useColor, Float_t colorAlpha, Int_t fillStyle, Int_t markStyle, Float_t markSize, Int_t lineStyle, Int_t lineWidth/*, Float_t yMin, Float_t yMax, Float_t xMin, Float_t xMax*/) {

  varGraph->SetFillColorAlpha(useColor, colorAlpha);
  varGraph->SetMarkerColor(useColor);
  varGraph->SetLineColor(useColor);
  varGraph->SetFillStyle(fillStyle);
  varGraph->SetMarkerStyle(markStyle);
  varGraph->SetMarkerSize(markSize);
  varGraph->SetLineStyle(lineStyle);
  varGraph->SetLineWidth(lineWidth);
  // for graphs histograms are just to draw the frame
  // if it has an error then that would draw a line at 0
  // at least until ROOT 6.14.02 this bug is there
  //varGraph->GetHistogram()->Sumw2(false);
  //varGraph->GetHistogram()->SetMinimum(yMin);
  //varGraph->GetHistogram()->SetMaximum(yMax);
  //varGraph->GetXaxis()->SetLimits(xMin, xMax);  
}

// Legend Style
void styleLeg(TLegend* varLeg, Int_t fColor, Int_t borSiz, Int_t texFon, Float_t texSiz, Int_t bordSiz/*, Float_t nCol, string legHead*/) {
   varLeg->SetFillColor(fColor);
   varLeg->SetBorderSize(borSiz);
   varLeg->SetTextFont(texFon);
   varLeg->SetTextSize(texSiz);
   varLeg->SetBorderSize(bordSiz);
   //varLeg->SetNColumns(nCol);
   //varLeg->SetHeader(legHead.c_str());
}

// Drawing flow
void drawVar(TCanvas* varCan, Int_t iCan, TGraphAsymmErrors* varGraphSig, TGraphAsymmErrors* varGraphSide, TH1F* varHist1, TH1F* varHist2, string drawOpt1, string drawOpt2, string drawOpt3) {

  varCan->cd(iCan);
  varHist1->Draw(drawOpt1.c_str() );
  varGraphSig->Draw(drawOpt3.c_str());
  varGraphSide->Draw(drawOpt3.c_str());    
  varHist2->Draw(drawOpt2.c_str() );  
  varHist1->Draw(drawOpt2.c_str() );
}

// for separate plot 
//void ptrapbinDmesoncombine(const std::string &outName, const std::string &fileName1) {
// for comparison plot on top
void NsigDDv5(const std::string &outName, const std::string &fileName1) {

  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  
  // Max digit you want to put in the y axis
  TGaxis::SetMaxDigits(5);
  // Make sure uncertainty in histogram bins is calculated correctly
  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(false);
  
  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////// INPUT AND OUTPUT DIRECTORY /////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  // Input and output directory
  string inDir;
  string outDir;

  //inDir = "/home/zulaiha/PhD/Analysis/wow/TtoH/JSON5/";  
  //outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/";
  
  //inDir = "/home/zulaiha/PhD/Analysis/wow/TtoH/JSON5/310120/";
  //outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/66plots/310120/";
  
  inDir = "/home/zulaiha/PhD/Analysis/wow/TtoH/Achim/";
  
  //outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/testforAchim/";  
  //outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/table/";  
  //outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/table/data11all/";  
  //outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/table/data15JSON5/";  
  //outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/table/dataBParkAODall/";  
  outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/table/data13all/";  

  //TFile fout((outDir + "h2DNsigplot.root").c_str(),"RECREATE");
 
  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////// INPUT AND OUTPUT FILE NAME ////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  // Input files
  TFile *inFile = TFile::Open((inDir + fileName1).c_str());

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////// DECLARE THE HISTOGRAMS /////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  // x axis for background region
  // Before and after signal
  // We take region that is signal free  
  Float_t Axmin;
  Float_t Axmax;
  Float_t Bxmin;
  Float_t Bxmax;
  Float_t Cxmin;
  Float_t Cxmax;
  Float_t Dxmin;
  Float_t Dxmax;
  Float_t Exmin;
  Float_t Exmax;

  // Background bin
  // Before & after signal
  // Right charge and wrong charge
  Int_t b4_binx1r;
  Int_t b4_binx2r;
  Int_t b4_binx1w;
  Int_t b4_binx2w;
  Int_t after_binx1r;
  Int_t after_binx2r;
  Int_t after_binx1w;
  Int_t after_binx2w;
 
  // Background integral
  // Before, after and total
  Double_t Ainter[66], Aintew[66], Einter[66], Eintew[66], Cinter[66], Cintew[66], TOTinter[66], TOTintew[66], Scaleup[66];
  Double_t ErrAr[66], ErrAw[66], ErrEr[66], ErrEw[66], ErrCr[66], ErrCw[66];

  // Signal bin
  // Right charge and wrong charge
  Int_t Sigbinx1r;
  Int_t Sigbinx2r;
  Int_t Sigbinx1w;
  Int_t Sigbinx2w;
  
  // Signal integral
  // Before and after scale factor
  Int_t NSignal_aftersf1[66], NSignal_b4sf[66], NSignal_aftersf2[66];
  Int_t NRS[66], NWS_aftersf[66], uncertSig[66];
  
  // x axis for background region
  // Before and after signal
  // We take region that is signal free
  // A == before signal
    // A region ---> side band region before signal
    Axmin = 0.;
    Axmax = 0.14248; 
    // B region ---> region that we don't want
    Bxmin = 0.14248; 
    Bxmax = 0.1444; 
    // C region ---> signal region
    // x axis for signal region
    // We take region that has more signal/background ratio
    Cxmin = 0.1444; 
    Cxmax = 0.14664;  
    // D region ---> region that we don't want
    Dxmin = 0.14664; 
    Dxmax = 0.1492; 
    // E region ---> side band region after signal
    Exmin = 0.1492;
    Exmax = 0.1652;
    /*
    // deltam
    // A region ---> side band region before signal
    Axmin = 0.;
    Axmax = 0.14216;
    // B region ---> region that we don't want
    Bxmin = 0.14216; 
    Bxmax = 0.14408; 
    // C region ---> signal region
    // x axis for signal region
    // We take region that has more signal/background ratio
    Cxmin = 0.14408; 
    Cxmax = 0.14696; 
    // D region ---> region that we don't want
    Dxmin = 0.14696; 
    Dxmax = 0.15016;
    // E region ---> side band region after signal
    Exmin = 0.15016; 
    Exmax = 0.17; 
    // both A and E regions are use to scale wrong charge to right charge to get SF
    */
  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////// END OF DECLARING HISTOGRAMS ///////// //////////////////
  ////////////////////////////////////////////////////////////////////////////////

  //string Varhist1 = "hc_Dstar_deltamr_ptyr";
  //string Varhist2 = "hc_Dstar_deltam_ptyr";  
  string Varhist1 = "hc_Dstar_deltamr_ptyr";
  string Varhist2 = "hc_Dstar_deltamr_ptyw";
  //string Varhist1 = "hc_D0ptyr";
  //string Varhist2 = "hc_D0ptyr";
  //string Varhist2 = "hc_Dstar_deltamr_ptyw";

  //deltam
  //string Varhist1 = "hc_Dstar_deltam_ptyr";
  //string Varhist2 = "hc_Dstar_deltam_ptyw";
    
  //Float_t Colhist1 = kBlue;
  //Float_t Colhist2 = kRed;

  // no scale: 1.
  //Float_t Scaleup = 1.0;
  
  TH1F *hAptrapr[66];
  TH1F *hAptrapw[66];

  TCanvas *c1;
  c1 = new TCanvas("c1", "c1", 200, 10, 1000, 1300);
  c1->Divide(5,10); //(x,y)
  // if full (uncomment)
  //c1->Divide(6,11); //(x,y)

  // style Legend
  TLegend *stdL0 = new TLegend(0.1, 0.96, 0.99, .98); // size of legend for lower pt, hlptr
  
  int bolehke;
  std::vector<int> vecbinr[66], vecbinw[66];
  //std::unique_ptr<TGraphErrors[]> g_gri = std::make_unique<TGraphErrors[]>(5);
  auto g_gri = std::make_unique<TGraphErrors>(6);
    
  // that means point 0 has x = 0.142, y = -1
  g_gri->SetPoint(0, Axmax, 0.);
  g_gri->SetPoint(1, Cxmin, 0.);
  g_gri->SetPoint(2, Cxmax, 0.);
  g_gri->SetPoint(3, Exmin, 0.);
  g_gri->SetPoint(4, Exmax, 0.);
  g_gri->SetPoint(5, -1., 0.);
    
  // error x low, error x high
  //for (auto &iP : {0, 1, 2, 3})
  for (auto &iP : {0, 1, 2, 3, 4}) //ubahshade
    
    //g_gri->SetPointError(iP, 1000., 1000., 1000., 1000.);
    {g_gri->SetPointError(iP, 0., 10000000.);} // error x and error y for point iP
  //g_gri->SetPointError(4, 100000., 0.);
  styleGraph(g_gri.get(), kBlack, 1., 0, 0, 1.5, 4, 1);
    
  // make a background shade for this region
  // using tgraphasymmerror
  auto shade_SideBand = std::make_unique<TGraphAsymmErrors>(2); // ade dua graf_asymmerror
  shade_SideBand->SetName("shade_SideBand");
  // point for after signal
  shade_SideBand->SetPoint(0, 0.155, 100); // 1st index, x, y // x n y can be any point
  // point for before signal
  shade_SideBand->SetPoint(1, 0.14, 100); // 2nd index, x, y
  // point error for after signal
  // errxlow = 0.16 - 0.15, errxhigh = 0.26 - 0.16
  shade_SideBand->SetPointError(0, (0.155 - Exmin), (Exmax - 0.155), 200., 20000000.); // index, errxlow, errxhigh, errylow, erryhigh
  // point error for before signal
  shade_SideBand->SetPointError(1, (0.14 - Axmin), (Axmax - 0.14), 200., 20000000.); // index, errxlow, errxhigh, errylow, erryhigh  
  styleGraph(shade_SideBand.get(), kGray +2, 0.5, 1001, 0, 0, 1, 1); // 3001 for fill full

  // make a signal shade for this region
  // using tgraphasymmerror
  auto shade_Sig = std::make_unique<TGraphAsymmErrors>(1);
  shade_Sig->SetName("shade_Sig");
  shade_Sig->SetPoint(0, 0.145, 100); // index, x, y // index 0 sbb da first graph
  shade_Sig->SetPointError(0, (0.145 - Cxmin), (Cxmax - 0.145), 200., 20000000.); // index, errxlow, errxhigh, errylow, erryhigh
  styleGraph(shade_Sig.get(), kPink +9, 0.4, 1001, 0, 0, 1, 1); // 3001 for fill full  

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////// Loop over the range ////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////

  // Get all the 66 histograms (start dr 0 sampai 65)
  for (int range = 0; range < 66; range++) {

    //cout << "range b4: " << range << endl;
    
    // This method is really for our range. remove part yg xnk
    // drp 66 jd 50. Buang knn skali(0-11) & atas skali(0-5)
    // if full (comment)
    const Bool_t xnak = (range != 0) && (range != 1) && (range != 2) && (range != 3) && (range != 4) && (range != 5) && (range != 11) && (range != 17) && (range != 23) && (range != 29) && (range != 35) && (range != 41) && (range != 47) && (range != 53) && (range != 59) && (range != 65);
      
    // if full (comment)
    if (!xnak) continue;
    
    hAptrapr[range] = (TH1F *) inFile->Get((Varhist1 + toStr(range)).c_str())->Clone("xxx");
    hAptrapw[range] = (TH1F *) inFile->Get((Varhist2 + toStr(range)).c_str())->Clone("yyy");

    //hAptrapw[range]->Scale(Scaleup);

    cout << "rangeafter: " << range << endl;

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////// Rebin //////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  // Optional
    
  std::cout << "" << std::endl;
  std::cout << "#bin, binlowedge, bincontent before rebin" << std::endl;  
  for (int iBin = 1; iBin <= hAptrapr[range]->GetNbinsX(); ++iBin) {
    std::cout << iBin << " " << hAptrapr[range]->GetBinLowEdge(iBin) << " " << hAptrapr[range]->GetBinContent(iBin) << std::endl;}
  /*
  hAptrapr[range]->Rebin(2);
  hAptrapw[range]->Rebin(2);
  
  std::cout << "" << std::endl;
  std::cout << "#bin, binlowedge, bincontent after rebin" << std::endl;  
  for (int iBin = 1; iBin <= hAptrapr[range]->GetNbinsX(); ++iBin) {
    std::cout << iBin << " " << hAptrapr[range]->GetBinLowEdge(iBin) << " " << hAptrapr[range]->GetBinContent(iBin) << std::endl;}
    */
  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////// Rebin end //////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////  

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////// MACHINERY. DO NOT TOUCH! ///////////////////////////
  ////////////////////////////////////////////////////////////////////////////////

  const double binwid = hAptrapr[range]->GetBinLowEdge(2) - hAptrapr[range]->GetBinLowEdge(1);
  cout << "binwidth: " << binwid << endl;
    
  vecbinr[range].push_back(hAptrapr[range]->GetXaxis()->FindBin(Axmin + (0.5 * binwid)));  
  vecbinr[range].push_back(hAptrapr[range]->GetXaxis()->FindBin(Axmax - (0.5 * binwid)));
  vecbinr[range].push_back(hAptrapr[range]->GetXaxis()->FindBin(Bxmin + (0.5 * binwid)));  
  vecbinr[range].push_back(hAptrapr[range]->GetXaxis()->FindBin(Bxmax - (0.5 * binwid)));  
  vecbinr[range].push_back(hAptrapr[range]->GetXaxis()->FindBin(Cxmin + (0.5 * binwid)));
  vecbinr[range].push_back(hAptrapr[range]->GetXaxis()->FindBin(Cxmax - (0.5 * binwid)));
  vecbinr[range].push_back(hAptrapr[range]->GetXaxis()->FindBin(Dxmin + (0.5 * binwid)));  
  vecbinr[range].push_back(hAptrapr[range]->GetXaxis()->FindBin(Dxmax - (0.5 * binwid)));  
  vecbinr[range].push_back(hAptrapr[range]->GetXaxis()->FindBin(Exmin + (0.5 * binwid)));
  vecbinr[range].push_back(hAptrapr[range]->GetXaxis()->FindBin(Exmax - (0.5 * binwid)));

  vecbinw[range].push_back(hAptrapw[range]->GetXaxis()->FindBin(Axmin + (0.5 * binwid)));  
  vecbinw[range].push_back(hAptrapw[range]->GetXaxis()->FindBin(Axmax - (0.5 * binwid)));
  vecbinw[range].push_back(hAptrapw[range]->GetXaxis()->FindBin(Bxmin + (0.5 * binwid)));  
  vecbinw[range].push_back(hAptrapw[range]->GetXaxis()->FindBin(Bxmax - (0.5 * binwid)));  
  vecbinw[range].push_back(hAptrapw[range]->GetXaxis()->FindBin(Cxmin + (0.5 * binwid)));
  vecbinw[range].push_back(hAptrapw[range]->GetXaxis()->FindBin(Cxmax - (0.5 * binwid)));
  vecbinw[range].push_back(hAptrapw[range]->GetXaxis()->FindBin(Dxmin + (0.5 * binwid)));  
  vecbinw[range].push_back(hAptrapw[range]->GetXaxis()->FindBin(Dxmax - (0.5 * binwid)));  
  vecbinw[range].push_back(hAptrapw[range]->GetXaxis()->FindBin(Exmin + (0.5 * binwid)));
  vecbinw[range].push_back(hAptrapw[range]->GetXaxis()->FindBin(Exmax - (0.5 * binwid)));

  for (int i = 0; i < vecbinr[range].size(); ++i){ // xkisah vecbinr or w sbb size dia sama je
    //std::cout << vecbinr.at(i) << " " << vecbinw.at(i) << endl; // it should be da same
  
    int num_bxmax = std::count(vecbinr[range].begin(), vecbinr[range].end(), vecbinr[range].at(i));
    int num_bxmaxw = std::count(vecbinw[range].begin(), vecbinw[range].end(), vecbinw[range].at(i));
    
    //std::cout << "rbefore: " << vecbinr.at(i) << " " << num_bxmax << endl;
    //std::cout << "wbefore: " << vecbinw.at(i) << " " << num_bxmaxw << endl;
    
    if (num_bxmax == 2) {
      vecbinr[range].at(i) = vecbinr[range].at(i) -1;
      vecbinw[range].at(i) = vecbinw[range].at(i) -1;      
    }
  }

  // Print out the values for checking
  cout << "*******************************************************************" << endl;
  cout << "Print out bin index for this x axis" << endl;
  cout << "*******************************************************************" << endl;
  cout << "Left side band (Region A):" << endl;
  cout << "------------------" << endl;
  cout << "Abinmin = " << vecbinr[range].at(0) << " " << "Abinmax = " << vecbinr[range].at(1) << endl;
  cout << "Unwanted band (Region B):" << endl;
  cout << "------------------" << endl;
  cout << "Bbinmin = " << vecbinr[range].at(2) << " " << "Bbinmax = " << vecbinr[range].at(3) << endl;  
  cout << "Signal band (Region C):" << endl;
  cout << "------------------" << endl;
  cout << "Cbinmin = " << vecbinr[range].at(4) << " " << "Cbinmax = " << vecbinr[range].at(5) << endl;
  cout << "Unwanted band (Region D):" << endl;
  cout << "------------------" << endl;
  cout << "Dbinmin = " << vecbinr[range].at(6) << " " << "Dbinmax = " << vecbinr[range].at(7) << endl;
  cout << "Right side band (Region E):" << endl;
  cout << "-----------------" << endl;
  cout << "Ebinmin =  " << vecbinr[range].at(8) << " " << "Ebinmax =  " << vecbinr[range].at(9) << endl;  
  cout << "*******************************************************************" << endl;
  
  Ainter[range] = hAptrapr[range]->IntegralAndError(vecbinr[range].at(0), vecbinr[range].at(1), ErrAr[range]);
  Aintew[range] = hAptrapw[range]->IntegralAndError(vecbinw[range].at(0), vecbinw[range].at(1), ErrAw[range]);
  Cinter[range] = hAptrapr[range]->IntegralAndError(vecbinr[range].at(4), vecbinr[range].at(5), ErrCr[range]);
  Cintew[range] = hAptrapw[range]->IntegralAndError(vecbinw[range].at(4), vecbinw[range].at(5), ErrCw[range]);
  Einter[range] = hAptrapr[range]->IntegralAndError(vecbinr[range].at(8), vecbinr[range].at(9), ErrEr[range]);
  Eintew[range] = hAptrapw[range]->IntegralAndError(vecbinw[range].at(8), vecbinw[range].at(9), ErrEw[range]);

  // to check venbinr and vecbinw should be the same
  //cout << "vecbinr = " << vecbinr[range].at(5) << " " << "vecbinw = " << vecbinw[range].at(5) << endl;
  
  TOTinter[range] = Ainter[range] + Einter[range];
  TOTintew[range] = Aintew[range] + Eintew[range];
  Scaleup[range] = TOTinter[range] / TOTintew[range];

  // Signal integral
  // before apply scale factor
  NSignal_b4sf[range] = (hAptrapr[range]->IntegralAndError(vecbinr[range].at(4), vecbinr[range].at(5), ErrCr[range]) ) - (hAptrapw[range]->IntegralAndError(vecbinr[range].at(4), vecbinr[range].at(5), ErrCw[range]) );

  // no scale: 1.
  hAptrapw[range]->Scale(Scaleup[range]);

  // after apply scale factor
  NSignal_aftersf1[range] = hAptrapr[range]->IntegralAndError(vecbinr[range].at(4), vecbinr[range].at(5), ErrCr[range]) - hAptrapw[range]->IntegralAndError(vecbinr[range].at(4), vecbinr[range].at(5), ErrCw[range]);

  // check nsignal before and after normalization
  cout << "Nsigb4 = " << NSignal_b4sf[range] << "Nsigafter = " << NSignal_aftersf1[range] << endl;
  
  NRS[range] = hAptrapr[range]->IntegralAndError(vecbinr[range].at(4), vecbinr[range].at(5), ErrCr[range]);
  NWS_aftersf[range] = hAptrapw[range]->IntegralAndError(vecbinr[range].at(4), vecbinr[range].at(5), ErrCw[range]);

  uncertSig[range] = sqrt((NRS[range] + NWS_aftersf[range])); // assuming both are poisson stat.

  cout << " " << endl;
  cout << "Total Entries of side band (l+r) before scaleup range: " << range << endl;
  cout << "------------------------------------------------" << endl;
  cout << "right charge = " << TOTinter[range] << " " << "wrong charge = " << TOTintew[range] << " " <<
    "Sf = " << Scaleup[range] << endl;
  cout << "Entries of signal b4 and after SF" << endl;
  cout << "----------------------------------" << endl;  
  cout << "NSignalb4Sf = " << NSignal_b4sf[range] << " " << "NSignal_afterSf = " << " " << NSignal_aftersf1[range] << " " << "NRS = " << NRS[range] << " " << "NWS_aftersf = " << NWS_aftersf[range] << " " << "uncertSig = " << uncertSig[range] << endl;  
  
    // if full (comment)
    // method ensure the range and canvas correlate
    if (range >= 6 && range <= 10) {bolehke = range -5;}
    else if (range >= 12 && range <= 16) {bolehke = range -6;}
    else if (range >= 18 && range <= 22) {bolehke = range -7;}
    else if (range >= 24 && range <= 28) {bolehke = range -8;}
    else if (range >= 30 && range <= 34) {bolehke = range -9;}
    else if (range >= 36 && range <= 40) {bolehke = range -10;}
    else if (range >= 42 && range <= 46) {bolehke = range -11;}
    else if (range >= 48 && range <= 52) {bolehke = range -12;}
    else if (range >= 54 && range <= 58) {bolehke = range -13;}
    else if (range >= 60 && range <= 64) {bolehke = range -14;}
  
    //styleHist(hAptrapr[range], Colhist1, "", -0.999);
    //styleHist(hAptrapw[range], Colhist2, "", -0.999);

    styleHist(hAptrapr[range], kBlue, -0.999, 0, 20, 0.5, 2., 1.1, 1., "", "", "m_{K#pi#pi_{s}} - m_{K#pi} (GeV)", 0.04, 0.04, 0.05, 0.05, 0, 1); // data 3520

    styleHist(hAptrapw[range], kRed, -0.999, 0, 20, 0.5, 2., 1.1, 1., "", "", "m_{K#pi#pi_{s}} - m_{K#pi} (GeV)", 0.04, 0.04, 0.05, 0.05, 0, 1); // for deltam vs deltamr, data 3520  

    /*
    stdL0->SetNColumns(4);  
    stdL0->AddEntry(hAptrapr[range], "right charge", "pl");
    stdL0->AddEntry(hAptrapw[range], "wrong charge", "l"); // if substract
    stdL0->AddEntry(shade_SideBand.get(), "side band", "f"); // if substract
    stdL0->AddEntry(shade_Sig.get(), "signal band", "f"); // if substract
    styleLeg(stdL0, 0, 0, 42, 0.03, 0);
    */
    //shade_SideBand->Draw("02"); // if substract
    //shade_Sig->Draw("02"); // if substract    
    drawVar(c1, bolehke, shade_Sig.get(), shade_SideBand.get(), hAptrapr[range], hAptrapw[range], "axis", "hist same", "02");
    // if full (uncomment)
    //drawVar(c1, range +1, hAptrapr[range], hAptrapw[range], "axis", "hist same");
    g_gri->Draw("0z same");

    //stdL0->Draw(); // leg kene draw kat the latest overlap

  int decNerr[range], decN[range];
  
  if (uncertSig[range] >= 1. and uncertSig[range] < 10.) {
    decNerr[range] = 2;
    if (NSignal_aftersf1[range] >= 1. and NSignal_aftersf1[range] <= 10.) {
      decN[range] = 2;
    }    
    else if (NSignal_aftersf1[range] >= 10. and NSignal_aftersf1[range] <= 99.) {
      decN[range] = 3;
    }
    else if (NSignal_aftersf1[range] >= 100. and NSignal_aftersf1[range] <= 999.) {
      decN[range] = 4;
    }
    else if (NSignal_aftersf1[range] >= 1000. and NSignal_aftersf1[range] <= 9999.) {
      decN[range] = 5;
    }
  }
  
  else if (uncertSig[range] >= 10. and uncertSig[range] < 100.) {
    decNerr[range] = 2;
    if (NSignal_aftersf1[range] >= 1. and NSignal_aftersf1[range] <= 9.) {
      decN[range] = 1;
    }    
    else if (NSignal_aftersf1[range] >= 10. and NSignal_aftersf1[range] <= 99.) {
      decN[range] = 2;
    }
    else if (NSignal_aftersf1[range] >= 100. and NSignal_aftersf1[range] <= 999.) {
      decN[range] = 3;
    }
    else if (NSignal_aftersf1[range] >= 1000. and NSignal_aftersf1[range] <= 9999.) {
      decN[range] = 4;
    }
  }

  else if (uncertSig[range] >= 100. and uncertSig[range] < 1000.) {
    decNerr[range] = 3;
    if (NSignal_aftersf1[range] >= 1. and NSignal_aftersf1[range] <= 9.) {
      decN[range] = 1;
    }    
    else if (NSignal_aftersf1[range] >= 10. and NSignal_aftersf1[range] <= 99.) {
      decN[range] = 2;
    }
    else if (NSignal_aftersf1[range] >= 100. and NSignal_aftersf1[range] <= 999.) {
      decN[range] = 3;
    }
    else if (NSignal_aftersf1[range] >= 1000. and NSignal_aftersf1[range] <= 9999.) {
      decN[range] = 4;
    }
  }  
  else {decNerr[range] = 2; decN[range] = 2;}
    
  const std::string N = "N(D*^{#pm}): " + toStr(NSignal_aftersf1[range], decN[range]) + " #pm " + toStr(uncertSig[range], decNerr[range]);
  
  TLatex *txt1 = new TLatex();
  txt1->SetTextSize(0.04);
  txt1->SetNDC();
  txt1->SetTextFont(42);
  txt1->DrawLatex(0.5, 0.8, N.c_str());

  //fout.cd();
  //hAptrapr[range]->Write();
  //hAptrapw[range]->Write();
    
    //cout << "range after : " << range +1 << endl;
  }// end of loop range



  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// END OF STYLING ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////

  c1->SaveAs((outDir + outName + ".pdf").c_str());
  c1->SaveAs((outDir + outName + ".root").c_str());
  c1->Close();

  gROOT->ProcessLine(".q");
  
}

// reference how u push back vector and call the element
  /*
  std::vector<int> v_Canrange;

    for (Int_t ayoyo = 1; ayoyo < 51; ayoyo++) {
      v_Canrange.push_back(ayoyo);
      //cout << ayoyo << endl;
    }
    
    for (Int_t i = 1; i < v_Canrange.size() +1; ++i) {
      //cout << "ayoyo: " << i << endl;
    }
  */
