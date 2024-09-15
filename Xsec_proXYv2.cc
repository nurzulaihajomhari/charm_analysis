// Code use to plot cross section afo pT
// for single(with ratio) and double differential plot
// usage:root -l 'Xsec_proXYv2b.cc("testratio", "", "h2DXsec_Dstar.root", 4)' to check satu2
// usage: for iNum in `seq 0 5`; do root -l -b 'Xsec_proXYv2b.cc("XDstpT'${iNum}'", "", "h2DXsec_Dstar.root", '${iNum}')'; done  to plot all of them including comb
// for iNum in `seq 0 5`; do root -l -b 'Xsec_proXYv2b.cc("XDstpT10mu_'${iNum}'", "", "h2DXsec_10mu_Dstar.root", '${iNum}')'; done
// include FONLL
// add ratio plot
//for iNum in `seq 0 5`; do root -l -b 'Xsec_proXYv2baratnew.cc("XDstpT10all_final_deltamr_charm_'${iNum}'", "", "h2DXsec_10all_final_deltamr_charm_Dstar.root", '${iNum}')'; done
// for iNum in `seq 0 5`; do root -l -b 'Xsec_proXYv2baratnew.cc("XDstpT10all_final_deltam_charm_'${iNum}'", "", "h2DXsec_10all_final_deltam_charm_Dstar.root", '${iNum}')'; done
// added another pythia prediction
// for iNum in `seq 0 5`; do root -l -b 'Xsec_proXYv2baratnewv1.cc("XDstpT10all_final_deltamrt_beauty_'${iNum}'", "", "h2DXsec_10all_final_deltamr_D0_Dstar.root", '${iNum}')'; done
// for iNum in `seq 0 5`; do root -l -b 'Xsec_proXYv2baratnewv1.cc("XDstpT10all_final_deltamr_semitight6_'${iNum}'", "", "h2DXsec_11all_deltamr_D0Kpi_Dstar.root", '${iNum}')'; done

// for iNum in `seq 0 5`; do root -l -b 'Xsec_proXYv2baratnewv1.cc("XDstpTdata15JSON5_deltamr_split2_'${iNum}'", "", "h2DXsec_data15JSON5_deltamr_D0Kpi_Dstar.root", '${iNum}')'; done
// for iNum in `seq 0 5`; do root -l -b 'Xsec_proXYv2baratnewv1Jambo.cc("XDstpT10all_final_deltamr_semitight4_'${iNum}'", "", "h2DXsec_10all_final_deltamr_D0_Dstar.root", '${iNum}')'; done
// for iNum in `seq 0 5`; do root -l -b 'Xsec_proXYv2baratnewv1Jambo.cc("XDstpT10all_final_deltamr_semitight4_'${iNum}'", "", "h2DXsec_10all_final_deltamr_D0_Dstar.root", '${iNum}')'; done
//for iNum in 3; do root -l -b 'Xsec_proXYv2baratnewv1Jambo.cc("XDstpT13all_deltamr_beauty5_'${iNum}'", "", "h2DXsec_data13all_deltamr_D0Kpi_beauty5_Dstar.root", '${iNum}')'; done
//for iNum in 0; do root -l -b 'Xsec_proXYv2baratnewv1Jambo.cc("XDstpT13all_deltamr_beauty7_'${iNum}'", "", "h2DXsec_13all_deltamr_D0Kpi_beauty7_Dstar.root", '${iNum}')'; done
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
#include "/home/zulaiha/PhD/Analysis/wow/Xsec/eachpT/PlotUtil.h"

// method to convert number become string
template <typename Number> std::string toStr(Number inNo, const int prec = -1, const bool fixed = false) {
  std::ostringstream outStr;
  if (fixed)
    outStr << std::fixed;
  if (prec > 0)
    outStr << std::setprecision(prec);

  outStr << inNo;
  return outStr.str();
}

void Xsec_proXYv2baratnewv1Jambo(const std::string &outNamepT, const std::string &outNamey, const std::string &fileName, const int num/*, const std::string &fileName1*/) { // h2DXsec_Dstar.root
  
  // don't draw the stat box
  gStyle->SetOptStat(0);
  // to include the tick atas dan kanan
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  //gPad->SetLogy(1);
  
  // Max digit you want to put in the y axis e.g: value 300, letak 3 x10^2 for max 1
  TGaxis::SetMaxDigits(4);
  // Make sure uncertainty in histogram bins is calculated correctly
  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(false);

  // directory of your input file
  // input dir utk ALICE N LHCb
  string inDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/eachpT/";
  // directory of your output file
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/eachpT/individual/";
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/eachpT/individual/FONLL/";
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/afopT/";
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/pT/";
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/pT/new/";
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/pT/beauty42/";
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/pT/semitight4/new/";
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/pT/semitight4/compare_mrt/";
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/pT/semitight4/compare_charm/";
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/pT/11all_semitight6/";
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/pT/data15JSON5_split2/";
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/pT/semitight4/usethis/Jamboree/";
  
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/pT/0BMB_13_beauty5/";
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/pT/13all_beauty5/nurcharm/";

  string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/pT/13all_beauty7/nurcharm/";
  // directory of your input file
  //string inDir2 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/testforAchim/Xsec/";
  //string inDir2 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/";
  //string inDir2 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/new/";
  //string inDir2 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/10all_final/";
  //string inDir2 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/11all_semitight6/";
  //string inDir2 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/data15JSON5_split2/";
  //string inDir2 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/0BMB_13_beauty5_dEdxyz2/";
  //string inDir2 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/13all_beauty5_dEdxyz2/";
  string inDir2 = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/newformat/XS/13all_beauty7_dEdxyz2/";
  
  // directory of your output file
  //string outDir = "/home/zulaiha/PhD/Analysis/wow/Xsec/Nsignal/testforAchim/Xsec/pT/";
  
  auto inFile = std::unique_ptr<TFile>(TFile::Open( (inDir2 + fileName).c_str() ));

  //####################################################################################//
  // Draw the cross sections as a function of pT for each rapidity    START             //
  // This is along y axis = ProjectionY                                                 //
  //####################################################################################//

  //////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////// Variant variables Start //////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////
  
  //$$$$$$$$$$$$$$$$$$$$$ Scale Factors $$$$$$$$$$$$$$$$$$$$$$$$$$$//
  // multiply by 2 to take into acc also for D*-  
  const double SFALpT = 2.;
  // multiply by 2 to get abs rap  
  const double SFLHpT = 2.;
  // normalized the MC to Data (try value mane yg close dgn data points)  
  const double SFforPy = 0.7;  
  const double SFPypT = (1/(20370. * 0.0267)) * SFforPy;
  const double SFPypTmcc = (1/(20370. * 0.0267)) * SFforPy; // for D0pi
  const double SFPypTmcb = (1/(20370. * 0.0267)) * SFforPy;

  //const double SFPypTmcc = (1/(3030.)) * SFforPy; // for charm MC  
  /*
  // for 5 TeV MC 40.4nb-1
  const double SFforPy = 1;  
  const double SFPypT = (1/(40400. * 0.0267)) * SFforPy;
  const double SFPypTmcc = (1/(40400. * 0.0267)) * SFforPy; // for D0pi
  const double SFPypTmcb = (1/(40400. * 0.0267)) * SFforPy;
  */
  //const double SFPypTmcc = (1/(3030. * 0.0267))* SFforPy;
  //const double SFPypTmcb = (1/(3640. * 0.0267))* SFforPy;
  
  //const double SFPypT = 1;  
  // Scale to avoid overlap
  const double SFCombpT0 = 1.e9; 
  const double SFCombpT0p5 = 1.e7; 
  const double SFCombpT1 = 1.e5; 
  const double SFCombpT1p5 = 1.e3; 
  const double SFCombpT2 = 1.e1; 
  //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//
  
  // Pythia
  const float useColPy= kRed,
    filStyPy= 0,
    marStyPy= 20,
    marSizPy= 2.3,
    linWidPy= 4.,
    yOffPy= 1.1,
    xOffPy= 1.,
    ylabSizPy= 0.06,
    xlabSizPy= 0.04,
    yTitSizPy= 0.06,
    xTitSizPy= 0.05,
    statHistPy= 0,
    linStPy= 1,
    linStmcc= 7,
    linStmcb= 8,    
    //yMinPy= 0.0699999,
    yMinPy= 0.011111,
    //yMinPy= -10.,

    yMaxPy = 1000.;
      
  const string ploTitlePy = "",
    yTitlePy = "#frac{d#sigma}{dp_{T}} [#frac{ub}{GeV}]",
    xTitlePy = "p_{T}(D*^{#pm}) [GeV]";
  // ALICE 
  const float useColAL = kAzure +7,
    filStyAL = 0,
    marStyAL = 21,
    marSizAL = 1.8,
    linWidAL = 3.,
    yOffAL = 1.,
    xOffAL = 1.,
    ylabSizAL = 0.04,
    xlabSizAL = 0.04,
    yTitSizAL = 0.05,
    xTitSizAL = 0.05,
    statHistAL = 0,
    linStAL = 1;
  
  // FONLL
  /* const float useColPy= kCyan,
    filStyPy= 0,
    marStyPy= 20,
    marSizPy= 2.3,
    linWidPy= 4.,
    yOffPy= 1.1,
    xOffPy= 1.,
    ylabSizPy= 0.06,
    xlabSizPy= 0.04,
    yTitSizPy= 0.06,
    xTitSizPy= 0.05,
    statHistPy= 0,
    linStPy= 1,
    yMinPy= 0.50,
    yMaxPy = 1000.;  
  */
  // Define axis of the histogram
  // shifted the point for ALICE only
  std::vector<float> v_pTBinAL = {0.3, 1.3, 2.3, 3.3, 4.3, 5.3, 6.3, 7.3, 8.3, 9.3, 10.3, 11.3};  
  
  // LHCb
  //const float useColLH = kGreen +2,
  const float useColLH = kMagenta +1,
    
    marStyLH = 47;

  // axis that we would like to have in our plot
  std::vector<float> v_pTBin = {0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11.};
  
  // CMS
  const float useColCM = kBlack,
    filStyCM = 0,
    marStyCM = 20,
    marSizCM = 2.2,
    linWidCM = 2.,
    yOffCM = 1.,
    xOffCM = 1.,
    ylabSizCM = 0.04,
    xlabSizCM = 0.04,
    yTitSizCM = 0.05,
    xTitSizCM = 0.05,
    statHistCM = 0,
    linStCM = 1;
  // Combine all
  const float yMinCombpT = 0.01, // change von 2.f to 0.699
    yMaxCombpT = 1.e12f,
    yTitSizComb= 0.04,
    ylabSizComb = 0.04,
    yOffComb = 1.9;
  const string yTitleCombpT = "10^{m} #times #frac{d#sigma}{dp_{T}} [#frac{ub}{GeV}]";

  // styleFONLL
  const float useColFO = kCyan,
    colAlphaFO = 0.25,
    filStyFO = 1001.,
    marSizFO = 0., 
    marStyFO = 1.5,
    linStyFO = 0.,
    linWidFO = 2.;
  
  // for ratio plot
  const float yMin_rat = 0.001,
    yMax_rat = 2.4999,
    yTitSiz_rat = 0.13,
    xTitSiz_rat = 0.15,  
    yOff_rat = 0.5,
    xOff_rat = 1.,
    ylabSiz_rat = 0.13,
    xlabSiz_rat = 0.13;
  const string yTitle_rat = "#frac{Data or Theory}{Pythia c}";
  
  // stylePad
  const float p1topMarg = 0.04, p1botMarg = 0.0, p1lefMarg = 0.15, p1rigMarg = 0.03;
  const float p2topMarg = 0.001, p2botMarg = 0.4, p2lefMarg = 0.15, p2rigMarg = 0.03;
  // setlogy
  const int p1logY = 1, p1logX = 0;
  const int p2logY = 0, p2logX = 0;

  // styleGraph
  const float useColgf = kBlack,
    colAlphagf = 1.,
    filStygf = 0.,
    marSizgf = 0., 
    marStygf = 1.5,
    linStygf = 4.,
    linWidgf = 2.;

  // Legend
  const float tlegx0 = 0.65,
    tlegx1 = 0.92,
    tlegy0 = 0.6,
    tlegy1 = 0.89;
  const float fColor = 0.,
    borSiz = 0.,
    texFon = 42.,
    texSiz = 0.05,
    bordSiz = 0.,
    filSty = 0;
    
  //////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// Variant variables End ///////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////


   
  //////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// ALICE part afo pT Start /////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////
  // old ALICE
  //auto inFileAL = std::unique_ptr<TFile>(TFile::Open( (inDir + "ALICE_HEPData-ins944757-v2-Table_3.root").c_str() ));
  // new ALICE
  auto inFileAL = std::unique_ptr<TFile>(TFile::Open( (inDir + "ALICEnew_HEPData-ins1511870-v1-Table_3.root").c_str() ));
  
  auto h_AL = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileAL->Get("Table 3/Hist1D_y1")->Clone()) );
  auto h_ALErr = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileAL->Get("Table 3/Hist1D_y1_e1")->Clone()) );
  
  TH1D *h_ALpT = new TH1D("h_ALpT", "h_ALpT", v_pTBinAL.size() - 1, v_pTBinAL.data());

  for (int jj = 2; jj < 9; ++jj) {
    // jj first refer ke v_pTBin, jj second refer ke histo ALICE yg ori
    h_ALpT->SetBinContent(jj, h_AL->GetBinContent(jj - 1)); 
    h_ALpT->SetBinError(jj, h_ALErr->GetBinContent(jj - 1));
    cout << "testALICE: " << h_ALErr->GetBinError(jj - 1) << endl;
  }

  // multiply by 2 to take into acc also for D*-
  h_ALpT->Scale(SFALpT);

  //////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// ALICE part afo pT End //////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////



  //////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// LHCb part afo pT Start //////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////

  auto inFileLHCb = std::unique_ptr<TFile>(TFile::Open( (inDir + "LHCb_HEPData-ins1218996-v1-Table_4.root").c_str() ));
  auto h_LHCby1 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileLHCb->Get("Table 4/Hist1D_y1")->Clone()) );
  auto h_LHCby1e1 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileLHCb->Get("Table 4/Hist1D_y1_e1")->Clone()) );

  TH1D *hpT_LHCb = new TH1D("hpT_LHCb", "hpT_LHCb", v_pTBinAL.size() - 1, v_pTBinAL.data());

  // Take the histogram (h_LHCby1) directly from clone LHCb hist
  for (int jj = 4; jj < 9; ++jj) {
    // jj yg frist refer ke v_pTBin, jj second refer ke histo LHCb yg ori
    hpT_LHCb->SetBinContent(jj, h_LHCby1->GetBinContent(jj));
    hpT_LHCb->SetBinError(jj, h_LHCby1e1->GetBinError(jj));
    cout << "LHCb: " << h_LHCby1->GetBinContent(jj) << endl;
  }

  // multiply by 2 to get abs rap
  hpT_LHCb->Scale(SFLHpT);

  //////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////// LHCb part afo pT Start ///////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////

  
  ///////////////////////////////////////////////////////////////////////////////////
  ///// PART YANG KITA NK REMOVE POINT YG XCANTIK ///////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////
  /*
  proYy0p5->SetBinContent(1, 0.);    
  proYy1->SetBinContent(1, 0.);
  proYy1p5->SetBinContent(1, 0.); 
  proYy1p5->SetBinContent(3, 0.); 
  proYy1p5->SetBinContent(4, 0.); 
  proYy2->SetBinContent(5, 0.); 
  //proYy2->SetBinContent(9, 0.); 
  */
  ///////////////////////////////////////////////////////////////////////////////////
  ///// PART YANG KITA NK REMOVE POINT YG XCANTIK END ///////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// MCD0 Pythia afo pT Start ////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////
  /*
  auto inFileMC = std::unique_ptr<TFile>(TFile::Open("/home/zulaiha/PhD/Analysis/wow/TtoH/JSON5/new/MuDhistos4_MC10_MBD0_JSON5.root"));
  //auto inFileMC = std::unique_ptr<TFile>(TFile::Open("/home/zulaiha/PhD/Analysis/wow/TtoH/JSON5/new/MuDhistosMC10_D0_beauty42.root"));
  
  auto h_MCPy0 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMC->Get("trueDstarptybin0")->Clone()) );
  auto h_MCPy1 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMC->Get("trueDstarptybin1")->Clone()) );
  auto h_MCPy2 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMC->Get("trueDstarptybin2")->Clone()) );
  auto h_MCPy3 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMC->Get("trueDstarptybin3")->Clone()) );
  auto h_MCPy4 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMC->Get("trueDstarptybin4")->Clone()) );
  */
  
  //auto inFileMC = std::unique_ptr<TFile>(TFile::Open("/home/zulaiha/PhD/Analysis/wow/TtoH/JSON5/new/MuDhistosMC10_D0_beauty42.root"));
  //auto inFileMC = std::unique_ptr<TFile>(TFile::Open("/home/zulaiha/PhD/Analysis/wow/TtoH/JSON5/new/MuDhistosMC10_D0_nobeauty_semitight4.root"));
  auto inFileMC = std::unique_ptr<TFile>(TFile::Open("/home/zulaiha/PhD/Analysis/wow/TtoH/JSON5/new/MuDhistosMC10_D0_beauty5_dEdxyz2.root"));

  auto h_Pymc0 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMC->Get("trueDstarHHpiptybin0")->Clone()) );
  auto h_Pymc1 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMC->Get("trueDstarHHpiptybin1")->Clone()) );
  auto h_Pymc2 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMC->Get("trueDstarHHpiptybin2")->Clone()) );
  auto h_Pymc3 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMC->Get("trueDstarHHpiptybin3")->Clone()) );
  auto h_Pymc4 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMC->Get("trueDstarHHpiptybin4")->Clone()) );  
  
  TH1D *h_Pyrap0 = new TH1D("h_Pyrap0", "h_Pyrap0", v_pTBin.size() - 1, v_pTBin.data());
  TH1D *h_Pyrap0p5 = new TH1D("h_Pyrap0p5", "h_Pyrap0p5", v_pTBin.size() - 1, v_pTBin.data());
  TH1D *h_Pyrap1 = new TH1D("h_Pyrap1", "h_Pyrap1", v_pTBin.size() - 1, v_pTBin.data());
  TH1D *h_Pyrap1p5 = new TH1D("h_Pyrap1p5", "h_Pyrap1p5", v_pTBin.size() - 1, v_pTBin.data());
  TH1D *h_Pyrap2 = new TH1D("h_Pyrap2", "h_Pyrap2", v_pTBin.size() - 1, v_pTBin.data());

  for (int pp = 1; pp < 12; ++pp) { // 0 bis 10

    //cout << "MCbin: " << h_Pymc0->GetBinContent(pp) << endl;

    h_Pyrap0->SetBinContent(pp, h_Pymc0->GetBinContent(pp));
    h_Pyrap0p5->SetBinContent(pp, h_Pymc1->GetBinContent(pp));
    h_Pyrap1->SetBinContent(pp, h_Pymc2->GetBinContent(pp));
    h_Pyrap1p5->SetBinContent(pp, h_Pymc3->GetBinContent(pp));
    h_Pyrap2->SetBinContent(pp, h_Pymc4->GetBinContent(pp));

    h_Pyrap0->SetBinError(pp, h_Pymc0->GetBinError(pp));
    h_Pyrap0p5->SetBinError(pp, h_Pymc1->GetBinError(pp));
    h_Pyrap1->SetBinError(pp, h_Pymc2->GetBinError(pp));
    h_Pyrap1p5->SetBinError(pp, h_Pymc3->GetBinError(pp));
    h_Pyrap2->SetBinError(pp, h_Pymc4->GetBinError(pp));
    

    cout << "MCbin: " << h_Pyrap0->GetBinContent(pp) << " " << "MCbinErr: " << h_Pyrap0->GetBinError(pp) << endl;    
  }

  // normalized the MC to Data
  h_Pyrap0->Scale(SFPypT);  
  h_Pyrap0p5->Scale(SFPypT);  
  h_Pyrap1->Scale(SFPypT);  
  h_Pyrap1p5->Scale(SFPypT);  
  h_Pyrap2->Scale(SFPypT);

  //////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// MCD0 Pythia afo pT End /////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// CMS c Start /////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////

  //TH1D CMScharm = proYy0 * h_Pyrapmcc0;

  //TH1D 
  //ratAL->Divide(hrat_AL, hrat_Py, 1., 1.);

  
  

  //////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// CMS c End /////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////


  
  //////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// MCc Pythia afo pT Start /////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////
  
  //auto inFileMCc = std::unique_ptr<TFile>(TFile::Open("/home/zulaiha/PhD/Analysis/wow/TtoH/JSON5/new/MuDhistosMC10_charm_nobeauty6_semitight4.root"));
  /*
  auto h_Pymcc0 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMCc->Get("trueDstarptybin0")->Clone()) );
  auto h_Pymcc1 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMCc->Get("trueDstarptybin1")->Clone()) );
  auto h_Pymcc2 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMCc->Get("trueDstarptybin2")->Clone()) );
  auto h_Pymcc3 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMCc->Get("trueDstarptybin3")->Clone()) );
  auto h_Pymcc4 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMCc->Get("trueDstarptybin4")->Clone()) );
  */
  
  auto h_Pymcc0 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMC->Get("true_cDstarHHpiptybin0")->Clone()) );
  auto h_Pymcc1 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMC->Get("true_cDstarHHpiptybin1")->Clone()) );
  auto h_Pymcc2 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMC->Get("true_cDstarHHpiptybin2")->Clone()) );
  auto h_Pymcc3 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMC->Get("true_cDstarHHpiptybin3")->Clone()) );
  auto h_Pymcc4 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMC->Get("true_cDstarHHpiptybin4")->Clone()) );
  
  TH1D *h_Pyrapmcc0 = new TH1D("h_Pyrapmcc0", "h_Pyrapmcc0", v_pTBin.size() - 1, v_pTBin.data());
  TH1D *h_Pyrapmcc0p5 = new TH1D("h_Pyrapmcc0p5", "h_Pyrapmcc0p5", v_pTBin.size() - 1, v_pTBin.data());
  TH1D *h_Pyrapmcc1 = new TH1D("h_Pyrapmcc1", "h_Pyrapmcc1", v_pTBin.size() - 1, v_pTBin.data());
  TH1D *h_Pyrapmcc1p5 = new TH1D("h_Pyrapmcc1p5", "h_Pyrapmcc1p5", v_pTBin.size() - 1, v_pTBin.data());
  TH1D *h_Pyrapmcc2 = new TH1D("h_Pyrapmcc2", "h_Pyrapmcc2", v_pTBin.size() - 1, v_pTBin.data());

  for (int pp = 1; pp < 12; ++pp) { // 0 bis 10

    //cout << "MCbin: " << h_Pymc0->GetBinContent(pp) << endl;

    h_Pyrapmcc0->SetBinContent(pp, h_Pymcc0->GetBinContent(pp));
    h_Pyrapmcc0p5->SetBinContent(pp, h_Pymcc1->GetBinContent(pp));
    h_Pyrapmcc1->SetBinContent(pp, h_Pymcc2->GetBinContent(pp));
    h_Pyrapmcc1p5->SetBinContent(pp, h_Pymcc3->GetBinContent(pp));
    h_Pyrapmcc2->SetBinContent(pp, h_Pymcc4->GetBinContent(pp));

    h_Pyrapmcc0->SetBinError(pp, h_Pymcc0->GetBinError(pp));
    h_Pyrapmcc0p5->SetBinError(pp, h_Pymcc1->GetBinError(pp));
    h_Pyrapmcc1->SetBinError(pp, h_Pymcc2->GetBinError(pp));
    h_Pyrapmcc1p5->SetBinError(pp, h_Pymcc3->GetBinError(pp));
    h_Pyrapmcc2->SetBinError(pp, h_Pymcc4->GetBinError(pp));
    

    cout << "MCbin: " << h_Pyrapmcc0->GetBinContent(pp) << " " << "MCbinErr: " << h_Pyrapmcc0->GetBinError(pp) << endl;    
  }

  // normalized the MC to Data
  h_Pyrapmcc0->Scale(SFPypTmcc);  
  h_Pyrapmcc0p5->Scale(SFPypTmcc);  
  h_Pyrapmcc1->Scale(SFPypTmcc);  
  h_Pyrapmcc1p5->Scale(SFPypTmcc);  
  h_Pyrapmcc2->Scale(SFPypTmcc);  

  //////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// MCc Pythia afo pT End //////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////



  
  //////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// MCb Pythia afo pT Start /////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////
  /*
  auto inFileMcb = std::unique_ptr<TFile>(TFile::Open("/home/zulaiha/PhD/Analysis/wow/TtoH/JSON5/new/MuDhistos4_MC10_MBbeauty_JSON5.root"));
  
  auto h_Pymcb0 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMc->Get("true_Dstarptybin0")->Clone()) );
  auto h_Pymcb1 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMc->Get("true_Dstarptybin1")->Clone()) );
  auto h_Pymcb2 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMc->Get("true_Dstarptybin2")->Clone()) );
  auto h_Pymcb3 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMc->Get("true_Dstarptybin3")->Clone()) );
  auto h_Pymcb4 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMc->Get("true_Dstarptybin4")->Clone()) );
  */
  
  auto h_Pymcb0 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMC->Get("true_bDstarHHpiptybin0")->Clone()) );
  auto h_Pymcb1 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMC->Get("true_bDstarHHpiptybin1")->Clone()) );
  auto h_Pymcb2 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMC->Get("true_bDstarHHpiptybin2")->Clone()) );
  auto h_Pymcb3 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMC->Get("true_bDstarHHpiptybin3")->Clone()) );
  auto h_Pymcb4 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inFileMC->Get("true_bDstarHHpiptybin4")->Clone()) );
  
  TH1D *h_Pyrapmcb0 = new TH1D("h_Pyrapmcb0", "h_Pyrapmcb0", v_pTBin.size() - 1, v_pTBin.data());
  TH1D *h_Pyrapmcb0p5 = new TH1D("h_Pyrapmcb0p5", "h_Pyrapmcb0p5", v_pTBin.size() - 1, v_pTBin.data());
  TH1D *h_Pyrapmcb1 = new TH1D("h_Pyrapmcb1", "h_Pyrapmcb1", v_pTBin.size() - 1, v_pTBin.data());
  TH1D *h_Pyrapmcb1p5 = new TH1D("h_Pyrapmcb1p5", "h_Pyrapmcb1p5", v_pTBin.size() - 1, v_pTBin.data());
  TH1D *h_Pyrapmcb2 = new TH1D("h_Pyrapmcb2", "h_Pyrapmcb2", v_pTBin.size() - 1, v_pTBin.data());

  for (int pp = 1; pp < 12; ++pp) { // 0 bis 10

    //cout << "MCbin: " << h_Pymc0->GetBinContent(pp) << endl;

    h_Pyrapmcb0->SetBinContent(pp, h_Pymcb0->GetBinContent(pp));
    h_Pyrapmcb0p5->SetBinContent(pp, h_Pymcb1->GetBinContent(pp));
    h_Pyrapmcb1->SetBinContent(pp, h_Pymcb2->GetBinContent(pp));
    h_Pyrapmcb1p5->SetBinContent(pp, h_Pymcb3->GetBinContent(pp));
    h_Pyrapmcb2->SetBinContent(pp, h_Pymcb4->GetBinContent(pp));

    h_Pyrapmcb0->SetBinError(pp, h_Pymcb0->GetBinError(pp));
    h_Pyrapmcb0p5->SetBinError(pp, h_Pymcb1->GetBinError(pp));
    h_Pyrapmcb1->SetBinError(pp, h_Pymcb2->GetBinError(pp));
    h_Pyrapmcb1p5->SetBinError(pp, h_Pymcb3->GetBinError(pp));
    h_Pyrapmcb2->SetBinError(pp, h_Pymcb4->GetBinError(pp));
    

    cout << "MCbin: " << h_Pyrapmcb0->GetBinContent(pp) << " " << "MCbinErr: " << h_Pyrapmcb0->GetBinError(pp) << endl;    
  }

  // normalized the MC to Data
  h_Pyrapmcb0->Scale(SFPypTmcb);  
  h_Pyrapmcb0p5->Scale(SFPypTmcb);  
  h_Pyrapmcb1->Scale(SFPypTmcb);  
  h_Pyrapmcb1p5->Scale(SFPypTmcb);  
  h_Pyrapmcb2->Scale(SFPypTmcb);  

  //////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// MCb Pythia afo pT End //////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////
  

 
  //////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////// CMS part afo pT Start ////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////
   
  auto h2DpT = std::unique_ptr<TH2D>(dynamic_cast<TH2D *>(inFile->Get("xxx")->Clone("XsecforpT")) );
  cout << "lowedgeY: " << h2DpT->GetXaxis()->GetBinLowEdge(5) << " " << "upedgeY: " << h2DpT->GetXaxis()->GetBinUpEdge(5) << endl;
  
  // Get the cross section value for each rap along pT(Yaxis)
  TH1D *proY0 = h2DpT->ProjectionY("y0", 0, 0); // underflow
  TH1D *proYy0 = h2DpT->ProjectionY( ("y_" + toStr(h2DpT->GetXaxis()->GetBinLowEdge(1)) + "_" + toStr(h2DpT->GetXaxis()->GetBinUpEdge(1))).c_str(), 1, 1); // |y| < 0.5
  TH1D *proYy0p5 = h2DpT->ProjectionY( ("y_" + toStr(h2DpT->GetXaxis()->GetBinLowEdge(2)) + "_" + toStr(h2DpT->GetXaxis()->GetBinUpEdge(2))).c_str(), 2, 2); // 0.5 < |y| < 1
  TH1D *proYy1 = h2DpT->ProjectionY( ("y_" + toStr(h2DpT->GetXaxis()->GetBinLowEdge(3)) + "_" + toStr(h2DpT->GetXaxis()->GetBinUpEdge(3))).c_str(), 3, 3); // 1 < |y| < 1.5
  TH1D *proYy1p5 = h2DpT->ProjectionY( ("y_" + toStr(h2DpT->GetXaxis()->GetBinLowEdge(4)) + "_" + toStr(h2DpT->GetXaxis()->GetBinUpEdge(4))).c_str(), 4, 4); // 1.5 < |y| < 2
  TH1D *proYy2 = h2DpT->ProjectionY( ("y_" + toStr(h2DpT->GetXaxis()->GetBinLowEdge(5)) + "_" + toStr(h2DpT->GetXaxis()->GetBinUpEdge(5))).c_str(), 5, 5); // 2 < |y| << 2.5

  // to check if the value printout ok
  for (int aa = 1; aa < 11; ++aa) {
    cout << "bincontentrecoY: " << proYy0->GetBinContent(aa) << " " << "binerrorrecoY: " << proYy0->GetBinError(aa) << " " << endl;    
  }
  /*
  proYy0->Scale((1/0.0267));
  proYy0p5->Scale((1/0.0267));
  proYy1->Scale((1/0.0267));
  proYy1p5->Scale((1/0.0267));
  proYy2->Scale((1/0.0267));
  */
  proYy0->Scale((1/0.0267) * 0.9);
  proYy0p5->Scale((1/0.0267) * 0.9);
  proYy1->Scale((1/0.0267) * 0.9);
  proYy1p5->Scale((1/0.0267) * 0.9);
  proYy2->Scale((1/0.0267) * 0.9);
  /*
  proYy0->Add(h_Pyrapmcb0, -1);
  proYy0p5->Add(h_Pyrapmcb0p5, -1);
  proYy1->Add(h_Pyrapmcb1, -1);
  proYy1p5->Add(h_Pyrapmcb1p5, -1);
  proYy2->Add(h_Pyrapmcb2, -1);  
  */
  //////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// CMS part afo pT End ///////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////


  
  



  //////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// MC FONLL afo pT Start //////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////

  
  const Int_t n = 12;
  Double_t x[n] = {0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.};    
  Double_t exl[n] = {0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
  Double_t exh[n] = {0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};   
  
   // y 0-0.5
  Double_t y0[n] = {9.1570e+06, 1.8510e+07, 1.3020e+07, 6.8230e+06, 3.4750e+06, 1.8470e+06, 1.0350e+06, 6.0960e+05, 3.7460e+05, 2.3900e+05, 5.6330e+05};
  Double_t eyl0[n] = {-1.4522e+05, 9.2034e+05, 3.2372e+06, 2.7891e+06, 1.8224e+06, 1.1257e+06, 6.9757e+05, 4.3361e+05, 2.7318e+05, 1.7797e+05, 4.4126e+05};
  Double_t eyh0[n] = {2.7133e+07, 4.5073e+07, 2.7327e+07, 1.2803e+07, 6.0085e+06, 3.0011e+06, 1.6022e+06, 9.0656e+05, 5.3909e+05, 3.3460e+05, 7.3875e+05};

  // y = 0.5-1
  Double_t y0p5[n]   = {9.1760e+06, 1.8380e+07, 1.2850e+07, 6.7080e+06, 3.4050e+06, 1.8050e+06, 1.0090e+06, 5.9280e+05, 3.6350e+05, 2.3150e+05, 5.4170e+05};
  Double_t eyl0p5[n] = {-1.5949e+05, 9.3971e+05, 3.2315e+06, 2.7594e+06, 1.7945e+06, 1.1042e+06, 6.8195e+05, 4.2168e+05, 2.6515e+05, 1.7235e+05, 4.2423e+05};
  Double_t eyh0p5[n] = {2.7250e+07, 4.4768e+07, 2.6986e+07, 1.2591e+07, 5.8877e+06, 2.9324e+06, 1.5615e+06, 8.8171e+05, 5.2315e+05, 3.2410e+05, 7.1055e+05};

  // y = 1-1.5
  Double_t y1[n]   = {9.3460e+06, 1.8140e+07, 1.2520e+07, 6.4790e+06, 3.2660e+06, 1.7210e+06, 9.5770e+05, 5.5990e+05, 3.4180e+05, 2.1670e+05, 4.9960e+05};
  Double_t eyl1[n] = {-2.3649e+05, 9.8194e+05, 3.2154e+06, 2.6984e+06, 1.7368e+06, 1.0604e+06, 6.5080e+05, 3.9812e+05, 2.4927e+05, 1.6138e+05, 3.9100e+05};
  Double_t eyh1[n] = {2.7917e+07, 4.4266e+07, 2.6300e+07, 1.2165e+07, 5.6511e+06, 2.7980e+06, 1.4827e+06, 8.3302e+05, 4.9207e+05, 3.0366e+05, 6.5587e+05};   

  // y = 1.5-2
  Double_t y1p5[n]   = {1.0080e+07, 1.7920e+07, 1.2020e+07, 6.1320e+06, 3.0580e+06, 1.5970e+06, 8.8120e+05, 5.1120e+05, 3.0990e+05, 1.9520e+05, 4.3870e+05};
  Double_t eyl1p5[n] = {-6.3218e+05, 1.0770e+06, 3.1930e+06, 2.5988e+06, 1.6464e+06, 9.9402e+05, 6.0368e+05, 3.6330e+05, 2.2578e+05, 1.4518e+05, 3.4305e+05};
  Double_t eyh1p5[n] = {3.0639e+07, 4.3878e+07, 2.5286e+07, 1.1518e+07, 5.2945e+06, 2.5976e+06, 1.3643e+06, 7.6099e+05, 4.4628e+05, 2.7351e+05, 5.7675e+05};

  // y = 2-2.5
  Double_t y2[n]   = {1.1400e+07, 1.7890e+07, 1.1370e+07, 5.6630e+06, 2.7790e+06, 1.4320e+06, 7.8050e+05, 4.4770e+05, 2.6850e+05, 1.6740e+05, 3.6230e+05};
  Double_t eyl2[n] = {-1.3662e+06, 1.4270e+06, 3.1870e+06, 2.4593e+06, 1.5205e+06, 9.0178e+05, 5.3694e+05, 3.1769e+05, 1.9545e+05, 1.2444e+05, 2.8269e+05};
  Double_t eyh2[n] = {3.5566e+07, 4.4103e+07, 2.3975e+07, 1.0659e+07, 4.8187e+06, 2.3313e+06, 1.2098e+06, 6.6697e+05, 3.8714e+05, 2.3478e+05, 4.7754e+05};

  // y = 2.5-3
  Double_t y2p5[n]   = {1.2780e+07, 1.7870e+07, 1.0580e+07, 5.0830e+06, 2.4350e+06, 1.2300e+06, 6.5880e+05, 3.7170e+05, 2.1930e+05, 1.3460e+05, 2.7580e+05};
  Double_t eyl2p5[n] = {-2.2896e+06, 1.5645e+06, 3.1756e+06, 2.2772e+06, 1.3590e+06, 7.8670e+05, 4.5225e+05, 2.6327e+05, 1.5939e+05, 9.9967e+04, 2.1454e+05};
  Double_t eyh2p5[n] = {4.1211e+07, 4.4511e+07, 2.2380e+07, 9.5882e+06, 4.2294e+06, 2.0064e+06, 1.0227e+06, 5.5470e+05, 3.1701e+05, 1.8930e+05, 3.6533e+05};
  
  // y = 3-3.5
  Double_t y3[n]   = {1.3930e+07, 1.7490e+07, 9.5940e+06, 4.3980e+06, 2.0360e+06, 9.9970e+05, 5.2160e+05, 2.8710e+05, 1.6540e+05, 9.9220e+04, 1.8830e+05};
  Double_t eyl3[n] = {-2.8384e+06, 1.1291e+06, 3.0552e+06, 2.0449e+06, 1.1656e+06, 6.5153e+05, 3.5677e+05, 2.0263e+05, 1.1979e+05, 7.3370e+04, 1.4557e+05};
  Double_t eyh3[n] = {4.6421e+07, 4.4214e+07, 2.0376e+07, 8.3197e+06, 3.5475e+06, 1.6357e+06, 8.1268e+05, 4.3012e+05, 2.4002e+05, 1.4015e+05, 2.5158e+05};
  
  // y = 3.5-4
  Double_t y3p5[n]   = {1.4710e+07, 1.6580e+07, 8.3500e+06, 3.6140e+06, 1.5970e+06, 7.5260e+05, 3.7810e+05, 2.0070e+05, 1.1170e+05, 6.4750e+04, 1.1090e+05};
  Double_t eyl3p5[n] = {-2.9918e+06, 3.6953e+05, 2.7490e+06, 1.7409e+06, 9.3876e+05, 4.9211e+05, 2.5717e+05, 1.4083e+05, 8.0394e+04, 4.7565e+04, 8.4843e+04};
  Double_t eyh3p5[n] = {5.0586e+07, 4.2797e+07, 1.7850e+07, 6.8668e+06, 2.7949e+06, 1.2373e+06, 5.9264e+05, 3.0285e+05, 1.6340e+05, 9.2223e+04, 1.5011e+05};
  
  // y = 4-4.5
  Double_t y4[n]   = {1.4920e+07, 1.5060e+07, 6.8610e+06, 2.7540e+06, 1.1430e+06, 5.0830e+05, 2.4170e+05, 1.2170e+05, 6.4450e+04, 3.5610e+04, 5.3590e+04};
  Double_t eyl4[n] = {-2.8818e+06, -3.3122e+05, 2.2745e+06, 1.3680e+06, 6.8864e+05, 3.2897e+05, 1.6271e+05, 8.4493e+04, 4.5873e+04, 2.5878e+04, 4.0336e+04};
  Double_t eyh4[n] = {5.2795e+07, 3.9785e+07, 1.4821e+07, 5.2695e+06, 2.0147e+06, 8.4312e+05, 3.8255e+05, 1.8571e+05, 9.5417e+04, 5.1405e+04, 7.3876e+04};

  // y = 4.5-7 (overflow)
  Double_t y4p5[n]   = {4.8220e+07, 3.5090e+07, 1.1640e+07, 3.7040e+06, 1.2780e+06, 4.8600e+05, 2.0180e+05, 8.9930e+04, 4.2530e+04, 2.1100e+04, 2.4460e+04};
  Double_t eyl4p5[n] = {-8.0084e+06, -2.9862e+06, 3.5569e+06, 1.8794e+06, 7.4955e+05, 3.0441e+05, 1.3195e+05, 6.0686e+04, 2.9376e+04, 1.4817e+04, 1.7410e+04};
  Double_t eyh4p5[n] = {1.8187e+08, 9.8971e+07, 2.6058e+07, 7.2678e+06, 2.3054e+06, 8.2583e+05, 3.2770e+05, 1.4108e+05, 6.4791e+04, 3.1448e+04, 3.5426e+04};

  // new value after * 2 (to have D*+-) & / factor for unit
  // another *2 for integral dpt/drap
  Double_t ynew0[n];
  Double_t eylnew0[n];
  Double_t eyhnew0[n];

  Double_t ynew0p5[n];
  Double_t eylnew0p5[n];
  Double_t eyhnew0p5[n];

  Double_t ynew1[n];
  Double_t eylnew1[n];
  Double_t eyhnew1[n];

  Double_t ynew1p5[n];
  Double_t eylnew1p5[n];
  Double_t eyhnew1p5[n];

  Double_t ynew2[n];
  Double_t eylnew2[n];
  Double_t eyhnew2[n];
  
  Double_t ynew2p5[n];
  Double_t eylnew2p5[n];
  Double_t eyhnew2p5[n];

  Double_t ynew3[n];
  Double_t eylnew3[n];
  Double_t eyhnew3[n];

  Double_t ynew3p5[n];
  Double_t eylnew3p5[n];
  Double_t eyhnew3p5[n];

  Double_t ynew4[n];
  Double_t eylnew4[n];
  Double_t eyhnew4[n];  

  Double_t ynew4p5[n];
  Double_t eylnew4p5[n];
  Double_t eyhnew4p5[n];
  
  //Double_t ynewv1[n] = {4.5880000e+10, 9.1900000e+10, 6.4250000e+10, 3.3540000e+10, 1.7025000e+10, 9.0250000e+09, 5.0450000e+09, 2.9640000e+09, 1.8175000e+09, 1.1575000e+09, 2.4970000e+09};
  
  for (int ii = 0; ii < 11; ++ii) {
    ynew0[ii] = (y0[ii] * 4) / 1e+06;
    eylnew0[ii] = (abs(y0[ii] - eyl0[ii]) * 4) / 1e+06;
    eyhnew0[ii] = (abs(eyh0[ii] - y0[ii]) * 4) / 1e+06;

    ynew0p5[ii] = (y0p5[ii] * 4) / 1e+06;
    eylnew0p5[ii] = (abs(y0p5[ii] - eyl0p5[ii]) * 4) / 1e+06;
    eyhnew0p5[ii] = (abs(eyh0p5[ii] - y0p5[ii]) * 4) / 1e+06;

    ynew1[ii] = (y1[ii] * 4) / 1e+06;
    eylnew1[ii] = (abs(y1[ii] - eyl1[ii]) * 4) / 1e+06;
    eyhnew1[ii] = (abs(eyh1[ii] - y1[ii]) * 4) / 1e+06;

    ynew1p5[ii] = (y1p5[ii] * 4) / 1e+06;
    eylnew1p5[ii] = (abs(y1p5[ii] - eyl1p5[ii]) * 4) / 1e+06;
    eyhnew1p5[ii] = (abs(eyh1p5[ii] - y1p5[ii]) * 4) / 1e+06;    
    
    ynew2[ii] = (y2[ii] * 4) / 1e+06;
    eylnew2[ii] = (abs(y2[ii] - eyl2[ii])  * 4) / 1e+06;
    eyhnew2[ii] = (abs(eyh2[ii] - y2[ii]) * 4) / 1e+06;

    ynew2p5[ii] = (y2p5[ii] * 4) / 1e+06;
    eylnew2p5[ii] = (abs(y2p5[ii] - eyl2p5[ii]) * 4) / 1e+06;
    eyhnew2p5[ii] = (abs(eyh2p5[ii] - y2p5[ii]) * 4) / 1e+06;

    ynew3[ii] = (y3[ii] * 4) / 1e+06;
    eylnew3[ii] = (abs(y3[ii] - eyl3[ii]) * 4) / 1e+06;
    eyhnew3[ii] = (abs(eyh3[ii] - y3[ii]) * 4) / 1e+06;

    ynew3p5[ii] = (y3p5[ii] * 4) / 1e+06;
    eylnew3p5[ii] = (abs(y3p5[ii] - eyl3p5[ii]) * 4) / 1e+06;
    eyhnew3p5[ii] = (abs(eyh3p5[ii] - y3p5[ii]) * 4) / 1e+06;

    ynew4[ii] = (y4[ii] * 4) / 1e+06;
    eylnew4[ii] = (abs(y4[ii] - eyl4[ii]) * 4) / 1e+06;
    eyhnew4[ii] = (abs(eyh4[ii] - y4[ii]) * 4) / 1e+06;    

    ynew4p5[ii] = (y4p5[ii] * 4) / 1e+06;
    eylnew4p5[ii] = (abs(y4p5[ii] - eyl4p5[ii]) * 4) / 1e+06;
    eyhnew4p5[ii] = (abs(eyh4p5[ii] - y4p5[ii]) * 4) / 1e+06;
    
    //cout << "ynew: " << ynew0[ii] << " " << "eylew: " << eylnew0[ii] << endl;
  }
   
  // test value
  /*
   const Int_t n = 3;  
   Double_t x[n] = {0.5, 1.5, 2.5};
   Double_t y[n] = {100., 90., 80.};
   Double_t exl[n] = {0.5, 0.5, 0.5};
   Double_t exh[n] = {0.5, 0.5, 0.5};   
   Double_t eyl[n] = {50., 40., 30.};
   Double_t eyh[n] = {20., 30., 40.};
   auto gr = new TGraphAsymmErrors(n,x,y,exl,exh,eyl,eyh);  
   */
   
  auto gr_FO0 = new TGraphAsymmErrors(n, x, ynew0, exl, exh, eylnew0, eyhnew0);  
  auto gr_FO0p5 = new TGraphAsymmErrors(n, x, ynew0p5, exl, exh, eylnew0p5, eyhnew0p5);  
  auto gr_FO1 = new TGraphAsymmErrors(n, x, ynew1, exl, exh, eylnew1, eyhnew1);  
  auto gr_FO1p5 = new TGraphAsymmErrors(n, x, ynew1p5, exl, exh, eylnew1p5, eyhnew1p5);  
  auto gr_FO2 = new TGraphAsymmErrors(n, x, ynew2, exl, exh, eylnew2, eyhnew2);
  
  //auto gr_FO2p5 = new TGraphAsymmErrors(n, x, ynew2p5, exl, exh, eylnew2p5, eyhnew2p5);  
  //auto gr3 = new TGraphAsymmErrors(n, x, ynew3, exl, exh, eylnew3, eyhnew3);  
  //auto gr3p5 = new TGraphAsymmErrors(n, x, ynew3p5, exl, exh, eylnew3p5, eyhnew3p5);  
  //auto gr4 = new TGraphAsymmErrors(n, x, ynew4, exl, exh, eylnew4, eyhnew4);  
  //auto gr4p5 = new TGraphAsymmErrors(n, x, ynew4p5, exl, exh, eylnew4p5, eyhnew4p5);  

  //gr->SetFillStyle(1001);
  //gr->SetFillColorAlpha(kCyan, 0.3);
  //styleGraph(gr_FO0, kCyan, 0.3, );
  //filStyPy, marStyPy, marSizPy, linWidPy,
  //styleGraph(gr_FO0, kCyan, 0.3, colAlphagf, filStygf, marStygf, marSizgf, linStygf, linWidgf);  
  styleGraph(gr_FO0, kCyan, colAlphaFO, filStyFO, marStyFO, marSizFO, linStyFO, linWidFO);  
  styleGraph(gr_FO0p5, kCyan, colAlphaFO, filStyFO, marStyFO, marSizFO, linStyFO, linWidFO);  
  styleGraph(gr_FO1, kCyan, colAlphaFO, filStyFO, marStyFO, marSizFO, linStyFO, linWidFO);  
  styleGraph(gr_FO1p5, kCyan, colAlphaFO, filStyFO, marStyFO, marSizFO, linStyFO, linWidFO);  
  styleGraph(gr_FO2, kCyan, colAlphaFO, filStyFO, marStyFO, marSizFO, linStyFO, linWidFO);  
  //styleGraph(gr_FO2p5, kCyan, colAlphaFO, filStyFO, marStyFO, marSizFO, linStyFO, linWidFO);  
  //styleGraph(gr3, kCyan, colAlphaFO, filStyFO, marStyFO, marSizFO, linStyFO, linWidFO);  
  //styleGraph(gr3p5, kCyan, colAlphaFO, filStyFO, marStyFO, marSizFO, linStyFO, linWidFO);  
  //styleGraph(gr4, kCyan, colAlphaFO, filStyFO, marStyFO, marSizFO, linStyFO, linWidFO);  
  //styleGraph(gr4p5, kCyan, colAlphaFO, filStyFO, marStyFO, marSizFO, linStyFO, linWidFO);  
  
  // For ratio plot:
  // since xleh divide dgn graf, kene convert graf->hist
  // pastu divide utk ratio, then tukar balik ke graf utk plot
  /*
  Double_t xx,yy;
  // Change graf to hist
  TH1D *hgr_FO0EH =  new TH1D("hgr_FO0EH", "hgr_FO0EH", v_pTBin.size() - 1, v_pTBin.data());
  TH1D *hgr_FO0EL =  new TH1D("hgr_FO0EL", "hgr_FO0EL", v_pTBin.size() - 1, v_pTBin.data());
  
  auto nPoints = gr_FO0->GetN();
  for (int ii = 0; ii < nPoints; ++ii) {
    // for checking:
    // print out value i,x,y 
    gr_FO0->GetPoint(ii, xx, yy);
    cout << "ii: " << ii << " X point: " << xx << " Y points: " << yy << endl;
    gr_FO0->GetErrorYhigh(ii);
    gr_FO0->GetErrorYlow(ii);
    cout << " YErrH: " << gr_FO0->GetErrorYhigh(ii) << endl;
    cout << " YErrL: " << gr_FO0->GetErrorYlow(ii) << endl;
    
    hgr_FO0EH->SetBinContent(ii, yy);
    hgr_FO0EH->SetBinError(ii, gr_FO0->GetErrorYhigh(ii));

    hgr_FO0EL->SetBinContent(ii, yy);
    hgr_FO0EL->SetBinError(ii, gr_FO0->GetErrorYlow(ii));
  }
  */
  
  //////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// MC FONLL afo pT End ///////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////

  /*
  //////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// New C histograms Start ////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////
  TH1D CMSnPyC = proYy0 * h_Pyrapmcc0;

  

  //////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// New C histograms end //////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////
  */

  
  //////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////// Include Ratio Plot ///////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////
  
  // Since Pythia and LHCb have same bin, CMS x. directly projection. ALICE, a bit offset
  // make a new histos for CMS, ALICE and LHCb
  TH1D *hrat_CMS = new TH1D("hrat_CMS", "hrat_CMS", v_pTBin.size() - 1, v_pTBin.data());
  TH1D *hrat_AL = new TH1D("hrat_AL", "hrat_AL", v_pTBin.size() - 1, v_pTBin.data());
  TH1D *hrat_LH = new TH1D("hrat_LH", "hrat_LH", v_pTBin.size() - 1, v_pTBin.data());  
  TH1D *hrat_Py = new TH1D("hrat_Py", "hrat_Py", v_pTBin.size() - 1, v_pTBin.data());  
  TH1D *hrat_FOEH = new TH1D("hrat_FOEH", "hrat_FOEH", v_pTBin.size() - 1, v_pTBin.data());  
  TH1D *hrat_FOEL = new TH1D("hrat_FOEL", "hrat_FOEL", v_pTBin.size() - 1, v_pTBin.data());
  TH1D *hrat_Pymcc = new TH1D("hrat_Pymcc", "hrat_Pymcc", v_pTBin.size() - 1, v_pTBin.data());  
  TH1D *hrat_Pymcb = new TH1D("hrat_Pymcb", "hrat_Pymcb", v_pTBin.size() - 1, v_pTBin.data());  

  // ini guna utk plot hist fonll dlm 2d
  TH1D *hrat_FOEL0 = new TH1D("hrat_FOEL0", "hrat_FOEL0", v_pTBin.size() - 1, v_pTBin.data());  
  TH1D *hrat_FOEL0p5 = new TH1D("hrat_FOEL0p5", "hrat_FOEL0p5", v_pTBin.size() - 1, v_pTBin.data());
  TH1D *hrat_FOEL1 = new TH1D("hrat_FOEL1", "hrat_FOEL1", v_pTBin.size() - 1, v_pTBin.data());  
  TH1D *hrat_FOEL1p5 = new TH1D("hrat_FOEL1p5", "hrat_FOEL1p5", v_pTBin.size() - 1, v_pTBin.data());
  TH1D *hrat_FOEL2 = new TH1D("hrat_FOEL2", "hrat_FOEL2", v_pTBin.size() - 1, v_pTBin.data());  
  
  
  // histos u want to appear in ratio plot 
  TH1D *ratAL = (TH1D*) h_Pyrap0->Clone();
  TH1D *ratCMS = (TH1D*) h_Pyrap0->Clone();
  TH1D *ratLH = (TH1D*) h_Pyrap0->Clone();
  TH1D *ratPy = (TH1D*) h_Pyrap0->Clone();
  TH1D *ratFOEH = (TH1D*) h_Pyrap0->Clone();
  TH1D *ratFOEL = (TH1D*) h_Pyrap0->Clone();
  TH1D *ratPymcc = (TH1D*) h_Pyrap0->Clone();
  TH1D *ratPymcb = (TH1D*) h_Pyrap0->Clone();

  // declare x and y value in graf
  Double_t xx,yy;
  Double_t xx0,yy0,xx0p5,yy0p5,xx1,yy1,xx1p5,yy1p5,xx2,yy2;

  // change histogram to graf
  Double_t gratC[n];
  Double_t gratEH[n];
  Double_t gratEL[n];
      
  // canvas for differential plot yg ade 2 pad
  TCanvas *c1 = new TCanvas("c1", "c1", 200, 10, 1000, 1000);

  TPad *pad1 = new TPad("pad1", "pad1", 0., 0.31, 1., 1.);
  TPad *pad2 = new TPad("pad2", "pad2", 0., 0., 1., 0.30);  
  c1->cd();
  stylePad(pad1, p1topMarg, p1botMarg, p1lefMarg, p1rigMarg, p1logY, p1logX);
  pad1->Draw();
  pad1->cd();
  
  // Legend for individual plots
  //TLegend *legInd = new TLegend(0.6, 0.7, 0.92, 0.89);
  TLegend *legInd = new TLegend(tlegx0, tlegy0, tlegx1, tlegy1);
  TLegend *stdL0 = new TLegend(0.2, 0.88, 0.89, .93); // size of legend for lower pt, hlptr
  
  /////////////////// This is where you draw & styling plots, canvas, legends //////////////////////
      
  if (num == 0) {

    // 2 sbb utk CMS point 0-1 pT xde
    // 13 sbb 13-2 = 11 bins (drp 0-11)
    // utk ratio xleh divide xsama binning, so kene make sure nbin setiap histos sama
    for (int pp = 2; pp < 13; ++pp) { 

      hrat_CMS->SetBinContent(pp, proYy0->GetBinContent(pp -1));
      hrat_CMS->SetBinError(pp, proYy0->GetBinError(pp -1));
      
      hrat_AL->SetBinContent(pp - 1, h_ALpT->GetBinContent(pp -1));
      hrat_AL->SetBinError(pp - 1, h_ALpT->GetBinError(pp -1));

      hrat_Py->SetBinContent(pp - 1, h_Pyrap0->GetBinContent(pp -1));
      hrat_Py->SetBinError(pp - 1, h_Pyrap0->GetBinError(pp -1));

      hrat_Pymcc->SetBinContent(pp - 1, h_Pyrapmcc0->GetBinContent(pp -1));
      hrat_Pymcc->SetBinError(pp - 1, h_Pyrapmcc0->GetBinError(pp -1));     

      hrat_Pymcb->SetBinContent(pp - 1, h_Pyrapmcb0->GetBinContent(pp -1));
      hrat_Pymcb->SetBinError(pp - 1, h_Pyrapmcb0->GetBinError(pp -1));      
      //cout << "hAL: " << hrat_AL->GetBinContent(pp - 1) << endl;
      //cout << "hPy: " << hrat_Py->GetBinContent(pp - 1) << endl;
      //cout << "hratCMS: " << hrat_CMS->GetBinContent(pp - 1) << endl;
      
      // print out value i,x,y
      gr_FO0->GetPoint(pp - 2, xx, yy);
      //cout << "ii: " << pp - 2 << " X point: " << xx << " Y points: " << yy << endl;
      gr_FO0->GetErrorYhigh(pp - 2);
      gr_FO0->GetErrorYlow(pp - 2);
      //cout << " YErrH: " << gr_FO0->GetErrorYhigh(pp - 2) << endl;
      //cout << " YErrL: " << gr_FO0->GetErrorYlow(pp - 2) << endl;
    
      hrat_FOEH->SetBinContent(pp - 1, yy);
      hrat_FOEH->SetBinError(pp - 1, gr_FO0->GetErrorYhigh(pp - 2));
      //cout << "BinC: " << hrat_FOEH->GetBinContent(pp - 1) << endl;
      //cout << "BinH: " << hrat_FOEH->GetBinError(pp - 1) << endl;
      
      hrat_FOEL->SetBinContent(pp - 1, yy);
      hrat_FOEL->SetBinError(pp - 1, gr_FO0->GetErrorYlow(pp - 2));      
      //cout << "BinC: " << hrat_FOEL->GetBinContent(pp - 1) << endl;
      //cout << "BinL: " << hrat_FOEL->GetBinError(pp - 1) << endl;	
    }

    TFile fout0("lala.root","RECREATE");
    fout0.cd();
    hrat_FOEL->Write();
    fout0.Close();

    auto inF = std::unique_ptr<TFile>(TFile::Open("./lala.root"));
    auto h_Clorap0 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inF->Get("hrat_FOEL")->Clone()) );

    // declare a new hist just to draw the line w/o err in the plot
    // cannot use hrat_FOEL/H as they hv the error
    // histograms w/o error to 
    TH1D *h_MCFOrap0 = new TH1D("h_MCFOrap0", "h_MCFOrap0", v_pTBin.size() - 1, v_pTBin.data());
    
    for (int pp = 1; pp < 12; ++pp) { // 0 bis 10    
      h_MCFOrap0->SetBinContent(pp, h_Clorap0->GetBinContent(pp));
      //h_MCFOrap0->SetBinError(pp, h_Clorap0->GetBinError(pp));
      // MUST put err eventho small, otherwise, go crazy
      h_MCFOrap0->SetBinError(pp, 0.000000001); 
    }
    
    //h_Pyrap0->Draw("hist");
    h_Pyrapmcc0->Draw("hist");
    //h_Pyrapmcb0->Draw("hist same");    
    h_ALpT->Draw("PEX0 same"); // ALICE
    proYy0->Draw("PEX0 same");
    
    gr_FO0->Draw("2");    
    //gr_FO0->Draw("E");    

    h_MCFOrap0->Draw("hist same");
    //h_Pyrap0->Draw("hist same");
    h_Pyrapmcc0->Draw("hist same");
    //h_Pyrapmcb0->Draw("hist same");        
    h_ALpT->Draw("PEX0 same"); // ALICE
    proYy0->Draw("PEX0 same");
    //h_MCFOrap0->Draw("hist same");

    
    // legend must be draw b4 ratio
    //otherwise, it will appear in ratio column
    legInd->Draw();

    //new legend for rapidity bin
    stdL0->SetNColumns(1);  
    stdL0->AddEntry(h_Pyrap0, "|y| < 0.5", "");
    styleLeg(stdL0, 0, 0, 42, 0.05, 0, 0);
    stdL0->Draw(); // leg kene draw kat the latest overlap
    
    // ratio plot can only be divided when #bin same & bin width same
    ratAL->Divide(hrat_AL, hrat_Pymcc, 1., 1.);
    ratCMS->Divide(hrat_CMS, hrat_Pymcc, 1., 1.);
    ratPy->Divide(hrat_Py, hrat_Pymcc, 1., 1.);
    ratFOEH->Divide(hrat_FOEH, hrat_Pymcc, 1., 1.);
    ratFOEL->Divide(hrat_FOEL, hrat_Pymcc, 1., 1.);
    ratPymcc->Divide(hrat_Pymcc, hrat_Pymcc, 1., 1.);
    ratPymcb->Divide(hrat_Pymcb, hrat_Pymcc, 1., 1.);

    for (int ii = 1; ii < 12; ++ii) {
      gratC[ii-1] = ratFOEH->GetBinContent(ii); // can take EL also
      gratEH[ii-1] = ratFOEH->GetBinError(ii);
      gratEL[ii-1] = ratFOEL->GetBinError(ii);
      
      //cout << "BinCrat: " << ratFOEH->GetBinContent(ii) << endl;
      cout << "BinHrat: " << ratFOEH->GetBinError(ii) << endl;
      //cout << "BinLrat: " << ratFOEL->GetBinError(ii) << endl;
      
    }
    
    auto grat0 = new TGraphAsymmErrors(n, x, gratC, exl, exh, gratEL, gratEH);
    TH1D *h_ratMCFO0 = new TH1D("h_ratMCFO0", "h_ratMCFO0", v_pTBin.size() - 1, v_pTBin.data());

    for (int pp = 1; pp < 12; ++pp) { // 0 bis 10    
      h_ratMCFO0->SetBinContent(pp, ratFOEH->GetBinContent(pp));
      //h_MCFOrap0->SetBinError(pp, h_Clorap0->GetBinError(pp));
      // MUST put err eventho small, otherwise, go crazy
      h_ratMCFO0->SetBinError(pp, 0.000000001); 
    }    
    
    c1->cd();
    stylePad(pad2, p2topMarg, p2botMarg, p2lefMarg, p2rigMarg, p2logY, p2logX);
    pad2->Draw();
    pad2->cd();
    pad2->SetGridy();

    ratAL->GetYaxis()->SetNdivisions(507);
    ratAL->GetXaxis()->SetNdivisions(507);   
    ratAL->Draw("E2");     
    //ratPy->Draw("histsame");
    ratPymcc->Draw("histsame");
    //ratPymcb->Draw("histsame");        
    ratCMS->Draw("E2same");
    grat0->Draw("2");
    //grat0->Draw("E");

    h_ratMCFO0->Draw("histsame");
    //ratPy->Draw("histsame");
    ratPymcc->Draw("histsame");
    //ratPymcb->Draw("histsame");        
    ratAL->Draw("E2same");     
    ratCMS->Draw("E2same");
    
    legInd->AddEntry(proYy0, "CMS c", "pl");
    legInd->AddEntry(h_ALpT, "ALICE c", "pl");        
    //legInd->AddEntry(h_Pyrap0, ("Pythia c+b #times " + toStr(SFforPy)).c_str(), "l");
    legInd->AddEntry(h_Pyrapmcc0, ("Pythia c #times " + toStr(SFforPy)).c_str(), "l");
    //legInd->AddEntry(h_Pyrapmcb0, ("Pythia b #times " + toStr(SFforPy)).c_str(), "l");        
    legInd->AddEntry(gr_FO0, "FONLL c", "fl");
    //legInd->AddEntry(h_Pyrap0, "|y| < 0.5", "");


    styleHist(h_Pyrap0, useColPy, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStPy, yMinPy, yMaxPy);
    styleHist(h_Pyrapmcc0, kGreen +2, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcc, yMinPy, yMaxPy);
    styleHist(h_Pyrapmcb0, kPink -9, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcb, yMinPy, yMaxPy);    
    styleHist(h_ALpT, useColAL, filStyAL, marStyAL, marSizAL, linWidAL, yOffAL, xOffAL, ploTitlePy, yTitlePy, xTitlePy, ylabSizAL, xlabSizAL, yTitSizAL, xTitSizAL, statHistAL, linStAL, yMinPy, yMaxPy);
    styleHist(proYy0, useColCM, filStyCM, marStyCM, marSizCM, linWidCM, yOffCM, xOffCM, ploTitlePy, yTitlePy, xTitlePy, ylabSizCM, xlabSizCM, yTitSizCM, xTitSizCM, statHistCM, linStCM, yMinPy, yMaxPy);
    styleHist(h_MCFOrap0, kCyan, filStyAL, marStyAL, marSizAL, linWidAL, yOffAL, xOffAL, ploTitlePy, yTitlePy, xTitlePy, ylabSizAL, xlabSizAL, yTitSizAL, xTitSizAL, statHistAL, 1, yMinPy, yMaxPy);
    
    
    styleHist(ratAL, useColAL, filStyAL, marStyAL, marSizAL, linWidAL, yOff_rat, xOff_rat, ploTitlePy, yTitle_rat, xTitlePy, ylabSiz_rat, xlabSiz_rat, yTitSiz_rat, xTitSiz_rat, statHistAL, linStAL, yMin_rat, yMax_rat);
    styleHist(ratCMS, useColCM, filStyCM, marStyCM, marSizCM, linWidAL, yOffCM, xOffCM, ploTitlePy, yTitlePy, xTitlePy, ylabSizCM, xlabSizCM, yTitSizCM, xTitSizCM, statHistCM, linStCM, yMinPy, yMaxPy);
    styleHist(ratPy, useColPy, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStPy, yMinPy, yMaxPy);
    styleHist(ratPymcc, kGreen +2, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcc, yMinPy, yMaxPy);
    styleHist(ratPymcb, kPink -9, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcb, yMinPy, yMaxPy);    
    styleHist(ratFOEH, kCyan, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStPy, yMinPy, yMaxPy);
    styleHist(ratFOEL, kCyan, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStPy, yMinPy, yMaxPy);
    styleGraph(grat0, kCyan, colAlphaFO, filStyFO, marStyFO, marSizFO, linStyFO, linWidFO);      
    styleHist(h_ratMCFO0, kCyan, filStyAL, marStyAL, marSizAL, linWidAL, yOffAL, xOffAL, ploTitlePy, yTitlePy, xTitlePy, ylabSizAL, xlabSizAL, yTitSizAL, xTitSizAL, statHistAL, 1, yMinPy, yMaxPy);

  TFile foutall("Xsecall.root","RECREATE");
  foutall.cd();
  h_MCFOrap0->Write();
  h_Pyrap0->Write();
  h_Pyrapmcc0->Write();
  h_Pyrapmcb0->Write();        
  h_ALpT->Write(); // ALICE
  proYy0->Write();
  h_ratMCFO0->Write();
  ratPy->Write();
  ratPymcc->Write();
  ratPymcb->Write();        
  ratAL->Write();     
  ratCMS->Write();
  foutall.Close();
  
    for(int index = 1; index < 12; ++index) {
      cout << "CMS point" << " " << index << ":" << " " << hrat_CMS->GetBinContent(index) << " " << "CMS uncert" << " " << index << ":" << " " << hrat_CMS->GetBinError(index) << "\n";
      cout << "ALICE point" << " " << index << ":" << " " << hrat_AL->GetBinContent(index) << " " << "ALICE uncert" << " " << index << ":" << " " << hrat_AL->GetBinError(index) << "\n";
      cout << "Pythia c+b point" << " " << index << ":" << " " << hrat_Py->GetBinContent(index) << " " << "Pythia c+b uncert" << " " << index << ":" << " " << hrat_Py->GetBinError(index) << "\n";
      cout << "Pythia c point" << " " << index << ":" << " " << hrat_Pymcc->GetBinContent(index) << " " << "Pythia c uncert" << " " << index << ":" << " " << hrat_Pymcc->GetBinError(index) << "\n";
      cout << "Pythia b point" << " " << index << ":" << " " << hrat_Pymcb->GetBinContent(index) << " " << "Pythia b uncert" << " " << index << ":" << " " << hrat_Pymcb->GetBinError(index) << "\n";
      cout << "FONLL point" << " " << index << ":" << " " << h_MCFOrap0->GetBinContent(index) << " " << "FONLL uncert (high)" << " " << index << ":" << " " << hrat_FOEH->GetBinError(index) << " " << "FONLL uncert (low)" << " " << index << ":" << " " << hrat_FOEL->GetBinError(index) << "\n";
      }  
  }
  else if (num == 1) {

    // 2 sbb utk CMS point 0-1 pT xde
    // 13 sbb 13-2 = 11 bins (drp 0-11)
    for (int pp = 2; pp < 13; ++pp) { 

      hrat_CMS->SetBinContent(pp, proYy0p5->GetBinContent(pp - 1));
      hrat_CMS->SetBinError(pp, proYy0p5->GetBinError(pp - 1));

      hrat_Py->SetBinContent(pp - 1, h_Pyrap0p5->GetBinContent(pp - 1));
      hrat_Py->SetBinError(pp - 1, h_Pyrap0p5->GetBinError(pp - 1));

      hrat_Pymcc->SetBinContent(pp - 1, h_Pyrapmcc0p5->GetBinContent(pp -1));
      hrat_Pymcc->SetBinError(pp - 1, h_Pyrapmcc0p5->GetBinError(pp -1));

      hrat_Pymcb->SetBinContent(pp - 1, h_Pyrapmcb0p5->GetBinContent(pp -1));
      hrat_Pymcb->SetBinError(pp - 1, h_Pyrapmcb0p5->GetBinError(pp -1));
      
      //cout << "hPy: " << h_Pyrap0p5->GetBinContent(pp - 1) << endl;
      //cout << "hratCMS: " << hrat_CMS->GetBinContent(pp - 1) << endl;

      // ref look num == 0
      gr_FO0p5->GetPoint(pp - 2, xx, yy);
      hrat_FOEH->SetBinContent(pp - 1, yy);
      hrat_FOEH->SetBinError(pp - 1, gr_FO0p5->GetErrorYhigh(pp - 2));
      hrat_FOEL->SetBinContent(pp - 1, yy);
      hrat_FOEL->SetBinError(pp - 1, gr_FO0p5->GetErrorYlow(pp - 2));    
    }

    TFile fout0p5("lala0p5.root","RECREATE");
    fout0p5.cd();
    hrat_FOEL->Write();
    fout0p5.Close();

    auto inF = std::unique_ptr<TFile>(TFile::Open("./lala0p5.root"));
    auto h_Clorap0p5 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inF->Get("hrat_FOEL")->Clone()) );

    // histograms w/o error to plot
    TH1D *h_MCFOrap0p5 = new TH1D("h_MCFOrap0p5", "h_MCFOrap0p5", v_pTBin.size() - 1, v_pTBin.data());
    
    for (int pp = 1; pp < 12; ++pp) { // 0 bis 10    
      h_MCFOrap0p5->SetBinContent(pp, h_Clorap0p5->GetBinContent(pp));
      //h_MCFOrap0p5->SetBinError(pp, h_Clorap0p5->GetBinError(pp));
      h_MCFOrap0p5->SetBinError(pp, 0.000000001);
    }    

    //h_Pyrap0p5->Draw("hist");
    h_Pyrapmcc0p5->Draw("hist");
    //h_Pyrapmcb0p5->Draw("hist same");           
    proYy0p5->Draw("PEX0 same");
    h_MCFOrap0p5->Draw("hist same");
    
    gr_FO0p5->Draw("2");    
    //gr_FO0p5->Draw("E");

    //h_Pyrap0p5->Draw("hist same");
    h_Pyrapmcc0p5->Draw("hist same");
    //h_Pyrapmcb0p5->Draw("hist same");       
    proYy0p5->Draw("PEX0 same");
      
    legInd->AddEntry(proYy0p5, "CMS c", "pl");
    //legInd->AddEntry(h_Pyrap0p5, ("Pythia c+b #times " + toStr(SFforPy)).c_str(), "l");
    legInd->AddEntry(h_Pyrapmcc0p5, ("Pythia c #times " + toStr(SFforPy)).c_str(), "l");
    //legInd->AddEntry(h_Pyrapmcb0p5, ("Pythia b #times " + toStr(SFforPy)).c_str(), "l");
    legInd->AddEntry(gr_FO0p5, "FONLL c", "fl");    
    //legInd->AddEntry(h_Pyrap0p5, "0.5 < |y| < 1.0", "");
    
    styleHist(h_Pyrap0p5, useColPy, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStPy, yMinPy, yMaxPy);
    styleHist(h_Pyrapmcc0p5, kGreen +2, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcc, yMinPy, yMaxPy);
    styleHist(h_Pyrapmcb0p5, kPink -9, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcb, yMinPy, yMaxPy);    
    styleHist(proYy0p5, useColCM, filStyCM, marStyCM, marSizCM, linWidAL, yOffCM, xOffCM, ploTitlePy, yTitlePy, xTitlePy, ylabSizCM, xlabSizCM, yTitSizCM, xTitSizCM, statHistCM, linStCM, yMinPy, yMaxPy);
    styleHist(h_MCFOrap0p5, kCyan, filStyAL, marStyAL, marSizAL, linWidAL, yOffAL, xOffAL, ploTitlePy, yTitlePy, xTitlePy, ylabSizAL, xlabSizAL, yTitSizAL, xTitSizAL, statHistAL, 1, yMinPy, yMaxPy);
    
    legInd->Draw();
    
    //new legend for rapidity bin
    stdL0->SetNColumns(1);  
    stdL0->AddEntry(h_Pyrap0p5, " 0.5 < |y| < 1.0", "");
    styleLeg(stdL0, 0, 0, 42, 0.05, 0, 0);
    stdL0->Draw(); // leg kene draw kat the latest overlap
    
    ratCMS->Divide(hrat_CMS, hrat_Pymcc, 1., 1.);
    ratPy->Divide(hrat_Py, hrat_Pymcc, 1., 1.);
    ratFOEH->Divide(hrat_FOEH, hrat_Pymcc, 1., 1.);
    ratFOEL->Divide(hrat_FOEL, hrat_Pymcc, 1., 1.);
    ratPymcc->Divide(hrat_Pymcc, hrat_Pymcc, 1., 1.);
    ratPymcb->Divide(hrat_Pymcb, hrat_Pymcc, 1., 1.);
    
    for (int ii = 1; ii < 12; ++ii) {
      gratC[ii-1] = ratFOEH->GetBinContent(ii); // can take EL also
      gratEH[ii-1] = ratFOEH->GetBinError(ii);
      gratEL[ii-1] = ratFOEL->GetBinError(ii);
      
      //cout << "BinCrat: " << ratFOEH->GetBinContent(ii) << endl;
    }
    
    auto grat0p5 = new TGraphAsymmErrors(n, x, gratC, exl, exh, gratEL, gratEH);  
    TH1D *h_ratMCFO0p5 = new TH1D("h_ratMCFO0p5", "h_ratMCFO0p5", v_pTBin.size() - 1, v_pTBin.data());

    for (int pp = 1; pp < 12; ++pp) { // 0 bis 10    
      h_ratMCFO0p5->SetBinContent(pp, ratFOEH->GetBinContent(pp));
      //h_MCFOrap0p5->SetBinError(pp, h_Clorap0p5->GetBinError(pp));
      // MUST put err eventho small, otherwise, go crazy
      h_ratMCFO0p5->SetBinError(pp, 0.000000001); 
    }
    
    c1->cd();
    stylePad(pad2, p2topMarg, p2botMarg, p2lefMarg, p2rigMarg, p2logY, p2logX);
    pad2->Draw();
    pad2->cd();
    pad2->SetGridy();
    
    ratCMS->GetYaxis()->SetNdivisions(507);
    ratCMS->GetXaxis()->SetNdivisions(507);   
    ratCMS->Draw("E2p");
    //ratPy->Draw("histsame");
    ratPymcc->Draw("histsame");
    //ratPymcb->Draw("histsame");    
    grat0p5->Draw("2");
    //grat0p5->Draw("E");
    
    h_ratMCFO0p5->Draw("histsame");
    //ratPy->Draw("histsame");
    ratCMS->Draw("E2same"); //PEX0same
    ratPymcc->Draw("histsame");
    //ratPymcb->Draw("histsame");    
    
    styleHist(ratCMS, useColCM, filStyCM, marStyCM, marSizCM, linWidAL, yOff_rat, xOff_rat, ploTitlePy, yTitle_rat, xTitlePy, ylabSiz_rat, xlabSiz_rat, yTitSiz_rat, xTitSiz_rat, statHistCM, linStCM, yMin_rat, yMax_rat);
    styleHist(ratPy, useColPy, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStPy, yMinPy, yMaxPy);
    styleHist(ratPymcc, kGreen +2, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcc, yMinPy, yMaxPy);
    styleHist(ratPymcb, kPink -9, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcb, yMinPy, yMaxPy); 
    styleGraph(grat0p5, kCyan, colAlphaFO, filStyFO, marStyFO, marSizFO, linStyFO, linWidFO);
    styleHist(h_ratMCFO0p5, kCyan, filStyAL, marStyAL, marSizAL, linWidAL, yOffAL, xOffAL, ploTitlePy, yTitlePy, xTitlePy, ylabSizAL, xlabSizAL, yTitSizAL, xTitSizAL, statHistAL, 1, yMinPy, yMaxPy);

 for(int index = 1; index < 12; ++index) {
      cout << "CMS point" << " " << index << ":" << " " << hrat_CMS->GetBinContent(index) << " " << "CMS uncert" << " " << index << ":" << " " << hrat_CMS->GetBinError(index) << "\n";
      cout << "Pythia c+b point" << " " << index << ":" << " " << hrat_Py->GetBinContent(index) << " " << "Pythia c+b uncert" << " " << index << ":" << " " << hrat_Py->GetBinError(index) << "\n";
      cout << "Pythia c point" << " " << index << ":" << " " << hrat_Pymcc->GetBinContent(index) << " " << "Pythia c uncert" << " " << index << ":" << " " << hrat_Pymcc->GetBinError(index) << "\n";
      cout << "Pythia b point" << " " << index << ":" << " " << hrat_Pymcb->GetBinContent(index) << " " << "Pythia b uncert" << " " << index << ":" << " " << hrat_Pymcb->GetBinError(index) << "\n";
      cout << "FONLL point" << " " << index << ":" << " " << h_MCFOrap0p5->GetBinContent(index) << " " << "FONLL uncert (high)" << " " << index << ":" << " " << hrat_FOEH->GetBinError(index) << " " << "FONLL uncert (low)" << " " << index << ":" << " " << hrat_FOEL->GetBinError(index) << "\n";
      }
  }
  
  else if (num == 2) {

    // 2 sbb utk CMS point 0-1 pT xde
    // 13 sbb 13-2 = 11 bins (drp 0-11)
    for (int pp = 2; pp < 13; ++pp) { 

      hrat_CMS->SetBinContent(pp, proYy1->GetBinContent(pp - 1));
      hrat_CMS->SetBinError(pp, proYy1->GetBinError(pp - 1));

      hrat_Py->SetBinContent(pp - 1, h_Pyrap1->GetBinContent(pp - 1));
      hrat_Py->SetBinError(pp - 1, h_Pyrap1->GetBinError(pp - 1));

      hrat_Pymcc->SetBinContent(pp - 1, h_Pyrapmcc1->GetBinContent(pp -1));
      hrat_Pymcc->SetBinError(pp - 1, h_Pyrapmcc1->GetBinError(pp -1));

      hrat_Pymcb->SetBinContent(pp - 1, h_Pyrapmcb1->GetBinContent(pp -1));
      hrat_Pymcb->SetBinError(pp - 1, h_Pyrapmcb1->GetBinError(pp -1));
      
      //cout << "hPy: " << h_Pyrap1->GetBinContent(pp - 1) << endl;
      //cout << "hratCMS: " << hrat_CMS->GetBinContent(pp - 1) << endl;

      // ref look num == 0
      gr_FO1->GetPoint(pp - 2, xx, yy);
      hrat_FOEH->SetBinContent(pp - 1, yy);
      hrat_FOEH->SetBinError(pp - 1, gr_FO1->GetErrorYhigh(pp - 2));
      hrat_FOEL->SetBinContent(pp - 1, yy);
      hrat_FOEL->SetBinError(pp - 1, gr_FO1->GetErrorYlow(pp - 2));    
    }

    TFile fout1("lala1.root","RECREATE");
    fout1.cd();
    hrat_FOEL->Write();
    fout1.Close();

    auto inF = std::unique_ptr<TFile>(TFile::Open("./lala1.root"));
    auto h_Clorap1 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inF->Get("hrat_FOEL")->Clone()) );

    // histograms w/o error to plot
    TH1D *h_MCFOrap1 = new TH1D("h_MCFOrap1", "h_MCFOrap1", v_pTBin.size() - 1, v_pTBin.data());
    
    for (int pp = 1; pp < 12; ++pp) { // 0 bis 10    
      h_MCFOrap1->SetBinContent(pp, h_Clorap1->GetBinContent(pp));
      //h_MCFOrap1->SetBinError(pp, h_Clorap1->GetBinError(pp));
      h_MCFOrap1->SetBinError(pp, 0.000000001);   
    
    }    

    //h_Pyrap1->Draw("hist");
    h_Pyrapmcc1->Draw("hist");
    //h_Pyrapmcb1->Draw("hist same");           
    proYy1->Draw("PEX0 same");
    h_MCFOrap1->Draw("hist same");
    
    gr_FO1->Draw("2");    
    //gr_FO1->Draw("E");

    //h_Pyrap1->Draw("hist same");
    h_Pyrapmcc1->Draw("hist same");
    //h_Pyrapmcb1->Draw("hist same");       
    proYy1->Draw("PEX0same");    
      
    legInd->AddEntry(proYy1, "CMS c", "pl");
    //legInd->AddEntry(h_Pyrap1, ("Pythia c+b #times " + toStr(SFforPy)).c_str(), "l");
    legInd->AddEntry(h_Pyrapmcc1, ("Pythia c #times " + toStr(SFforPy)).c_str(), "l");
    //legInd->AddEntry(h_Pyrapmcb1, ("Pythia b #times " + toStr(SFforPy)).c_str(), "l");
    legInd->AddEntry(gr_FO1, "FONLL c", "fl");    
    //legInd->AddEntry(h_Pyrap1, "0.5 < |y| < 1.0", "");
    
    styleHist(h_Pyrap1, useColPy, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStPy, yMinPy, yMaxPy);
    styleHist(h_Pyrapmcc1, kGreen +2, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcc, yMinPy, yMaxPy);
    styleHist(h_Pyrapmcb1, kPink -9, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcb, yMinPy, yMaxPy);    
    styleHist(proYy1, useColCM, filStyCM, marStyCM, marSizCM, linWidAL, yOffCM, xOffCM, ploTitlePy, yTitlePy, xTitlePy, ylabSizCM, xlabSizCM, yTitSizCM, xTitSizCM, statHistCM, linStCM, yMinPy, yMaxPy);
    styleHist(h_MCFOrap1, kCyan, filStyAL, marStyAL, marSizAL, linWidAL, yOffAL, xOffAL, ploTitlePy, yTitlePy, xTitlePy, ylabSizAL, xlabSizAL, yTitSizAL, xTitSizAL, statHistAL, 1, yMinPy, yMaxPy);
    
    legInd->Draw();

    //new legend for rapidity bin
    stdL0->SetNColumns(1);  
    stdL0->AddEntry(h_Pyrap0, "1 < |y| < 1.5", "");
    styleLeg(stdL0, 0, 0, 42, 0.05, 0, 0);
    stdL0->Draw(); // leg kene draw kat the latest overlap
    
    ratCMS->Divide(hrat_CMS, hrat_Pymcc, 1., 1.);
    ratPy->Divide(hrat_Py, hrat_Pymcc, 1., 1.);
    ratFOEH->Divide(hrat_FOEH, hrat_Pymcc, 1., 1.);
    ratFOEL->Divide(hrat_FOEL, hrat_Pymcc, 1., 1.);
    ratPymcc->Divide(hrat_Pymcc, hrat_Pymcc, 1., 1.);
    ratPymcb->Divide(hrat_Pymcb, hrat_Pymcc, 1., 1.);
    
    for (int ii = 1; ii < 12; ++ii) {
      gratC[ii-1] = ratFOEH->GetBinContent(ii); // can take EL also
      gratEH[ii-1] = ratFOEH->GetBinError(ii);
      gratEL[ii-1] = ratFOEL->GetBinError(ii);
      
      //cout << "BinCrat: " << ratFOEH->GetBinContent(ii) << endl;
    }
    
    auto grat1 = new TGraphAsymmErrors(n, x, gratC, exl, exh, gratEL, gratEH);  
    TH1D *h_ratMCFO1 = new TH1D("h_ratMCFO1", "h_ratMCFO1", v_pTBin.size() - 1, v_pTBin.data());

    for (int pp = 1; pp < 12; ++pp) { // 0 bis 10    
      h_ratMCFO1->SetBinContent(pp, ratFOEH->GetBinContent(pp));
      //h_MCFOrap1->SetBinError(pp, h_Clorap1->GetBinError(pp));
      // MUST put err eventho small, otherwise, go crazy
      h_ratMCFO1->SetBinError(pp, 0.000000001); 
    }
    
    c1->cd();
    stylePad(pad2, p2topMarg, p2botMarg, p2lefMarg, p2rigMarg, p2logY, p2logX);
    pad2->Draw();
    pad2->cd();
    pad2->SetGridy();
    
    ratCMS->GetYaxis()->SetNdivisions(507);
    ratCMS->GetXaxis()->SetNdivisions(507);   
    ratCMS->Draw("E2p");
    //ratPy->Draw("histsame");
    ratPymcc->Draw("histsame");
    //ratPymcb->Draw("histsame");    
    grat1->Draw("2");
    //grat1->Draw("E");
    
    h_ratMCFO1->Draw("histsame");
    //ratPy->Draw("histsame");
    ratCMS->Draw("E2same"); //PEX0same
    ratPymcc->Draw("histsame");
    //ratPymcb->Draw("histsame");    
    
    styleHist(ratCMS, useColCM, filStyCM, marStyCM, marSizCM, linWidAL, yOff_rat, xOff_rat, ploTitlePy, yTitle_rat, xTitlePy, ylabSiz_rat, xlabSiz_rat, yTitSiz_rat, xTitSiz_rat, statHistCM, linStCM, yMin_rat, yMax_rat);
    styleHist(ratPy, useColPy, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStPy, yMinPy, yMaxPy);
    styleHist(ratPymcc, kGreen +2, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcc, yMinPy, yMaxPy);
    styleHist(ratPymcb, kPink -9, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcb, yMinPy, yMaxPy); 
    styleGraph(grat1, kCyan, colAlphaFO, filStyFO, marStyFO, marSizFO, linStyFO, linWidFO);
    styleHist(h_ratMCFO1, kCyan, filStyAL, marStyAL, marSizAL, linWidAL, yOffAL, xOffAL, ploTitlePy, yTitlePy, xTitlePy, ylabSizAL, xlabSizAL, yTitSizAL, xTitSizAL, statHistAL, 1, yMinPy, yMaxPy);
  

 for(int index = 1; index < 12; ++index) {
      cout << "CMS point" << " " << index << ":" << " " << hrat_CMS->GetBinContent(index) << " " << "CMS uncert" << " " << index << ":" << " " << hrat_CMS->GetBinError(index) << "\n";
      cout << "Pythia c+b point" << " " << index << ":" << " " << hrat_Py->GetBinContent(index) << " " << "Pythia c+b uncert" << " " << index << ":" << " " << hrat_Py->GetBinError(index) << "\n";
      cout << "Pythia c point" << " " << index << ":" << " " << hrat_Pymcc->GetBinContent(index) << " " << "Pythia c uncert" << " " << index << ":" << " " << hrat_Pymcc->GetBinError(index) << "\n";
      cout << "Pythia b point" << " " << index << ":" << " " << hrat_Pymcb->GetBinContent(index) << " " << "Pythia b uncert" << " " << index << ":" << " " << hrat_Pymcb->GetBinError(index) << "\n";
      cout << "FONLL point" << " " << index << ":" << " " << h_MCFOrap1->GetBinContent(index) << " " << "FONLL uncert (high)" << " " << index << ":" << " " << hrat_FOEH->GetBinError(index) << " " << "FONLL uncert (low)" << " " << index << ":" << " " << hrat_FOEL->GetBinError(index) << "\n";
      }
  }
  
 
  
  else if (num == 3) {

    // 2 sbb utk CMS point 0-1 pT xde
    // 13 sbb 13-2 = 11 bins (drp 0-11)
    for (int pp = 2; pp < 13; ++pp) { 

      hrat_CMS->SetBinContent(pp, proYy1p5->GetBinContent(pp - 1));
      hrat_CMS->SetBinError(pp, proYy1p5->GetBinError(pp - 1));

      hrat_Py->SetBinContent(pp - 1, h_Pyrap1p5->GetBinContent(pp -1));
      hrat_Py->SetBinError(pp - 1, h_Pyrap1p5->GetBinError(pp -1));

      hrat_Pymcc->SetBinContent(pp - 1, h_Pyrapmcc1p5->GetBinContent(pp -1));
      hrat_Pymcc->SetBinError(pp - 1, h_Pyrapmcc1p5->GetBinError(pp -1));

      hrat_Pymcb->SetBinContent(pp - 1, h_Pyrapmcb1p5->GetBinContent(pp -1));
      hrat_Pymcb->SetBinError(pp - 1, h_Pyrapmcb1p5->GetBinError(pp -1));      
      //cout << "hPy: " << h_Pyrap1p5->GetBinContent(pp - 1) << endl;
      //cout << "hratCMS: " << hrat_CMS->GetBinContent(pp - 1) << endl;

      gr_FO1p5->GetPoint(pp - 2, xx, yy);
      hrat_FOEH->SetBinContent(pp - 1, yy);
      hrat_FOEH->SetBinError(pp - 1, gr_FO1p5->GetErrorYhigh(pp - 2));
      hrat_FOEL->SetBinContent(pp - 1, yy);
      hrat_FOEL->SetBinError(pp - 1, gr_FO1p5->GetErrorYlow(pp - 2));      
    }

    TFile fout1p5("lala1p5.root","RECREATE");
    fout1p5.cd();
    hrat_FOEL->Write();
    fout1p5.Close();

    auto inF = std::unique_ptr<TFile>(TFile::Open("./lala1p5.root"));
    auto h_Clorap1p5 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inF->Get("hrat_FOEL")->Clone()) );

  // histograms w/o error to plot
  TH1D *h_MCFOrap1p5 = new TH1D("h_MCFOrap1p5", "h_MCFOrap1p5", v_pTBin.size() - 1, v_pTBin.data());
    
  for (int pp = 1; pp < 12; ++pp) { // 0 bis 10    
    h_MCFOrap1p5->SetBinContent(pp, h_Clorap1p5->GetBinContent(pp));
    //h_MCFOrap1p5->SetBinError(pp, h_Clorap1p5->GetBinError(pp));
    h_MCFOrap1p5->SetBinError(pp, 0.000000001);   
    
  }
    
  //h_Pyrap1p5->Draw("hist ");
    h_Pyrapmcc1p5->Draw("hist");
    //h_Pyrapmcb1p5->Draw("hist same");        
    proYy1p5->Draw("PEX0 same");
    h_MCFOrap1p5->Draw("hist same");
    
    gr_FO1p5->Draw("2");    
    //gr_FO1p5->Draw("E");
    
    //h_Pyrap1p5->Draw("hist same");
    h_Pyrapmcc1p5->Draw("hist same");
    //h_Pyrapmcb1p5->Draw("hist same");            
    proYy1p5->Draw("PEX0 same");
    
    //legInd->AddEntry(proYy1p5, "CMS c", "pl");
    //legInd->AddEntry(h_Pyrap1p5, ("Pythia c+b #times " + toStr(SFforPy)).c_str(), "l");
    legInd->AddEntry(h_Pyrapmcc1p5, ("Pythia c #times " + toStr(SFforPy)).c_str(), "l");
    //legInd->AddEntry(h_Pyrapmcb1p5, ("Pythia b #times " + toStr(SFforPy)).c_str(), "l");
    legInd->AddEntry(gr_FO1p5, "FONLL c", "fl");    
    //legInd->AddEntry(h_Pyrap1p5, "1.5 < |y| < 2.0", "");
    
    styleHist(h_Pyrap1p5, useColPy, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStPy, yMinPy, yMaxPy);
    styleHist(h_Pyrapmcc1p5, kGreen +2, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcc, yMinPy, yMaxPy);
    styleHist(h_Pyrapmcb1p5, kPink -9, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcb, yMinPy, yMaxPy);    
    styleHist(proYy1p5, useColCM, filStyCM, marStyCM, marSizCM, linWidAL, yOffCM, xOffCM, ploTitlePy, yTitlePy, xTitlePy, ylabSizCM, xlabSizCM, yTitSizCM, xTitSizCM, statHistCM, linStCM, yMinPy, yMaxPy);
    styleHist(h_MCFOrap1p5, kCyan, filStyAL, marStyAL, marSizAL, linWidAL, yOffAL, xOffAL, ploTitlePy, yTitlePy, xTitlePy, ylabSizAL, xlabSizAL, yTitSizAL, xTitSizAL, statHistAL, 1, yMinPy, yMaxPy);
    
    legInd->Draw();

    //new legend for rapidity bin
    stdL0->SetNColumns(1);  
    stdL0->AddEntry(h_Pyrap0, "1.5 < |y| < 2.0", "");
    styleLeg(stdL0, 0, 0, 42, 0.05, 0, 0);
    stdL0->Draw(); // leg kene draw kat the latest overlap
    
    ratCMS->Divide(hrat_CMS, hrat_Pymcc, 1., 1.);
    ratPy->Divide(hrat_Py, hrat_Pymcc, 1., 1.);
    ratPymcc->Divide(hrat_Pymcc, hrat_Pymcc, 1., 1.);
    ratPymcb->Divide(hrat_Pymcb, hrat_Pymcc, 1., 1.);        
    ratFOEH->Divide(hrat_FOEH, hrat_Pymcc, 1., 1.);
    ratFOEL->Divide(hrat_FOEL, hrat_Pymcc, 1., 1.);

    for (int ii = 1; ii < 12; ++ii) {
      gratC[ii-1] = ratFOEH->GetBinContent(ii); // can take EL also
      gratEH[ii-1] = ratFOEH->GetBinError(ii);
      gratEL[ii-1] = ratFOEL->GetBinError(ii);
      
      //cout << "BinCrat: " << ratFOEH->GetBinContent(ii) << endl;
    }
    
    auto grat1p5 = new TGraphAsymmErrors(n, x, gratC, exl, exh, gratEL, gratEH);
    TH1D *h_ratMCFO1p5 = new TH1D("h_ratMCFO1p5", "h_ratMCFO1p5", v_pTBin.size() - 1, v_pTBin.data());

    for (int pp = 1; pp < 12; ++pp) { // 0 bis 10    
      h_ratMCFO1p5->SetBinContent(pp, ratFOEH->GetBinContent(pp));
      //h_MCFOrap1p5->SetBinError(pp, h_Clorap1p5->GetBinError(pp));
      // MUST put err eventho small, otherwise, go crazy
      h_ratMCFO1p5->SetBinError(pp, 0.000000001); 
    }
    
    c1->cd();
    stylePad(pad2, p2topMarg, p2botMarg, p2lefMarg, p2rigMarg, p2logY, p2logX);
    pad2->Draw();
    pad2->cd();
    pad2->SetGridy();
    
    ratCMS->GetYaxis()->SetNdivisions(507);
    ratCMS->GetXaxis()->SetNdivisions(507);   
    ratCMS->Draw("E2");
    //ratPy->Draw("histsame");
    ratPymcc->Draw("histsame");
    //ratPymcb->Draw("histsame");
    
    grat1p5->Draw("2");
    //grat1p5->Draw("E");

    h_ratMCFO1p5->Draw("histsame");    
    //ratPy->Draw("histsame");    
    ratCMS->Draw("E2same");
    ratPymcc->Draw("histsame");
    //ratPymcb->Draw("histsame");
    
    styleHist(ratCMS, useColCM, filStyCM, marStyCM, marSizCM, linWidAL, yOff_rat, xOff_rat, ploTitlePy, yTitle_rat, xTitlePy, ylabSiz_rat, xlabSiz_rat, yTitSiz_rat, xTitSiz_rat, statHistCM, linStCM, yMin_rat, 2.899);
    styleHist(ratPy, useColPy, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStPy, yMinPy, yMaxPy);
    styleHist(ratPymcc, kGreen +2, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcc, yMinPy, yMaxPy);
    styleHist(ratPymcb, kPink -9, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcb, yMinPy, yMaxPy);    
    styleGraph(grat1p5, kCyan, colAlphaFO, filStyFO, marStyFO, marSizFO, linStyFO, linWidFO);
    styleHist(h_ratMCFO1p5, kCyan, filStyAL, marStyAL, marSizAL, linWidAL, yOffAL, xOffAL, ploTitlePy, yTitlePy, xTitlePy, ylabSizAL, xlabSizAL, yTitSizAL, xTitSizAL, statHistAL, 1, yMinPy, yMaxPy);

 for(int index = 1; index < 12; ++index) {
      cout << "CMS point" << " " << index << ":" << " " << hrat_CMS->GetBinContent(index) << " " << "CMS uncert" << " " << index << ":" << " " << hrat_CMS->GetBinError(index) << "\n";
      cout << "Pythia c+b point" << " " << index << ":" << " " << hrat_Py->GetBinContent(index) << " " << "Pythia c+b uncert" << " " << index << ":" << " " << hrat_Py->GetBinError(index) << "\n";
      cout << "Pythia c point" << " " << index << ":" << " " << hrat_Pymcc->GetBinContent(index) << " " << "Pythia c uncert" << " " << index << ":" << " " << hrat_Pymcc->GetBinError(index) << "\n";
      cout << "Pythia b point" << " " << index << ":" << " " << hrat_Pymcb->GetBinContent(index) << " " << "Pythia b uncert" << " " << index << ":" << " " << hrat_Pymcb->GetBinError(index) << "\n";
      cout << "FONLL point" << " " << index << ":" << " " << h_MCFOrap1p5->GetBinContent(index) << " " << "FONLL uncert (high)" << " " << index << ":" << " " << hrat_FOEH->GetBinError(index) << " " << "FONLL uncert (low)" << " " << index << ":" << " " << hrat_FOEL->GetBinError(index) << "\n";
      }
  }
  else if(num == 4) {
    // 2 sbb utk CMS point 0-1 pT xde
    // 13 sbb 13-2 = 11 bins (drp 0-11)
    for (int pp = 2; pp < 13; ++pp) { 

      hrat_LH->SetBinContent(pp - 1, hpT_LHCb->GetBinContent(pp -1));
      hrat_LH->SetBinError(pp - 1, hpT_LHCb->GetBinError(pp -1));
      
      hrat_CMS->SetBinContent(pp, proYy2->GetBinContent(pp - 1));
      hrat_CMS->SetBinError(pp, proYy2->GetBinError(pp - 1));

      hrat_Py->SetBinContent(pp - 1, h_Pyrap2->GetBinContent(pp -1));
      hrat_Py->SetBinError(pp - 1, h_Pyrap2->GetBinError(pp -1));

      hrat_Pymcc->SetBinContent(pp - 1, h_Pyrapmcc2->GetBinContent(pp -1));
      hrat_Pymcc->SetBinError(pp - 1, h_Pyrapmcc2->GetBinError(pp -1));

      hrat_Pymcb->SetBinContent(pp - 1, h_Pyrapmcb2->GetBinContent(pp -1));
      hrat_Pymcb->SetBinError(pp - 1, h_Pyrapmcb2->GetBinError(pp -1));      
      //cout << "hPy: " << h_Pyrap2->GetBinContent(pp - 1) << endl;
      //cout << "hratCMS: " << hrat_CMS->GetBinContent(pp - 1) << endl;

      gr_FO2->GetPoint(pp - 2, xx, yy);
      hrat_FOEH->SetBinContent(pp - 1, yy);
      hrat_FOEH->SetBinError(pp - 1, gr_FO2->GetErrorYhigh(pp - 2));
      hrat_FOEL->SetBinContent(pp - 1, yy);
      hrat_FOEL->SetBinError(pp - 1, gr_FO2->GetErrorYlow(pp - 2));       
    }
   
    TFile fout2("lala2.root","RECREATE");
    fout2.cd();
    hrat_FOEL->Write();
    fout2.Close();

    auto inF = std::unique_ptr<TFile>(TFile::Open("./lala2.root"));
    auto h_Clorap2 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inF->Get("hrat_FOEL")->Clone()) );

  // histograms w/o error to plot
  TH1D *h_MCFOrap2 = new TH1D("h_MCFOrap2", "h_MCFOrap2", v_pTBin.size() - 1, v_pTBin.data());
    
  for (int pp = 1; pp < 12; ++pp) { // 0 bis 10    
    h_MCFOrap2->SetBinContent(pp, h_Clorap2->GetBinContent(pp));
    //h_MCFOrap2->SetBinError(pp, h_Clorap2->GetBinError(pp));
    h_MCFOrap2->SetBinError(pp, 0.000000001);   
    
  }

  //h_Pyrap2->Draw("hist ");
    h_Pyrapmcc2->Draw("hist");
    //h_Pyrapmcb2->Draw("hist same");        
    hpT_LHCb->Draw("PEX0 same"); // LHCb
    proYy2->Draw("PEX0 same");
    h_MCFOrap2->Draw("hist same");
    
    gr_FO2->Draw("2");    
    //gr_FO2->Draw("E");
    
    //h_Pyrap2->Draw("hist same");
    h_Pyrapmcc2->Draw("hist same");
    //h_Pyrapmcb2->Draw("hist same");            
    hpT_LHCb->Draw("PEX0 same"); // LHCb
    proYy2->Draw("PEX0 same");
    
    legInd->AddEntry(proYy2, "CMS c", "pl");
    legInd->AddEntry(hpT_LHCb, "LHCb c", "pl");
    //legInd->AddEntry(h_Pyrap2, ("Pythia c+b #times " + toStr(SFforPy)).c_str(), "l");
    legInd->AddEntry(h_Pyrapmcc2, ("Pythia c #times " + toStr(SFforPy)).c_str(), "l");
    //legInd->AddEntry(h_Pyrapmcb2, ("Pythia b #times " + toStr(SFforPy)).c_str(), "l");
    legInd->AddEntry(gr_FO2, "FONLL c", "fl");    
    //legInd->AddEntry(h_Pyrap2, "2.0 < y < 2.5", "");
    
    styleHist(h_Pyrap2, useColPy, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStPy, yMinPy, yMaxPy);
    styleHist(h_Pyrapmcc2, kGreen +2, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcc, yMinPy, yMaxPy);
    styleHist(h_Pyrapmcb2, kPink -9, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcb, yMinPy, yMaxPy);    
    styleHist(hpT_LHCb, useColLH, filStyCM, marStyLH, marSizCM, linWidAL, yOffCM, xOffCM, ploTitlePy, yTitlePy, xTitlePy, ylabSizCM, xlabSizCM, yTitSizCM, xTitSizCM, statHistCM, linStCM, yMinPy, yMaxPy);     
    styleHist(proYy2, useColCM, filStyCM, marStyCM, marSizCM, linWidAL, yOffCM, xOffCM, ploTitlePy, yTitlePy, xTitlePy, ylabSizCM, xlabSizCM, yTitSizCM, xTitSizCM, statHistCM, linStCM, yMinPy, yMaxPy);
    styleHist(h_MCFOrap2, kCyan, filStyAL, marStyAL, marSizAL, linWidAL, yOffAL, xOffAL, ploTitlePy, yTitlePy, xTitlePy, ylabSizAL, xlabSizAL, yTitSizAL, xTitSizAL, statHistAL, 1, yMinPy, yMaxPy);
  
    legInd->Draw();
    
    //new legend for rapidity bin
    stdL0->SetNColumns(1);  
    stdL0->AddEntry(h_Pyrap0, "2.0 < |y| < 2.5", "");
    styleLeg(stdL0, 0, 0, 42, 0.05, 0, 0);
    stdL0->Draw(); // leg kene draw kat the latest overlap
    
  ratCMS->Divide(hrat_CMS, hrat_Pymcc, 1., 1.);
  ratLH->Divide(hrat_LH, hrat_Pymcc, 1., 1.);
  ratPy->Divide(hrat_Py, hrat_Pymcc, 1., 1.);
  ratPymcc->Divide(hrat_Pymcc, hrat_Pymcc, 1., 1.);
  ratPymcb->Divide(hrat_Pymcb, hrat_Pymcc, 1., 1.);    
  ratFOEH->Divide(hrat_FOEH, hrat_Pymcc, 1., 1.);
  ratFOEL->Divide(hrat_FOEL, hrat_Pymcc, 1., 1.);

    for (int ii = 1; ii < 12; ++ii) {
      gratC[ii-1] = ratFOEH->GetBinContent(ii); // can take EL also
      gratEH[ii-1] = ratFOEH->GetBinError(ii);
      gratEL[ii-1] = ratFOEL->GetBinError(ii);
      
      //cout << "BinCrat: " << ratFOEH->GetBinContent(ii) << endl;
    }
    
    auto grat2 = new TGraphAsymmErrors(n, x, gratC, exl, exh, gratEL, gratEH);
    TH1D *h_ratMCFO2 = new TH1D("h_ratMCFO2", "h_ratMCFO2", v_pTBin.size() - 1, v_pTBin.data());

    for (int pp = 1; pp < 12; ++pp) { // 0 bis 10    
      h_ratMCFO2->SetBinContent(pp, ratFOEH->GetBinContent(pp));
      //h_MCFO0->SetBinError(pp, h_Clorap2->GetBinError(pp));
      // MUST put err eventho small, otherwise, go crazy
      h_ratMCFO2->SetBinError(pp, 0.000000001); 
    }
    
    c1->cd();
    stylePad(pad2, p2topMarg, p2botMarg, p2lefMarg, p2rigMarg, p2logY, p2logX);
    pad2->Draw();
    pad2->cd();
    pad2->SetGridy();
    
    ratLH->GetYaxis()->SetNdivisions(507);
    ratLH->GetXaxis()->SetNdivisions(507);
    ratLH->Draw("E2");
    //ratPy->Draw("histsame");
    ratPymcc->Draw("histsame");
    //ratPymcb->Draw("histsame");            
    ratCMS->Draw("E2same");    
    grat2->Draw("2");
    //grat2->Draw("E");
    
    h_ratMCFO2->Draw("histsame");
    //ratPy->Draw("histsame");
    ratPymcc->Draw("histsame");
    //ratPymcb->Draw("histsame");                
    ratLH->Draw("E2same");
    ratCMS->Draw("E2same");    
    
    
    styleHist(ratCMS, useColCM, filStyCM, marStyCM, marSizCM, linWidAL, yOff_rat, xOff_rat, ploTitlePy, yTitle_rat, xTitlePy, ylabSiz_rat, xlabSiz_rat, yTitSiz_rat, xTitSiz_rat, statHistCM, linStCM, yMin_rat, 2.499);
    styleHist(ratLH, useColLH, filStyCM, marStyLH, marSizCM, linWidAL, yOff_rat, xOff_rat, ploTitlePy, yTitle_rat, xTitlePy, ylabSiz_rat, xlabSiz_rat, yTitSiz_rat, xTitSiz_rat, statHistCM, linStCM, yMin_rat, yMax_rat); // LHCb      
    styleHist(ratPy, useColPy, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStPy, yMinPy, yMaxPy);
    styleHist(ratPymcc, kGreen +2, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcc, yMinPy, yMaxPy);
    styleHist(ratPymcb, kPink -9, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitlePy, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcb, yMinPy, yMaxPy);    
    styleGraph(grat2, kCyan, colAlphaFO, filStyFO, marStyFO, marSizFO, linStyFO, linWidFO);
    styleHist(h_ratMCFO2, kCyan, filStyAL, marStyAL, marSizAL, linWidAL, yOffAL, xOffAL, ploTitlePy, yTitlePy, xTitlePy, ylabSizAL, xlabSizAL, yTitSizAL, xTitSizAL, statHistAL, 1, yMinPy, yMaxPy);


 for(int index = 1; index < 12; ++index) {
      cout << "CMS point" << " " << index << ":" << " " << hrat_CMS->GetBinContent(index) << " " << "CMS uncert" << " " << index << ":" << " " << hrat_CMS->GetBinError(index) << "\n";
      cout << "LHCb point" << " " << index << ":" << " " << hrat_LH->GetBinContent(index) << " " << "LHCb uncert" << " " << index << ":" << " " << hrat_LH->GetBinError(index) << "\n";      
      cout << "Pythia c+b point" << " " << index << ":" << " " << hrat_Py->GetBinContent(index) << " " << "Pythia c+b uncert" << " " << index << ":" << " " << hrat_Py->GetBinError(index) << "\n";
      cout << "Pythia c point" << " " << index << ":" << " " << hrat_Pymcc->GetBinContent(index) << " " << "Pythia c uncert" << " " << index << ":" << " " << hrat_Pymcc->GetBinError(index) << "\n";
      cout << "Pythia b point" << " " << index << ":" << " " << hrat_Pymcb->GetBinContent(index) << " " << "Pythia b uncert" << " " << index << ":" << " " << hrat_Pymcb->GetBinError(index) << "\n";
      cout << "FONLL point" << " " << index << ":" << " " << h_MCFOrap2->GetBinContent(index) << " " << "FONLL uncert (high)" << " " << index << ":" << " " << hrat_FOEH->GetBinError(index) << " " << "FONLL uncert (low)" << " " << index << ":" << " " << hrat_FOEL->GetBinError(index) << "\n";
      }
  }
  else {

    for (int ii = 0; ii < 12; ++ii) {
      ynew0[ii] = ynew0[ii] * SFCombpT0;
      eylnew0[ii] = eylnew0[ii] * SFCombpT0;
      eyhnew0[ii] = eyhnew0[ii] * SFCombpT0;
      
      ynew0p5[ii] = ynew0p5[ii] * SFCombpT0p5;
      eylnew0p5[ii] = eylnew0p5[ii] * SFCombpT0p5;
      eyhnew0p5[ii] = eyhnew0p5[ii] * SFCombpT0p5;
      
      ynew1[ii] = ynew1[ii] * SFCombpT1;
      eylnew1[ii] = eylnew1[ii] * SFCombpT1;
      eyhnew1[ii] = eyhnew1[ii] * SFCombpT1;

      ynew1p5[ii] = ynew1p5[ii] * SFCombpT1p5;
      eylnew1p5[ii] = eylnew1p5[ii] * SFCombpT1p5;
      eyhnew1p5[ii] = eyhnew1p5[ii] * SFCombpT1p5;    
    
      ynew2[ii] = ynew2[ii] * SFCombpT2;
      eylnew2[ii] = eylnew2[ii] * SFCombpT2;
      eyhnew2[ii] = eyhnew2[ii] * SFCombpT2;
      
      //cout << "ynew: " << ynew[ii] << " " << "eylew: " << eylnew[ii] << endl;
    }
   
    auto gr_FO0 = new TGraphAsymmErrors(n, x, ynew0, exl, exh, eylnew0, eyhnew0);  
    auto gr_FO0p5 = new TGraphAsymmErrors(n, x, ynew0p5, exl, exh, eylnew0p5, eyhnew0p5);  
    auto gr_FO1 = new TGraphAsymmErrors(n, x, ynew1, exl, exh, eylnew1, eyhnew1);  
    auto gr_FO1p5 = new TGraphAsymmErrors(n, x, ynew1p5, exl, exh, eylnew1p5, eyhnew1p5);  
    auto gr_FO2 = new TGraphAsymmErrors(n, x, ynew2, exl, exh, eylnew2, eyhnew2);  

    styleGraph(gr_FO0, kCyan, colAlphaFO, filStyFO, marStyFO, marSizFO, linStyFO, linWidFO);  
    styleGraph(gr_FO0p5, kCyan, colAlphaFO, filStyFO, marStyFO, marSizFO, linStyFO, linWidFO);  
    styleGraph(gr_FO1, kCyan, colAlphaFO, filStyFO, marStyFO, marSizFO, linStyFO, linWidFO);  
    styleGraph(gr_FO1p5, kCyan, colAlphaFO, filStyFO, marStyFO, marSizFO, linStyFO, linWidFO);  
    styleGraph(gr_FO2, kCyan, colAlphaFO, filStyFO, marStyFO, marSizFO, linStyFO, linWidFO);  
    
    c1->cd();
    styleCan(c1, 0.03, 0.12, 0.18, 0.015, 1, 0);  

    // Draw the histograms
    h_Pyrap0->Scale(SFCombpT0);
    proYy0->Scale(SFCombpT0);
    h_ALpT->Scale(SFCombpT0);
    h_Pyrapmcc0->Scale(SFCombpT0);
    h_Pyrapmcb0->Scale(SFCombpT0);
    
    h_Pyrap0p5->Scale(SFCombpT0p5);
    proYy0p5->Scale(SFCombpT0p5);
    h_Pyrapmcc0p5->Scale(SFCombpT0p5);
    h_Pyrapmcb0p5->Scale(SFCombpT0p5);
    
    h_Pyrap1->Scale(SFCombpT1);
    proYy1->Scale(SFCombpT1);
    h_Pyrapmcc1->Scale(SFCombpT1);
    h_Pyrapmcb1->Scale(SFCombpT1);
    
    h_Pyrap1p5->Scale(SFCombpT1p5);
    proYy1p5->Scale(SFCombpT1p5);
    h_Pyrapmcc1p5->Scale(SFCombpT1p5);
    h_Pyrapmcb1p5->Scale(SFCombpT1p5);
    
    h_Pyrap2->Scale(SFCombpT2);
    proYy2->Scale(SFCombpT2);
    hpT_LHCb->Scale(SFCombpT2);
    h_Pyrapmcc2->Scale(SFCombpT2);
    h_Pyrapmcb2->Scale(SFCombpT2);

    for (int pp = 2; pp < 13; ++pp) { 

      gr_FO0->GetPoint(pp - 2, xx0, yy0);
      gr_FO0->GetErrorYhigh(pp - 2);
      gr_FO0->GetErrorYlow(pp - 2);
      
      gr_FO0p5->GetPoint(pp - 2, xx0p5, yy0p5);
      gr_FO0p5->GetErrorYhigh(pp - 2);
      gr_FO0p5->GetErrorYlow(pp - 2);
      
      gr_FO1->GetPoint(pp - 2, xx1, yy1);
      gr_FO1->GetErrorYhigh(pp - 2);
      gr_FO1->GetErrorYlow(pp - 2);
      
      gr_FO1p5->GetPoint(pp - 2, xx1p5, yy1p5);
      gr_FO1p5->GetErrorYhigh(pp - 2);
      gr_FO1p5->GetErrorYlow(pp - 2);
      
      gr_FO2->GetPoint(pp - 2, xx2, yy2);
      gr_FO2->GetErrorYhigh(pp - 2);
      gr_FO2->GetErrorYlow(pp - 2);
      
      hrat_FOEL0->SetBinContent(pp - 1, yy0);
      hrat_FOEL0->SetBinError(pp - 1, gr_FO0->GetErrorYlow(pp - 2));
      hrat_FOEL0p5->SetBinContent(pp - 1, yy0p5);
      hrat_FOEL0p5->SetBinError(pp - 1, gr_FO0p5->GetErrorYlow(pp - 2));
      hrat_FOEL1->SetBinContent(pp - 1, yy1);
      hrat_FOEL1->SetBinError(pp - 1, gr_FO1->GetErrorYlow(pp - 2));
      hrat_FOEL1p5->SetBinContent(pp - 1, yy1p5);
      hrat_FOEL1p5->SetBinError(pp - 1, gr_FO1p5->GetErrorYlow(pp - 2));
      hrat_FOEL2->SetBinContent(pp - 1, yy2);
      hrat_FOEL2->SetBinError(pp - 1, gr_FO2->GetErrorYlow(pp - 2));      
    }

    TFile foutall("lalaall.root","RECREATE");
    foutall.cd();
    hrat_FOEL0->Write();   
    hrat_FOEL0p5->Write();   
    hrat_FOEL1->Write();   
    hrat_FOEL1p5->Write();   
    hrat_FOEL2->Write();
    foutall.Close();

    auto inF = std::unique_ptr<TFile>(TFile::Open("./lalaall.root"));
    auto h_Clo0 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inF->Get("hrat_FOEL0")->Clone()) );    
    auto h_Clo0p5 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inF->Get("hrat_FOEL0p5")->Clone()) );
    auto h_Clo1 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inF->Get("hrat_FOEL1")->Clone()) );    
    auto h_Clo1p5 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inF->Get("hrat_FOEL1p5")->Clone()) );
    auto h_Clo2 = std::unique_ptr<TH1>(dynamic_cast<TH1 *>(inF->Get("hrat_FOEL2")->Clone()) );

    TH1D *h_MCFO0 = new TH1D("h_MCFO0", "h_MCFO0", v_pTBin.size() - 1, v_pTBin.data());
    TH1D *h_MCFO0p5 = new TH1D("h_MCFO0p5", "h_MCFO0p5", v_pTBin.size() - 1, v_pTBin.data());
    TH1D *h_MCFO1 = new TH1D("h_MCFO1", "h_MCFO1", v_pTBin.size() - 1, v_pTBin.data());
    TH1D *h_MCFO1p5 = new TH1D("h_MCFO1p5", "h_MCFO1p5", v_pTBin.size() - 1, v_pTBin.data());
    TH1D *h_MCFO2 = new TH1D("h_MCFO2", "h_MCFO2", v_pTBin.size() - 1, v_pTBin.data());

    for (int pp = 1; pp < 12; ++pp) { // 0 bis 10    
      h_MCFO0->SetBinContent(pp, h_Clo0->GetBinContent(pp));
      h_MCFO0->SetBinError(pp, 0.000000001);
      h_MCFO0p5->SetBinContent(pp, h_Clo0p5->GetBinContent(pp));
      h_MCFO0p5->SetBinError(pp, 0.000000001);
      h_MCFO1->SetBinContent(pp, h_Clo1->GetBinContent(pp));
      h_MCFO1->SetBinError(pp, 0.000000001);
      h_MCFO1p5->SetBinContent(pp, h_Clo1p5->GetBinContent(pp));
      h_MCFO1p5->SetBinError(pp, 0.000000001);
      h_MCFO2->SetBinContent(pp, h_Clo2->GetBinContent(pp));
      h_MCFO2->SetBinError(pp, 0.000000001);      
    }
    
    /*
    h_Pyrap0->Draw("hist");
    h_Pyrap0p5->Draw("histsame");  
    h_Pyrap1->Draw("histsame");  
    h_Pyrap1p5->Draw("histsame");  
    h_Pyrap2->Draw("histsame");
    */
    h_Pyrapmcc0->Draw("hist");
    h_Pyrapmcc0p5->Draw("histsame");  
    h_Pyrapmcc1->Draw("histsame");  
    h_Pyrapmcc1p5->Draw("histsame");  
    h_Pyrapmcc2->Draw("histsame");
    /*
    h_Pyrapmcb0->Draw("histsame");
    h_Pyrapmcb0p5->Draw("histsame");  
    h_Pyrapmcb1->Draw("histsame");  
    h_Pyrapmcb1p5->Draw("histsame");  
    h_Pyrapmcb2->Draw("histsame");
    */
    hpT_LHCb->Draw("PEX0same");
    h_ALpT->Draw("PEX0same"); // ALICE    
    
    proYy0->Draw("PEX0same");
    proYy0p5->Draw("PEX0same");
    proYy1->Draw("PEX0same");
    proYy1p5->Draw("PEX0same");
    proYy2->Draw("PEX0same");

    h_MCFO0->Draw("hist same");     
    h_MCFO0p5->Draw("hist same");     
    h_MCFO1->Draw("hist same");     
    h_MCFO1p5->Draw("hist same");     
    h_MCFO2->Draw("hist same");     

    gr_FO0->Draw("2");    
    gr_FO0p5->Draw("2");    
    gr_FO1->Draw("2");    
    gr_FO1p5->Draw("2");    
    gr_FO2->Draw("2");    
    /*
    gr_FO0->Draw("E");
    gr_FO0p5->Draw("E");
    gr_FO1->Draw("E");
    gr_FO1p5->Draw("E");
    gr_FO2->Draw("E");
*/
    /*
    h_Pyrap0->Draw("histsame");
    h_Pyrap0p5->Draw("histsame");  
    h_Pyrap1->Draw("histsame");  
    h_Pyrap1p5->Draw("histsame");  
    h_Pyrap2->Draw("histsame");
    */
    h_Pyrapmcc0->Draw("histsame");
    h_Pyrapmcc0p5->Draw("histsame");  
    h_Pyrapmcc1->Draw("histsame");  
    h_Pyrapmcc1p5->Draw("histsame");  
    h_Pyrapmcc2->Draw("histsame");
    /*
    h_Pyrapmcb0->Draw("histsame");
    h_Pyrapmcb0p5->Draw("histsame");  
    h_Pyrapmcb1->Draw("histsame");  
    h_Pyrapmcb1p5->Draw("histsame");  
    h_Pyrapmcb2->Draw("histsame");
    */
    hpT_LHCb->Draw("PEX0same");
    h_ALpT->Draw("PEX0same"); // ALICE    
    
    proYy0->Draw("PEX0same");
    proYy0p5->Draw("PEX0same");
    proYy1->Draw("PEX0same");
    proYy1p5->Draw("PEX0same");
    proYy2->Draw("PEX0same");    
   

    styleHist(h_Pyrap0, useColPy, filStyPy, marStyPy, marSizPy, linWidAL, yOffComb, xOffPy, ploTitlePy, yTitleCombpT, xTitlePy, ylabSizComb, xlabSizPy, yTitSizComb, xTitSizPy, statHistPy, linStPy, yMinCombpT, yMaxCombpT);  
    styleHist(h_Pyrap0p5, useColPy, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitleCombpT, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStPy, yMinCombpT, yMaxCombpT);  
    styleHist(h_Pyrap1, useColPy, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitleCombpT, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStPy, yMinPy, yMaxPy);  
    styleHist(h_Pyrap1p5, useColPy, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitleCombpT, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStPy, yMinPy, yMaxPy);  
    styleHist(h_Pyrap2, useColPy, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitleCombpT, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStPy, yMinPy, yMaxPy);

    // mcc
    styleHist(h_Pyrapmcc0, kGreen +2, filStyPy, marStyPy, marSizPy, linWidAL, yOffComb, xOffPy, ploTitlePy, yTitleCombpT, xTitlePy, ylabSizComb, xlabSizPy, yTitSizComb, xTitSizPy, statHistPy, linStmcc, yMinCombpT, yMaxCombpT);  
    styleHist(h_Pyrapmcc0p5, kGreen +2, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitleCombpT, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcc, yMinCombpT, yMaxCombpT);  
    styleHist(h_Pyrapmcc1, kGreen +2, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitleCombpT, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcc, yMinPy, yMaxPy);  
    styleHist(h_Pyrapmcc1p5, kGreen +2, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitleCombpT, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcc, yMinPy, yMaxPy);  
    styleHist(h_Pyrapmcc2, kGreen +2, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitleCombpT, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcc, yMinPy, yMaxPy);

    // mcb
    styleHist(h_Pyrapmcb0, kPink -9, filStyPy, marStyPy, marSizPy, linWidAL, yOffComb, xOffPy, ploTitlePy, yTitleCombpT, xTitlePy, ylabSizComb, xlabSizPy, yTitSizComb, xTitSizPy, statHistPy, linStmcb, yMinCombpT, yMaxCombpT);  
    styleHist(h_Pyrapmcb0p5, kPink -9, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitleCombpT, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcb, yMinCombpT, yMaxCombpT);  
    styleHist(h_Pyrapmcb1, kPink -9, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitleCombpT, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcb, yMinPy, yMaxPy);  
    styleHist(h_Pyrapmcb1p5, kPink -9, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitleCombpT, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcb, yMinPy, yMaxPy);  
    styleHist(h_Pyrapmcb2, kPink -9, filStyPy, marStyPy, marSizPy, linWidAL, yOffPy, xOffPy, ploTitlePy, yTitleCombpT, xTitlePy, ylabSizPy, xlabSizPy, yTitSizPy, xTitSizPy, statHistPy, linStmcb, yMinPy, yMaxPy);    
 
    styleHist(h_ALpT, useColAL, filStyAL, marStyAL, marSizAL, linWidAL, yOffAL, xOffAL, ploTitlePy, yTitlePy, xTitlePy, ylabSizAL, xlabSizAL, yTitSizAL, xTitSizAL, statHistAL, linStAL, yMinPy, yMaxPy); // ALICE
    styleHist(hpT_LHCb, useColLH, filStyAL, marStyLH, marSizPy, linWidAL, yOffAL, xOffAL, ploTitlePy, yTitlePy, xTitlePy, ylabSizAL, xlabSizAL, yTitSizAL, xTitSizAL, statHistAL, linStAL, yMinPy, yMaxPy); // LHCb
     
    styleHist(proYy0, useColCM, filStyCM, marStyCM, marSizCM, linWidAL, yOffCM, xOffCM, ploTitlePy, yTitlePy, xTitlePy, ylabSizCM, xlabSizCM, yTitSizCM, xTitSizCM, statHistCM, linStCM, yMinPy, yMaxPy);  
    styleHist(proYy0p5, useColCM, filStyCM, marStyCM, marSizCM, linWidAL, yOffCM, xOffCM, ploTitlePy, yTitlePy, xTitlePy, ylabSizCM, xlabSizCM, yTitSizCM, xTitSizCM, statHistCM, linStCM, yMinPy, yMaxPy);
    styleHist(proYy1, useColCM, filStyCM, marStyCM, marSizCM, linWidAL, yOffCM, xOffCM, ploTitlePy, yTitlePy, xTitlePy, ylabSizCM, xlabSizCM, yTitSizCM, xTitSizCM, statHistCM, linStCM, yMinPy, yMaxPy);  
    styleHist(proYy1p5, useColCM, filStyCM, marStyCM, marSizCM, linWidAL, yOffCM, xOffCM, ploTitlePy, yTitlePy, xTitlePy, ylabSizCM, xlabSizCM, yTitSizCM, xTitSizCM, statHistCM, linStCM, yMinPy, yMaxPy);
    styleHist(proYy2, useColCM, filStyCM, marStyCM, marSizCM, linWidAL, yOffCM, xOffCM, ploTitlePy, yTitlePy, xTitlePy, ylabSizCM, xlabSizCM, yTitSizCM, xTitSizCM, statHistCM, linStCM, yMinPy, yMaxPy);

    styleHist(h_MCFO0, kCyan, filStyAL, marStyAL, marSizAL, linWidAL, yOffAL, xOffAL, ploTitlePy, yTitlePy, xTitlePy, ylabSizAL, xlabSizAL, yTitSizAL, xTitSizAL, statHistAL, 1, yMinPy, yMaxPy);
    styleHist(h_MCFO0p5, kCyan, filStyAL, marStyAL, marSizAL, linWidAL, yOffAL, xOffAL, ploTitlePy, yTitlePy, xTitlePy, ylabSizAL, xlabSizAL, yTitSizAL, xTitSizAL, statHistAL, 1, yMinPy, yMaxPy);
    styleHist(h_MCFO1, kCyan, filStyAL, marStyAL, marSizAL, linWidAL, yOffAL, xOffAL, ploTitlePy, yTitlePy, xTitlePy, ylabSizAL, xlabSizAL, yTitSizAL, xTitSizAL, statHistAL, 1, yMinPy, yMaxPy);
    styleHist(h_MCFO1p5, kCyan, filStyAL, marStyAL, marSizAL, linWidAL, yOffAL, xOffAL, ploTitlePy, yTitlePy, xTitlePy, ylabSizAL, xlabSizAL, yTitSizAL, xTitSizAL, statHistAL, 1, yMinPy, yMaxPy);
     styleHist(h_MCFO2, kCyan, filStyAL, marStyAL, marSizAL, linWidAL, yOffAL, xOffAL, ploTitlePy, yTitlePy, xTitlePy, ylabSizAL, xlabSizAL, yTitSizAL, xTitSizAL, statHistAL, 1, yMinPy, yMaxPy);
   
      
    // letak setndivision lepas styling
    //h_Pyrap0->GetYaxis()->SetNdivisions(-7);
    h_Pyrapmcc0->GetYaxis()->SetNdivisions(-7);
    
    TLatex *txt1 = new TLatex();
    txt1->SetTextSize(0.03);
    txt1->SetTextFont(42);
    txt1->SetTextAngle(345);
    txt1->DrawTextNDC(0.64, 0.875, "|y| < 0.5, m = 9");
    
    TLatex *txt2 = new TLatex();
    txt2->SetTextSize(0.03);
    txt2->SetTextFont(42);
    txt2->SetTextAngle(345);
    txt2->DrawTextNDC(0.56, 0.77, "0.5 < |y| < 1.0, m = 7");

    TLatex *txt3 = new TLatex();
    txt3->SetTextSize(0.03);
    txt3->SetTextFont(42);
    txt3->SetTextAngle(345);
    txt3->DrawTextNDC(0.52, 0.66, "1.0 < |y| < 1.5, m = 5");

    TLatex *txt4 = new TLatex();
    txt4->SetTextSize(0.03);
    txt4->SetTextFont(42);
    txt4->SetTextAngle(345);
    txt4->DrawTextNDC(0.49, 0.54, "1.5 < |y| < 2.0, m = 3");

    TLatex *txt5 = new TLatex();
    txt5->SetTextSize(0.03);
    txt5->SetTextFont(42);
    txt5->SetTextAngle(345);
    txt5->DrawTextNDC(0.47, 0.43, "2.0 < |y| < 2.5, m = 1");

    //TLegend *stdL1 = new TLegend(0.79, 0.8, 0.95, 0.95);
    TLegend *stdL1 = new TLegend(0.52, 0.12, 0.8, 0.29);
    stdL1->AddEntry(proYy0, "CMS c", "pl");
    stdL1->AddEntry(h_ALpT, "ALICE c", "pl");
    stdL1->AddEntry(hpT_LHCb, "LHCb c", "pl");
    //stdL1->AddEntry(h_Pyrap0, ("Pythia c+b #times " + toStr(SFforPy)).c_str(), "l");
    stdL1->AddEntry(h_Pyrapmcc0, ("Pythia c #times " + toStr(SFforPy)).c_str(), "l");
    //stdL1->AddEntry(h_Pyrapmcb0, ("Pythia b #times " + toStr(SFforPy)).c_str(), "l");    
    stdL1->AddEntry(gr_FO0, "FONLL c", "fl");
    //stdL1->AddEntry(gr_FO0, "FONLL c", "l");
    
    stdL1->Draw();
    styleLeg(stdL1, 0, 0, 42, 0.03, 0, 0);
  } // end of else {
     
  //styleLeg(legInd, 0, 0, 42, 0.03, 0);
  styleLeg(legInd, fColor, borSiz, texFon, texSiz, bordSiz, filSty);
  
  //pad1->RedrawAxis();

  auto g_gri = std::make_unique<TGraphErrors>(1);
  g_gri->SetPoint(0, -1., 1.);
  // error x low, error x high
  g_gri->SetPointError(0, 1000., 0.);// error x and error y for point iP
  styleGraph(g_gri.get(), kBlack, colAlphagf, filStygf, marStygf, marSizgf, linStygf, linWidgf);  

  if (num < 5) {
  g_gri->Draw("0z same");
  //pad2->RedrawAxis();
  }
  c1->SaveAs((outDir + outNamepT + ".pdf").c_str());
  c1->Close();
  //c2->cd();
  //c2->SaveAs((outDir + outNamepT + ".pdf").c_str());
  //c2->Close();
  //####################################################################################//
  // Draw the cross sections as a function of pT for each rapidity    END               //
  //####################################################################################//

  
  //c1->Close();
  gROOT->ProcessLine(".q");  
}


// BR from PDG online (latest)
// D*->D0pi = (67.7 +- 0.5)% = 0.677 +- 0.0050
// D0->Kpi = (3.95 +- 0.031)% = 0.0395 +- 0.00031
// D* BR = 0.0267 or 2.67 +- 0.124% (0.677 * 0.0395 = 0.0267 +- 0.00124)
