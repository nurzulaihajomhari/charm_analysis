// put all the styling options here
// this is central file for styling histograms
// ACHTUNG!: kalau ubah args dlm ni, dia effect hok yg lain jugok! (u dont have to know)
// More information of options available for histograms:
   // TColor: https://root.cern.ch/doc/master/classTColor.html
   // TAxis: https://root.cern.ch/doc/master/classTAxis.html
   // TLegend: https://root.cern.ch/doc/master/classTLegend.html
   // TH1: https://root.cern.ch/doc/master/classTH1.html
   // THistPainter (for draw option): https://root.cern/doc/master/classTHistPainter.html
   // TStyle: https://root.cern.ch/doc/master/classTStyle.html

// to make sure bila panggil a drp b
#ifndef PLOTUTIL_H
#define PLOTUTIL_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
//#include <stdlib>
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
#include "TH2D.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
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
#include "TPaletteAxis.h"
#include "TEfficiency.h"
#include "TF1.h"
#include "TFitResult.h"
//#include "/home/nuha/root/macros/tdrstyle.C"

using namespace std;

// Legend Style
void styleLeg(TLegend* varLeg, Int_t fColor, Int_t borSiz, Int_t texFon, Float_t texSiz, Int_t bordSize, Int_t filSty/*, Float_t nCol, string legHead*/) {
   varLeg->SetFillColor(fColor);
   varLeg->SetBorderSize(borSiz);
   varLeg->SetTextFont(texFon);
   varLeg->SetTextSize(texSiz);
   varLeg->SetBorderSize(bordSize);
   varLeg->SetFillStyle(filSty);   
   //varLeg->SetNColumns(nCol);
   //varLeg->SetHeader(legHead.c_str());
}

// Canvas Style
void styleCan(TCanvas* varCan, Float_t tMarg, Float_t bMarg, Float_t lMarg, Float_t rMarg, Int_t logy, Int_t logx) {
  varCan->SetTopMargin(tMarg);
  varCan->SetBottomMargin(bMarg);
  varCan->SetLeftMargin(lMarg);
  varCan->SetRightMargin(rMarg);
  varCan->SetLogy(logy);
  varCan->SetLogx(logx);  
}

// pad Style
void stylePad(TPad* varPad, Float_t tMarg, Float_t bMarg, Float_t lMarg, Float_t rMarg, Int_t logy, Int_t logx) {
  varPad->SetTopMargin(tMarg);
  varPad->SetBottomMargin(bMarg);
  varPad->SetLeftMargin(lMarg);
  varPad->SetRightMargin(rMarg);
  varPad->SetLogy(logy);
  varPad->SetLogx(logx);  
}

// graphstyle
// if u want to have styleGraph but have asymm n biase, pki template 
// can be also TGraphAsymmErrors
void styleGraph(TGraphErrors* varGraph, Float_t useColor, Float_t colorAlpha, Float_t fillStyle, Float_t markStyle, Float_t markSize, Float_t lineStyle, Float_t lineWidth/*, Float_t yMin, Float_t yMax, Float_t xMin, Float_t xMax*/) {
  
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

// histogram style
//template <typename Plot>
// Parameters u want to include in your styling
void styleHist(TH1* varHist, Float_t useCol, Float_t filSty, Float_t marSty, Float_t marSiz, Float_t linWid, Float_t yOff, Float_t xOff, string ploTitle, string yTitle, string xTitle,  Float_t ylabSiz, Float_t xlabSiz, Float_t yTitSiz, Float_t xTitSiz, Float_t statHist, Float_t linSt, Float_t yMin, Float_t yMax) {

  //varHist->SetFillColorAlpha(useCol, colorAlpha);
  varHist->SetLineColor(useCol);
  //varHist->SetTitle(ploTitle.c_str());
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
  varHist->GetYaxis()->SetTitleSize(yTitSiz);
  varHist->GetXaxis()->SetTitleSize(xTitSiz);
  varHist->SetStats(statHist);  
  varHist->SetLineStyle(linSt);
  //varHist->SetMaximum(yMax);
  //varHist->SetMinimum(yMin);
  // kalau xnk customize ymin n ymax, put ymin = ymax, otherwise:
  if (yMin < yMax) {
  varHist->GetYaxis()->SetRangeUser(yMin, yMax);
  }     
  //varHist->GetXaxis()->SetRangeUser(xmin, xmax);  
}

// palette style for 2D histograms 
void stylePal(TH2D* varHist, TCanvas* varCan, Float_t x1, Float_t x2, Float_t y1, Float_t y2) {

  TPaletteAxis *allpallete;  
  allpallete = (TPaletteAxis*) varHist->GetListOfFunctions()->FindObject("palette");
  allpallete->SetX1NDC(x1);
  allpallete->SetX2NDC(x2);
  allpallete->SetY1NDC(y1);
  allpallete->SetY2NDC(y2);
}

// canvas/output save in pdf
void drawCan(TCanvas* varCan, string outfile, string outDir) {
  varCan->SaveAs((outDir + outfile + ".pdf").c_str() );
  varCan->Close();
}

// Hist2D style
void styleHist2D(TH2D* varHist, Float_t zMin, Float_t zMax, string ploTitle, string xTitle, string yTitle, Float_t markSize, Float_t yMin, Float_t yMax, Float_t xMin, Float_t xMax, Int_t useCol, Float_t yOff, Float_t xOff, string zTitle) {
  // don't want to customize da z range
  if (zMin <    zMax) {
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
  varHist->GetZaxis()->SetTitle(zTitle.c_str());
  
  gStyle->SetOptStat(0);
  // put #0 in 0bincontent
  gStyle->SetHistMinimumZero();
}

// histogram draw and canvas update after 2Dhistogram draw
void drawVar(TCanvas* varCan, TH2D* varHist, string drawOpt) {

  varCan->cd();  
  varHist->Draw(drawOpt.c_str() );  
  varCan->Update();
  /*
  TPaletteAxis *allpallete;  
  allpallete = (TPaletteAxis*) varHist->GetListOfFunctions()->FindObject("palette");
  allpallete->SetX1NDC(0.905);
  allpallete->SetX2NDC(0.935);
  allpallete->SetY1NDC(0.1);
  allpallete->SetY2NDC(0.9);
  */
}

void drawVar50Plot(TCanvas* varCan, Int_t iCan, TGraphAsymmErrors* varGraphSig, TGraphAsymmErrors* varGraphSide, TH1F* varHist1, TH1F* varHist2, string drawOpt1, string drawOpt2, string drawOpt3) {

  varCan->cd(iCan);
  varHist1->Draw(drawOpt1.c_str() );
  varGraphSig->Draw(drawOpt3.c_str());
  varGraphSide->Draw(drawOpt3.c_str());    
  varHist2->Draw(drawOpt2.c_str() );  
  varHist1->Draw(drawOpt2.c_str() );
}

void styleGraphPhase(TGraphAsymmErrors* varGraph, Float_t useColor, Int_t lineStyle, Int_t lineWidth/*, Float_t yMin, Float_t yMax, Float_t xMin, Float_t xMax*/) {

  varGraph->SetLineColor(useColor);
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


#endif
