//================================================================================================================================//
// Author: Nur Zulaiha binti Jomhari (Nuha) //
//////////////////////////////////////////////
// Plot Nsignal for: hpT & lpT (both wit fit); 66 all (nofit); 66 indv (fit&nofit); Nsigtable;

// Usage for hpt & lpt:
// for data:
//root -l -b 'Nsignalv1_modiv0.cc("MuDhistostest2010_13all.root", "data13all", "deltamr", 0, "lpt", 6)'
//root -l -b 'Nsignalv1_modiv0.cc("MuDhistostest2010_13all.root", "data13all", "deltamr", 0, "hpt", 6)'
// for MC:
//root -l -b 'Nsignalv1_modiv0.cc("MuDhistosMC10_D0_beauty5_dEdxyz2.root", "MCbeauty5_dEdxyz2", "deltamr", 1, "lpt", 6)'
//root -l -b 'Nsignalv1_modiv0.cc("MuDhistosMC10_D0_beauty5_dEdxyz2.root", "MCbeauty5_dEdxyz2", "deltamr", 1, "hpt", 6)'

// Usage for indvnofit & indvfit:
// for data:
// for 1 specific bin (use for check specific bin / debug)
//for iNum in 6; do root -l -b 'Nsignalv1_modiv0.cc("MuDhistostest2010_13all.root", "data13all_'${iNum}'", "deltamr", 0, "indvnofit", '${iNum}')'; done
// for all bins (please refer table bins)
//for iNum in `seq 6 65`; do root -l -b 'Nsignalv1_modiv0.cc("MuDhistostest2010_13all.root", "data13all_'${iNum}'", "deltamr", 0, "indvnofit", '${iNum}')'; done
//for iNum in `seq 6 65`; do root -l -b 'Nsignalv1_modiv0.cc("MuDhistostest2010_13all.root", "data13all_'${iNum}'", "deltamr", 0, "indvfit", '${iNum}')'; done
// for MC:
// for 1 specific bin (use for check specific bin / debug)
//for iNum in 6; do root -l -b 'Nsignalv1_modiv0.cc("MuDhistosMC10_D0_beauty5_dEdxyz2.root", "MCbeauty5_dEdxyz2_'${iNum}'", "deltamr", 1, "indvnofit", '${iNum}')'; done
// for all bins (please refer table bins)
//for iNum in `seq 6 65`; do root -l -b 'Nsignalv1_modiv0.cc("MuDhistosMC10_D0_beauty5_dEdxyz2.root", "MCbeauty5_dEdxyz2_'${iNum}'", "deltamr", 1, "indvnofit", '${iNum}')'; done
//for iNum in `seq 6 65`; do root -l -b 'Nsignalv1_modiv0.cc("MuDhistosMC10_D0_beauty5_dEdxyz2.root", "MCbeauty5_dEdxyz2_'${iNum}'", "deltamr", 1, "indvfit", '${iNum}')'; done

// Usage for nsigtable:
// for data:
//root -l -b 'Nsignalv1_modiv0.cc("MuDhistostest2010_13all.root", "data13all", "deltamr", 0, "nsigtable", 6)'
//root -l -b 'Nsignalv1_modiv0.cc("MuDhistosMC10_D0_beauty5_dEdxyz2.root", "MCbeauty5_dEdxyz2", "deltamr", 1, "nsigtable", 6)'
//================================================================================================================================//

// COMMENT THIS IF YOU DONT PLOT NSIGNAL IN TABLE/Eff table
//#define sigTab50

// ROOT & C header files, and also styling definition is in this header file
#include "/home/zulaiha/PhD/merge_code/PlotUtil.h"
#include "/home/zulaiha/PhD/merge_code/Func.h"

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

void Nsignalv1_modiv0(const std::string &fileName, const std::string &outName, const std::string &whichDst, const bool isMC, const std::string &whichPlot, const int Num) {
  
  gStyle->SetOptStat(0);
  // to include the tick atas dan kanan
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  
  // Max digit you want to put in the y axis. eg. 3000 --> 3x10^3 etc
  TGaxis::SetMaxDigits(7);
  // Make sure uncertainty in histogram bins is calculated correctly
  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(false);
  
  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////// DECLARATION OF VARIABLES ///////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  // Input and output directory
  string inDir;
  string outDir;

  // Input file
  TFile *inFile;
  TFile *RFile;
  
  // Input histogram that we read/use
  // right & wrong charge
  string Varhist1;
  string Varhist2;
  string Varhist3;
  string Varhist4;
  string Varhist5;
  string Varhist6;

  string Varhistrc;
  string Varhistwc;
  string Varhistrb;
  string Varhistwb;
  // New histogram
  // this is the histogram that we do physics on it
  // right and wrong charge
  TH1F *hptrapr;
  TH1F *hptrapw;
  TH1F *hdiff;
  
  // Divide each section of the plot
  // assign the x-axis
  Double_t Axmin;
  Double_t Axmax;
  Double_t Bxmin;
  Double_t Bxmax;
  Double_t Cxmin;
  Double_t Cxmax;
  Double_t Dxmin;
  Double_t Dxmax;
  Double_t Exmin;
  Double_t Exmax;

  // Background integral
  // before, after and total
  Double_t Ainter;
  Double_t Aintew;
  Double_t Einter;
  Double_t Eintew;
  Double_t Cinter;
  Double_t Cintew;
  Double_t Cintew_afterscale;
  Double_t TOTinter;
  Double_t TOTintew;
  Double_t Scaleup;

  // binwidth
  Double_t binwid;

  // Signal integral
  // Before and after scale factor
  Double_t NSignal_aftersf1;
  Double_t NSignal_b4sf;
  Double_t uncertSig;
  
  // Canvas
  TCanvas *can1;

  // Legend
  TLegend *stdL0;
  TLegend *stdLfit; // legend for fit

  Double_t yMax, yMin, xlatex, ylatex1, ylatex2, ylatex3, ylatex4, ylatex5, ylatex6, ylatex7;
  std::vector<int> vecbin;

  int range;
  std::vector<std::pair<double, int> > v_Ainter;
  std::vector<std::pair<double, int> > v_SF;
  std::vector<std::pair<double, int> > v_totintegralr;
  std::vector<std::pair<double, int> > v_totintegralw;
  std::vector<std::pair<double, int> > v_Nsigb4;
  std::vector<std::pair<double, int> > Nsigafter;
  std::vector<std::pair<double, int> > uncerNsigafter;

  vector<std::pair<int, int> > truth;  
  vector<std::pair<double, int> > uncertruth;

  // declaration for fitting
  TF1 *Fitsig, *fdiff, *Fitbkg1, *Fit1, *Fitbkgdraw, *Fitsigdraw, *fdeltaMwrongcharge, *fdeltaM; 

  double checkNsig, checkNsigErr, chi2Prob;
  string chi2, ndof, chi2ovndof, pvalue, N, Nsub, sigma, Mcentre;
  int decNerr, decN;

  // bR, div and uncerBR for MC uncertainties
  Float_t BR;
  Int_t div;
  Float_t uncerBR;
  TFitResultPtr pr_fit;
  
  // variables for efficiency
  ofstream myfile, Nsigfile, efffile;
  TTree *tree;
  Float_t NsigafterDD, UncerNsigafterDD, TruthDD, UncerTruthDD, EffDD;  
  std::vector<float> v_Nsigafter, v_uncerNsigafter, v_truth, v_uncertruth, v_eff, v_uncerEff;
  Double_t uncerEffb4SF;
  Int_t nevent;   

  TH2D *h_nume, *h_deno, *h_deff;
  TCanvas *c00, *c01, *c02, *c03, *c04, *c05;
  TH1D *hist1, *hist2;
  TEfficiency* pEff;
  TFile *pFile;
  TGraphAsymmErrors *gr;
  Double_t Eff_afterBR, Uncer_afterBRHigh, Uncer_afterBRLow, aveUncerUpLow;
  TH2D *h_deffafterBR, *h_deffafterBR3D;
  TH1F *hh;
  string ploTitle2D;
  int index;
  std::vector<float> v_effafterBR, v_aveuncert;
  
  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// END OF DECLARATION //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////


  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////// PLACE WHERE YOU MODIFIED THINGS //////////////////////////
  ////////// EXCEPT FOR STYLING BCOZ STYLE ALWAYS PUT AT THE END /////////////////
  ////////////////////////////////////////////////////////////////////////////////

  // Input directory
  // Place all MuDhistos in 1 directory
  //inDir = "/home/zulaiha/PhD/Analysis/wow/TtoH/Achim/";
  inDir = "/home/zulaiha/PhD/Yewon/merge_code/";

  // Output directory
  // Place all output files in 1 directory
  outDir = "/home/zulaiha/PhD/Yewon/merge_code/test1/";

  inFile = TFile::Open((inDir + fileName).c_str());

  cout << " " << endl;
  cout << "******************************************************************************" <<  endl;
  cout << "Reading " << inDir << fileName << endl;
  cout << "Writing to " << outDir << endl;
  cout << "******************************************************************************" <<  endl;
  cout << " " << endl;

  // list of histograms we want to use for corresponding purposes
  if (isMC == 0) { // isMC == 0 means data
    // deltamr
    if (whichDst == "deltamr") { 
      if (whichPlot == "hpt") {
	Varhist1 = "hc_Dstar_deltamrhptr";
	Varhist2 = "hc_Dstar_deltamrhptw";
      } 
      else if (whichPlot == "lpt") {
	Varhist1 = "hc_Dstar_deltamrlptr";
	Varhist2 = "hc_Dstar_deltamrlptw";
      } 
      else if (whichPlot == "indvnofit" or whichPlot == "indvfit") {
	Varhist1 = "hc_Dstar_deltamr_ptyr" + toStr(Num);
	Varhist2 = "hc_Dstar_deltamr_ptyw" + toStr(Num);
      }
      else if (whichPlot == "nsigtable") {
	Varhist1 = "hc_Dstar_deltamr_ptyr";
	Varhist2 = "hc_Dstar_deltamr_ptyw";  
      }
      else {
	cout << "Please insert which histogram u want to plot for deltamr. Available options are:" << endl;
	cout << "hpt / lpt / indvnofit / indvfit / nsigtable" << endl;
	cout << " " << endl;
      }
    } // end of whichDst == deltamr

    // deltam
    else if (whichDst == "deltam") {
      if (whichPlot == "hpt") {
	Varhist1 = "hc_Dstar_deltamhptr";
	Varhist2 = "hc_Dstar_deltamhptw";
      }
      else if (whichPlot == "lpt") {
	Varhist1 = "hc_Dstar_deltamlptr";
	Varhist2 = "hc_Dstar_deltamlptw";
      } 
      else if (whichPlot == "indvnofit" or whichPlot == "indvfit") {
	Varhist1 = "hc_Dstar_deltam_ptyr" + toStr(Num);
	Varhist2 = "hc_Dstar_deltam_ptyw" + toStr(Num);
      }
      else if (whichPlot == "nsigtable") {
	Varhist1 = "hc_Dstar_deltam_ptyr";
	Varhist2 = "hc_Dstar_deltam_ptyw";   
      }
      else {
	cout << "Please insert which histogram u want to plot for deltam. Available options are:" << endl;
	cout << "hpt / lpt / indvnofit / indvfit / nsigtable" << endl;
	cout << " " << endl;
      }
    } // end of whichDst == deltam
    else {
      cout << "Please insert whichDst you want. Available options are:" << endl;
      cout << "deltamr / deltam" << endl;
      cout << " " << endl;
    }
  } // end of isMC == 0 (data)

  else if (isMC == 1) { // isMC == 1 means MC
    // deltamr
    if (whichDst == "deltamr") {
      if (whichPlot == "hpt") {
	Varhist1 = "hc_Dstar_deltamrhptrt";
	Varhist2 = "hc_Dstar_deltamrhptwt";

	Varhistrc = "hc_Dstar_deltamrhptrc";
	Varhistwc = "hc_Dstar_deltamrhptwc";

	Varhistrb = "hc_Dstar_deltamrhptrb";
	Varhistwb = "hc_Dstar_deltamrhptwb";      
      }
      else if (whichPlot == "lpt") {
	Varhist1 = "hc_Dstar_deltamrlptrt";
	Varhist2 = "hc_Dstar_deltamrlptwt";
	
	Varhistrc = "hc_Dstar_deltamrlptrc";
	Varhistwc = "hc_Dstar_deltamrlptwc";
	
	Varhistrb = "hc_Dstar_deltamrlptrb";
	Varhistwb = "hc_Dstar_deltamrlptwb";      
      }
      else if (whichPlot == "indvnofit" or whichPlot == "indvfit") {
	Varhist1 = "hc_Dstar_deltamr_ptyrt" + toStr(Num);
	Varhist2 = "hc_Dstar_deltamr_ptywt" + toStr(Num);

	Varhistrc = "hc_Dstar_deltamr_ptyrc" + toStr(Num);
	Varhistwc = "hc_Dstar_deltamc_ptywc" + toStr(Num); // need to change after achim change it in mudhistos
	
	Varhistrb = "hc_Dstar_deltamr_ptyrb" + toStr(Num);
	Varhistwb = "hc_Dstar_deltamb_ptywb" + toStr(Num); // need to change after achim change it in mudhistos      
      }
      else if (whichPlot == "nsigtable") {
	Varhist1 = "hc_Dstar_deltamr_ptyrt";
	Varhist2 = "hc_Dstar_deltamr_ptywt"; 
	
	Varhistrc = "hc_Dstar_deltamr_ptyrc";
	Varhistwc = "hc_Dstar_deltamc_ptywc"; // need to change after achim change it in mudhistos
	
	Varhistrb = "hc_Dstar_deltamr_ptyrb";
	Varhistwb = "hc_Dstar_deltamb_ptywb"; // need to change after achim change it in mudhistos
	
	Varhist3 = "trueDstaryptbin";
	Varhist4 = "trueDstarHHpiyptbin";
	
	Varhist5 = "true_cDstarHHpiyptbin"; // 5 for c
	Varhist6 = "true_bDstarHHpiyptbin"; // 6 for b     
      }
      else {
	cout << "Please insert which histogram u want to plot for deltamr. Available options are:" << endl;
	cout << "hpt / lpt / indvnofit / indvfit / nsigtable" << endl;
	cout << " " << endl;
      }
    } // end of whichDst == deltamr

    // deltam
    else if (whichDst == "deltam") {
      if (whichPlot == "hpt") {
	Varhist1 = "hc_Dstar_deltamhptrt";
	Varhist2 = "hc_Dstar_deltamhptwt";

	Varhistrc = "hc_Dstar_deltamhptrc";
	Varhistwc = "hc_Dstar_deltamhptwc";

	Varhistrb = "hc_Dstar_deltamhptrb";
	Varhistwb = "hc_Dstar_deltamhptwb";          
      }
      else if (whichPlot == "lpt") {
	Varhist1 = "hc_Dstar_deltamlptrt";
	Varhist2 = "hc_Dstar_deltamlptwt";

	Varhistrc = "hc_Dstar_deltamlptrc";
	Varhistwc = "hc_Dstar_deltamlptwc";

	Varhistrb = "hc_Dstar_deltamrlptrb";
	Varhistwb = "hc_Dstar_deltamrlptwb";       
      }
      else if (whichPlot == "indvnofit" or whichPlot == "indvfit") {
	Varhist1 = "hc_Dstar_deltam_ptyrt" + toStr(Num);
	Varhist2 = "hc_Dstar_deltam_ptywt" + toStr(Num);

	Varhistrc = "hc_Dstar_deltam_ptyrc" + toStr(Num);
	Varhistwc = "hc_Dstar_deltam_ptywc" + toStr(Num);

	Varhistrb = "hc_Dstar_deltam_ptyrb" + toStr(Num);
	Varhistwb = "hc_Dstar_deltam_ptywb" + toStr(Num);      
      }
      else if (whichPlot == "nsigtable") {
	Varhist1 = "hc_Dstar_deltam_ptyrt";
	Varhist2 = "hc_Dstar_deltam_ptywt";

	Varhistrc = "hc_Dstar_deltam_ptyrc";
	Varhistwc = "hc_Dstar_deltam_ptywc";

	Varhistrb = "hc_Dstar_deltam_ptyrb";
	Varhistwb = "hc_Dstar_deltam_ptywb";
      
	Varhist3 = "trueDstaryptbin";
	Varhist4 = "trueDstarHHpiyptbin";

	Varhist5 = "true_cDstarHHpiyptbin"; // 5 for c
	Varhist6 = "true_bDstarHHpiyptbin"; // 6 for b       
      }
      else {
	cout << "Please insert which histogram u want to plot for deltam. Available options are:" << endl;
	cout << "hpt / lpt / indvnofit / indvfit / nsigtable" << endl;
	cout << " " << endl;
      }
    } // end of whichDst == deltam
    else {
      cout << "Please insert whichDst you want. Available options are:" << endl;
      cout << "deltamr / deltam" << endl;
      cout << " " << endl;
    }    
  } // end of isMC == 1 (MC)
  else {
    cout << "Please insert which MC or data. Available options are:" << endl;
    cout << "0 (for data) / 1 (for MC)" << endl;
    cout << " " << endl;
  }
  
  // these numbers are w/o rebin. If rebin, pls uncomment lines in rebin section and check corresponding upper and lower edge
  // x axis binedge deltamr
  if (whichDst == "deltamr") {
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
    // both A and E regions are use to scale wrong charge to right charge to get SF
  }
  
  // x axis binedge deltam
  else if (whichDst == "deltam") {
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
  }

  // customize yMax
  // only did for hpt/lpt as individual plots for each bin varies a lot
  if (isMC == 0) {
    if (whichPlot == "hpt" or whichPlot == "lpt") {
      yMax = 2000.;}
    else {yMin = yMax;}
  }
  else if (isMC == 1) {
    if (whichPlot == "hpt" or whichPlot == "lpt") {
      yMax = 20000.;}
    else {yMin = yMax;}
  }
  // MCD0:16000. or 19000; 10all:1950.; 10el3:350.; MCcharm:3000.; MCbeauty:400.; MCMB:350.;19000; DataBPark:1900000., 0BMB: 2000.
  // MCD0:2600. or 4000; 10all:610.; 10el3:75.; MCcharm:500.; MCbeauty:60.; MCMB:90.; 4000; BPark: 150000., 0BMB: 610.
      
  // rand number as it will not cust. yMax in stylehist
  // in stylehist put yMin = yMax for uncustomize yMax
  //else {yMax = 1010.;}

  // position of the latex of statistic box
  if (whichPlot == "hpt" or whichPlot == "indvfit") {  
    xlatex = 0.46,
      ylatex1 = 0.745,
      ylatex2 = 0.705,
      ylatex3 = 0.67,
      ylatex4 = 0.63,
      ylatex5 = 0.59,      
      ylatex6 = 0.54,
      ylatex7 = 0.50;
  }

  else if (whichPlot == "lpt") {
    xlatex = 0.46,
      // uncomment this line if u want the stat. box to placed higher
      /*
      ylatex1 = 0.445,
      ylatex2 = 0.39,
      ylatex3 = 0.34,
      ylatex4 = 0.29,
      ylatex5 = 0.24,
      ylatex6 = 0.19;
      ylatex7 = 0.15;
      */
      ylatex1 = 0.83,
      ylatex2 = 0.79,
      ylatex3 = 0.755,
      ylatex4 = 0.71,
      ylatex5 = 0.67,      
      ylatex6 = 0.62,
      ylatex7 = 0.58;      
  }
  
  // stylehist variables
  const float useColr = kBlue,
    useColw = kRed,
    filSty = 0,
    marSty = 20,
    marSiz = 1.5,
    linWid = 2.,
    yOff = 1.19,
    xOff = 1.,
    ylabSiz = 0.038,
    xlabSiz = 0.04,
    yTitSiz = 0.05,
    xTitSiz = 0.05,
    statHist = 0.,
    linSt = 1.;
     
  const string ploTitle = "",
    yTitle = "Entries",
    xTitle = "m_{K#pi#pi_{s}} - m_{K#pi} (GeV)";

  // stylehist2D variables
  const float zMin2D = 0.,
    zMax2D = 1.,
    marSiz2D = 1.2,
    yMin2D = 1.,
    yMax2D = 11.,
    xMin2D = 0.,
    xMax2D = 2.5,
    useCol2D = kRed + 1,
    yOff2D = 1.1,
    xOff2D = 1.;

  const string yTitle2D = "p_{T} (GeV)",
    xTitle2D = "|y|",
    zTitle2D = "entries";


  if (whichPlot != "nsigtable") {
    // Name of new histograms
    hptrapr = (TH1F*) inFile->Get((Varhist1).c_str())->Clone("xxx");
    hptrapw = (TH1F*) inFile->Get((Varhist2).c_str())->Clone("yyy");
  }
  
#ifdef sigTab50
  for (int histNum = 0; histNum < 66; ++histNum) {
    // repeat the vector from scratch bila loop
    // hanya dlm this case letak this clear at the beginning
    // can check/debug for more info dlm cout ifdef
    vecbin.clear();
    hptrapr = (TH1F*) inFile->Get((Varhist1 + toStr(histNum)).c_str())->Clone("xxx");
    hptrapw = (TH1F*) inFile->Get((Varhist2 + toStr(histNum)).c_str())->Clone("yyy");
    //hptrapr = (TH1F*) inFile->Get((Varhistrc + toStr(histNum)).c_str())->Clone("xxx");
    //hptrapw = (TH1F*) inFile->Get((Varhistwc + toStr(histNum)).c_str())->Clone("yyy");
#endif

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// END OF MODIFICATION /////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////// Rebin (Optional) ///////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  // Optional
  // printout lower and upper edge for debug/checking consistency
  //std::cout << "" << std::endl;
  //std::cout << "#bin, binlowedge, binhighedge, bincontentr, bincontentw," << std::endl;  
  //for (int iBin = 1; iBin <= hptrapr->GetNbinsX(); ++iBin) {
  //std::cout << iBin << " " << hptrapr->GetBinLowEdge(iBin) << " " << hptrapr->GetXaxis()->GetBinUpEdge(iBin) << " " << hptrapr->GetBinContent(iBin) << " " << hptrapw->GetBinContent(iBin) << std::endl;
  //}
  /*
  hptrapr->Rebin(2);
  hptrapw->Rebin(2);
  
  std::cout << "" << std::endl;
  std::cout << "#bin, binlowedge, bincontent after rebin" << std::endl;  
  for (int iBin = 1; iBin <= hptrapr->GetNbinsX(); ++iBin) {
    //std::cout<< iBin << " " << hptrapr->GetBinLowEdge(iBin) << " " << hptrapr->GetXaxis()->GetBinUpEdge(iBin) << " " << hptrapr->GetBinContent(iBin) << std::endl;}
  */
  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////// Rebin end //////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////    

  
  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////// MACHINERY FOR SIGNAL EXTRACTION ////////////////////////
  ///////////////////// USING BACKGROUND SUBTRACTION METHOD //////////////////////
  ///////////////////////// DO NOT TOUCH IF POSSIBLE! ////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////

  // after #endif, it will break the indent, therefore
  // for the first line after #endif, correct the indent and the rest will follow
  binwid = hptrapr->GetBinLowEdge(2) - hptrapr->GetBinLowEdge(1);
  cout << "=================================================" << endl;
  cout << "binwidth: " << binwid << endl;
  
  // get the bin for each section of x axis
  // doesn't matter hptrapr or hptrapw as the axis is the same for both
  vecbin.push_back(hptrapr->GetXaxis()->FindBin(Axmin + (0.5 * binwid)));  
  vecbin.push_back(hptrapr->GetXaxis()->FindBin(Axmax - (0.5 * binwid)));
  vecbin.push_back(hptrapr->GetXaxis()->FindBin(Bxmin + (0.5 * binwid)));  
  vecbin.push_back(hptrapr->GetXaxis()->FindBin(Bxmax - (0.5 * binwid)));  
  vecbin.push_back(hptrapr->GetXaxis()->FindBin(Cxmin + (0.5 * binwid)));
  //vecbin.push_back(hptrapr->GetXaxis()->FindBin(Cxmin));
  
  vecbin.push_back(hptrapr->GetXaxis()->FindBin(Cxmax - (0.5 * binwid)));
  vecbin.push_back(hptrapr->GetXaxis()->FindBin(Dxmin + (0.5 * binwid)));  
  vecbin.push_back(hptrapr->GetXaxis()->FindBin(Dxmax - (0.5 * binwid)));  
  vecbin.push_back(hptrapr->GetXaxis()->FindBin(Exmin + (0.5 * binwid)));
  vecbin.push_back(hptrapr->GetXaxis()->FindBin(Exmax - (0.5 * binwid)));
  /*
  // Print out the values for checking
  cout << "*******************************************************************" << endl;
  cout << "Print out bin index for this x axis" << endl;
  cout << "to ensure continuos bin flow" << endl;
  cout << "*******************************************************************" << endl;
  cout << "Left side band (Region A): " << endl;
  cout << "--------------------------" << endl;
  cout << "Abinmin = " << vecbin.at(0) << " " << "Abinmax = " << vecbin.at(1) << endl;
  cout << "\nUnwanted band (Region B): " << endl;
  cout << "-------------------------" << endl;
  cout << "Bbinmin = " << vecbin.at(2) << " " << "Bbinmax = " << vecbin.at(3) << endl;  
  cout << "\nSignal band (Region C):" << endl;
  cout << "-----------------------" << endl;
  cout << "Cbinmin = " << vecbin.at(4) << " " << "Cbinmax = " << vecbin.at(5) << endl;
  cout << "\nUnwanted band (Region D):" << endl;
  cout << "-------------------------" << endl;
  cout << "Dbinmin = " << vecbin.at(6) << " " << "Dbinmax = " << vecbin.at(7) << endl;
  cout << "\nRight side band (Region E):" << endl;
  cout << "---------------------------" << endl;
  cout << "Ebinmin =  " << vecbin.at(8) << " " << "Ebinmax = " << vecbin.at(9) << endl;  
  cout << "*******************************************************************" << endl;
  */
  // integrate region that u want to integrate 
  Ainter = hptrapr->Integral(vecbin.at(0), vecbin.at(1));
  Aintew = hptrapw->Integral(vecbin.at(0), vecbin.at(1));
  Cinter = hptrapr->Integral(vecbin.at(4), vecbin.at(5));
  Cintew = hptrapw->Integral(vecbin.at(4), vecbin.at(5));
  Einter = hptrapr->Integral(vecbin.at(8), vecbin.at(9));
  Eintew = hptrapw->Integral(vecbin.at(8), vecbin.at(9));

  // Checking double counting
  // integral from region A to region E must be = integral of whole range
  cout << "Integral whole range with vec:  " << hptrapr->Integral(vecbin.at(0), vecbin.at(9)) << endl;
  // if deltam
  if (whichDst == "deltam") {cout << "Integral whole range:  " << hptrapr->Integral() << endl;}
  // if deltamr  
  else if (whichDst == "deltamr") {cout << "Integral whole range:  " << hptrapr->Integral(0, hptrapr->GetXaxis()->FindBin(Exmax - (0.5 * binwid))) << endl;}
  // 86 coz vecbin.at(9) is bin 86
  
  // total integral of both side bands
  TOTinter = Ainter + Einter;
  TOTintew = Aintew + Eintew;
  
  //cout << "TOTintegral_RC_A_region_plus_E_region: " << TOTinter << endl;
  //cout << "TOTintegral_WC_A_region_plus_E_region: " << TOTintew << endl;
  //cout << " " << endl;

  // divide tot. side band in right & wrong charge to get SF
  // if totintew == 0, scaleup will be 0, if !=0, it will follow formula below
  Scaleup = (TOTintew == 0.) ? 0. : TOTinter / TOTintew;
  
  //cout << "Scale Factor: " << Scaleup << endl;  
  
  // signal integral
  // before apply scale factor
  NSignal_b4sf = Cinter - Cintew;
  
  // no scale = 1.
  // normalize the whole range wrong charge to right charge
  hptrapw->Scale(Scaleup);

  // after apply scale factor
  Cintew_afterscale = hptrapw->Integral(vecbin.at(4), vecbin.at(5));
  NSignal_aftersf1 = Cinter - Cintew_afterscale;
  
  //uncertSig = sqrt((NRS + NWS_aftersf)); // assuming both are poisson stat.
  uncertSig = sqrt((Cinter + Cintew_afterscale)); // assuming both are poisson stat.
  
  cout << " " << endl;
  cout << "Total Entries of side band (A+E) before scaleup" << endl;
  cout << "------------------------------------------------" << endl;
  cout << "right charge = " << TOTinter << endl;
  cout << "wrong charge = " << TOTintew << endl;
  cout << "Scale Factor = " << Scaleup << endl;
  cout << " " << endl;
  cout << "Entries of signal b4 and after SF" << endl;
  cout << "----------------------------------" << endl;  
  cout << "NSignalb4Sf = " << NSignal_b4sf << endl;
  cout << "NSignal_afterSf = " << " " << NSignal_aftersf1 << endl;
  cout << "Integral of right charge in C = " << Cinter << endl;
  cout << "Integral of wrong charge in C afterSf = " << Cintew_afterscale << endl;
  cout << "uncertSig = " << uncertSig << endl;
  cout << "=================================================" << endl;  
  cout << " " << endl;

  //hptrapr->Add(hptrapw, -1);
#ifdef sigTab50
  v_SF.push_back({Scaleup, histNum});
  v_totintegralr.push_back({TOTinter, histNum});
  v_totintegralw.push_back({TOTintew, histNum});
  v_Nsigb4.push_back({NSignal_b4sf, histNum});
  Nsigafter.push_back({NSignal_aftersf1, histNum});
  uncerNsigafter.push_back({uncertSig, histNum});
  } // end of ifdef sigTab
#endif
  // dont put vecbin.clear here
  // when cout, size bin will increase, coz we dont refresh vector every loop 

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////// END OF SIGNAL EXTRACTION MACHINERY /////////////////////////
  ////////////////////////////////////////////////////////////////////////////////


  ////////////////////////////////////////////////////////////////////////////////
  ////////////// DECLARE HISTOGRAM THAT WILL USE FOR PLOTTING ////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  
  //TH1F *hptrapr = (TH1F*) hptrapr->Clone(); 
  //TH1F *hptrapw = (TH1F*) hptrapw->Clone();
  hdiff = (TH1F*) hptrapr->Clone();
  
  hdiff->Add(hptrapw, -1); // if substract
  //hdiff->Draw("E same");
  
  /////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// FITTING START ////////////////////////////////////
  /////////////////// USE TO FIT HIST IN HPT, LPT, INDVFIT ////////////////////////
  /////////////////////////////////////////////////////////////////////////////////

  if (whichPlot == "hpt" or whichPlot == "lpt" or whichPlot == "indvfit") {
    // Fit the histogram after substraction with mod gaus function
    Fitsig = new TF1("Fitsig", custGaus, 0.138, Exmax, 3);
    Fitsig->SetNpx(10000); // use to make the peak smooth  
    Fitsig->SetParameter(0,0.1454); // the peak
    Fitsig->SetParameter(1,0.0005); // ori:0.0005
    Fitsig->SetParameter(2,600); // free param

    hdiff->Fit("Fitsig","N"); // put N option for it to not draw
    fdiff = (TF1 *) hdiff->GetListOfFunctions()->At(0);
  
    //fit a background to the wrong charge, in this case the Granet function
    Fitbkg1 = new TF1("Fitbkg1",Granet,Pimass,Exmax,3);
    Fitbkg1->SetParameter(0,2000); // 2000
    Fitbkg1->SetParameter(1,0.1); // 0.1
    Fitbkg1->SetParameter(2,50); // 10
  
    hptrapw->Fit("Fitbkg1","N","",Pimass,Exmax); // fit wc tp jgn draw
  
    //Fit the right charge using a combination of a Gaussian and Granet function
    Fit1 = new TF1("Fit1", Dfit,0.1396, Exmax,6);
    Fit1->SetParNames("mu","sigma","N","A","B","C");
    Fit1->SetNpx(10000); // use to make the peak smooth
    Fit1->SetParameter(0,Fitsig->GetParameter(0)); //Use parameters of the signal fit as starting points for this fit
    Fit1->SetParLimits(1,0.0001,0.0007);
    Fit1->SetParameter(1,Fitsig->GetParameter(1));
    Fit1->SetParameter(2,Fitsig->GetParameter(2));
    Fit1->SetParameter(3, Fitbkg1->GetParameter(0));//use parameters of the background fit as starting points for this fit
    Fit1->SetParameter(4, Fitbkg1->GetParameter(1));
    Fit1->SetParameter(5, Fitbkg1->GetParameter(2));  
    Fit1->SetLineColor(kBlue);
    Fit1->SetLineWidth(2);

    Fit1->SetParError(0,Fitsig->GetParError(0)); 
    Fit1->SetParError(1,Fitsig->GetParError(1));
    Fit1->SetParError(2,Fitsig->GetParError(2));
    Fit1->SetParError(3, Fitbkg1->GetParError(0));
    Fit1->SetParError(4, Fitbkg1->GetParError(1));
    Fit1->SetParError(5, Fitbkg1->GetParError(2));
  
    hptrapr->Fit("Fit1","","",Pimass,Exmax); //Actually Fit

    //draw the Background Fit to right charge
    Fitbkgdraw = new TF1("Fitbkgdraw",Granet,Pimass,Exmax,3);
    Fitbkgdraw->SetParameter(0,Fit1->GetParameter(3));
    Fitbkgdraw->SetParameter(1,Fit1->GetParameter(4));
    Fitbkgdraw->SetParameter(2,Fit1->GetParameter(5));
    Fitbkgdraw->SetLineColor(kBlack);
    Fitbkgdraw->SetLineStyle(2);
    Fitbkgdraw->SetLineWidth(2);

    // fit signal drp combined fit function modGaus+Granet
    Fitsigdraw = new TF1("Fitsigdraw", custGaus, 0.138, Exmax, 3);
    Fitsigdraw->SetNpx(10000); // use to make the peak smooth  
    Fitsigdraw->SetParameter(0, Fit1->GetParameter(0)); // the peak
    Fitsigdraw->SetParameter(1, Fit1->GetParameter(1)); // ori:0.0005
    Fitsigdraw->SetParameter(2, Fit1->GetParameter(2)); // free param

    Fitsigdraw->SetParError(0, Fit1->GetParError(0)); // the peak
    Fitsigdraw->SetParError(1, Fit1->GetParError(1)); // ori:0.0005
    Fitsigdraw->SetParError(2, Fit1->GetParError(2)); // free param  
    
    // Find the ND*, sigma and deltam central value
    //checkNsigErr = ( Fitsigdraw->IntegralError(Cxmin, Cxmax) <= 0.) ? 0. : Fitsigdraw->IntegralError(Cxmin, Cxmax) / binwid;
   
    checkNsig = Fitsigdraw->Integral(Cxmin, Cxmax) / binwid;
    checkNsigErr = Fitsigdraw->IntegralError(Cxmin, Cxmax) / binwid;
    //cout << "checkNsignal: " << checkNsig << " " << "checkNsignalErr: " << checkNsigErr << endl;
        
    //hdiff->Fit("Fitsig","N"); // put N option for it to not draw
    //hptrapw->Fit("Fitbkg1","","",Pimass,0.17); // fit wc tp jgn draw
    //TF1 *fdeltaMwrongcharge = (TF1 *)Alcremie-Vanilla Cream Ribbon hptrapw->GetListOfFunctions()->At(0);
    //fdeltaMwrongcharge->SetLineColor(kRed);
    //fdeltaMwrongcharge->SetLineWidth(3);
    //hDstdeltaM->Fit("Fit1","","",Pimass,0.17); //Actually Fit
  
    pr_fit = hptrapr->Fit("Fit1", "SFREMQ");
    //TF1 *fdeltaM = (TF1 *) hptrapr->GetListOfFunctions()->At(0);
    //fdeltaM->SetLineColor(kBlue);
    //fdeltaM->SetLineWidth(3);
    chi2Prob = TMath::Prob(pr_fit->Chi2(), pr_fit->Ndf());

    // Find the chi2, ndof and p-value
    chi2 = "#chi^{2}: " + toStr(pr_fit->Chi2(), 4); 
    ndof = "ndf: " + toStr(pr_fit->Ndf(), 2);
    chi2ovndof = "#chi^{2} / ndf: " + toStr(pr_fit->Chi2() / pr_fit->Ndf(), 2);
    pvalue = "p-value: " + toStr(chi2Prob, 2);

    // putting how many decimal place
    // *NEED TO CHECK THE LOGIC AGAIN!*
    decNerr, decN;
  
    if (checkNsigErr >= 1. and checkNsigErr < 10.) {
      decNerr = 2;
      if (checkNsig >= 1. and checkNsig <= 10.) {decN = 2;}    
      else if (checkNsig >= 11. and checkNsig <= 99.) {decN = 3;}
      else if (checkNsig >= 100. and checkNsig <= 999.) {decN = 4;}
      else if (checkNsig >= 1000. and checkNsig <= 9999.) {decN = 5;}
    }
  
    else if (checkNsigErr >= 10. and checkNsigErr < 100.) {decNerr = 2;
      if (checkNsig >= 1. and checkNsig <= 10.) {decN = 1;}     
      else if (checkNsig >= 11. and checkNsig <= 99.) {decN = 2;}    
      else if (checkNsig >= 100. and checkNsig <= 999.) {decN = 3;}
      else if (checkNsig >= 1000. and checkNsig <= 9999.) {decN = 4;}
    }

    else if (checkNsigErr >= 100. and checkNsigErr < 10000.) {decNerr = 3;
      if (checkNsig >= 1. and checkNsig <= 10.) {decN = 1;}   
      else if (checkNsig >= 11. and checkNsig <= 99.) {decN = 2;}
      else if (checkNsig >= 100. and checkNsig <= 999.) {decN = 3;}
      else if (checkNsig >= 1000. and checkNsig <= 9999.) {decN = 4;}
      else if (checkNsig >= 10000. and checkNsig <= 999999.) {decN = 5;} 
    }
    else {decNerr = 2; decN = 2;}
   
    N = "N(D*^{#pm}): " + toStr(checkNsig, decN) + " #pm " + toStr(checkNsigErr, decNerr);
    Nsub = "N_{sub}(D*^{#pm}): " + toStr(NSignal_aftersf1, 4) + " #pm " + toStr(uncertSig, decNerr);  // 4 is brp significant digit nk tulis
    /*
      double s3 = Fit1->GetParameter(1);
      double es3=Fit1->GetParError(1);
      double n3 = Fit1->GetParameter(2);
      double en3 = Fit1->GetParError(2);  
      double No3=n3*sqrt(2*TMath::Pi())*s3/binwidth;
      double eNo3=No3*sqrt( TMath::Power(en3/n3,2 ) + TMath::Power(es3/s3,2 ) );  
      const std::string N = Form(" N(D*^{#pm})   = %.0F #pm %.0F",No3,eNo3);
    */
    //const std::string sigma = "#sigma: " + toStr((Fit1->GetParameter(1)),2) + " #pm " + toStr((Fit1->GetParError(1)),2); // uncert small enough so boleh remove
    sigma = "#sigma: " + toStr((Fit1->GetParameter(1)),2) + " GeV";
    //const std::string Mcentre = "#DeltaM_{central}: " + toStr(Fit1->GetParameter(0)) + " #pm " + toStr(Fit1->GetParError(0),1); // uncert small enough so boleh remove
    Mcentre = "#DeltaM_{central}: " + toStr(Fit1->GetParameter(0),4) + " GeV";

    /*
    // this method not so correct as it implies for normal gaus, not modi gaus
    //double n = Fit1->GetParameter(2);
    //double en = Fit1->GetParError(2);
    //double s = Fit1->GetParameter(1);
    //double es = Fit1->GetParError(1);
    //double No = n * sqrt(2 * TMath::Pi()) * s / binwidth;
    //double eNo = No * sqrt( TMath::Power(en/n,2) + TMath::Power(es/s,2) );
    
    //const std::string N = "N(D*^{#pm}): " + toStr(No,4) + " #pm " + toStr(eNo,3); //4&3=how many digit
    //const std::string sigma = "#sigma: " + toStr(1000*s,2) + " #pm " + toStr(1000*es,2);
    //const std::string Mcentre = "#DeltaM_{central}: " + toStr(1000*Fit1->GetParameter(0)) + " #pm " + toStr(1000*Fit1->GetParError(0),2);

    double chi2Prob;
      
    //double lala = TMath::Prob(pr_fit->Chi2(), pr_fit->Ndf());
    const double lala1 = pr_fit->Chi2();
    const double lala2 = pr_fit->Ndf();
    
    chi2Prob = (lala1 <= 0.) ? 0. : TMath::Prob(pr_fit->Chi2(), pr_fit->Ndf());
    */
  
    cout << "chi2 = " << pr_fit->Chi2() << " " << "nDF = " << pr_fit->Ndf() << " " << "chi2/nDF = " << pr_fit->Chi2() / pr_fit->Ndf() << " " << "p-value = " << chi2Prob << endl;

    // legend for fit
    stdLfit = new TLegend(0.45, 0.88, .95, 0.9);
    stdLfit->SetNColumns(2);   
    stdLfit->AddEntry(Fit1, "fit to right charge", "pl");
    stdLfit->AddEntry(Fitbkgdraw, "fit to background", "pl");
    styleLeg(stdLfit, 0, 0, 42, 0.03, 0, 0);
   
    stdLfit->Draw();
    
    TLatex *txt1 = new TLatex();
    txt1->SetTextSize(0.04);
    txt1->SetNDC();
    txt1->SetTextFont(42);
    txt1->DrawLatex(xlatex, ylatex1, chi2.c_str());
    txt1->DrawLatex(xlatex, ylatex2, ndof.c_str());
    //txt1->DrawLatex(xlatex, 0.70, chi2ovndof.c_str());
    txt1->DrawLatex(xlatex, ylatex3, pvalue.c_str());
    txt1->DrawLatex(xlatex, ylatex4, N.c_str());
    txt1->DrawLatex(xlatex, ylatex5, Nsub.c_str());
    txt1->DrawLatex(xlatex, ylatex6, sigma.c_str());
    txt1->DrawLatex(xlatex, ylatex7, Mcentre.c_str());    
  } // end of if (whichPlot == "hpt" or whichPlot == "lpt" or whichPlot == "indvfit")
  
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// END OF FITTING ///////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////



  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////// STYLING HISTOGRAMS /////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////

  styleHist(hptrapr, useColr, filSty, marSty, marSiz, linWid, yOff, xOff, ploTitle, yTitle, xTitle, ylabSiz, xlabSiz, yTitSiz, xTitSiz, statHist, linSt, yMin, yMax);    
  styleHist(hptrapw, useColw, filSty, marSty, marSiz, linWid, yOff, xOff, ploTitle, yTitle, xTitle, ylabSiz, xlabSiz, yTitSiz, xTitSiz, statHist, linSt, yMin, yMax);    

  // start making shades for each regions
  auto g_gri = std::make_unique<TGraphErrors>(6); 
  g_gri->SetPoint(0, Axmax, 0.);
  g_gri->SetPoint(1, Cxmin, 0.);
  g_gri->SetPoint(2, Cxmax, 0.);
  g_gri->SetPoint(3, Exmin, 0.);
  g_gri->SetPoint(4, Exmax, 0.);
  g_gri->SetPoint(5, -1., 0.);

  // error x low, error x high
  for (auto &iP : {0, 1, 2, 3, 4}) 
    {g_gri->SetPointError(iP, 0., 10000000.);} // error x and error y for point iP

  styleGraph(g_gri.get(), kBlack, 1., 0, 0, 1.5, 4, 1);
  
  // make shades for side bands 
  // using tgraphasymmerror
  auto shade_SideBand = std::make_unique<TGraphAsymmErrors>(2); // have 2 graf_asymmerror
  shade_SideBand->SetName("shade_SideBand");
  // point for after signal
  shade_SideBand->SetPoint(0, 0.155, 100); // 1st index, x, y // x n y can be ANY point within the range that u want to shade
  // point for before signal
  shade_SideBand->SetPoint(1, 0.14, 100); // 2nd index, x, y
  // point error for after signal
  // eg. errxlow = 0.155-0.15 = 0.005, errxhigh = 0.165 - 0.155 = 0.01
  shade_SideBand->SetPointError(0, (0.155 - Exmin), (Exmax - 0.155), 200., 20000000.); // index, errxlow, errxhigh, errylow, erryhigh
  // point error for before signal
  shade_SideBand->SetPointError(1, (0.14 - Axmin), (Axmax - 0.14), 200., 20000000.); // index, errxlow, errxhigh, errylow, erryhigh  
  styleGraph(shade_SideBand.get(), kGray +2, 0.5, 1001, 0, 0, 1, 1); // 3001 for fill full

  // make shade for signal band
  // using tgraphasymmerror
  auto shade_Sig = std::make_unique<TGraphAsymmErrors>(1);
  shade_Sig->SetName("shade_Sig");
  shade_Sig->SetPoint(0, 0.145, 100); // index, x, y // index 0 coz it is the first graph
  shade_Sig->SetPointError(0, (0.145 - Cxmin), (Cxmax - 0.145), 200., 20000000.); // index, errxlow, errxhigh, errylow, erryhigh
  styleGraph(shade_Sig.get(), kPink +9, 0.4, 1001, 0, 0, 1, 1); // 3001 for fill full  

  // style legend
  stdL0 = new TLegend(0.1, 0.96, 0.99, .98); // size of legend for lower pt, hlptr
  
  stdL0->SetNColumns(4);  
  stdL0->AddEntry(hptrapr, "right charge", "pl");
  stdL0->AddEntry(hptrapw, "wrong charge", "l"); // if substract
  stdL0->AddEntry(shade_SideBand.get(), "side band", "f"); // if substract //ubahshade
  stdL0->AddEntry(shade_Sig.get(), "signal band", "f"); // if substract

  styleLeg(stdL0, 0, 0, 42, 0.03, 0, 0);

  // style canvas
  can1 = new TCanvas("can1", "can1", 200, 10, 1000, 800);
  styleCan(can1, 0.045, 0.11, 0.11, 0.035, 0, 0);
  
  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////// END OF STYLING HISTOGRAMS /////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////


  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////// DRAW AND SAVE HISTOGRAMS /////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////

  // draw axis for the histogram
  hptrapr->Draw("axis"); 
  // draw shade for side bands
  shade_SideBand->Draw("02");
  // draw shade for signal band
  shade_Sig->Draw("02");
  g_gri->Draw("0z same");

  hptrapr->Draw("pe1 func same");
  hptrapw->Draw("hist func same");
  if (whichPlot == "hpt" or whichPlot == "lpt" or whichPlot == "indvfit")
    {
      Fitbkgdraw->Draw("same");
      Fit1->Draw("same"); //Draw the Right charge fit again over the background fit
    }

  // Draw legend
  stdL0->Draw(); // draw leg at the latest overlap

  if (whichPlot != "nsigtable") {
    if (isMC == 0) {can1->SaveAs((outDir + whichPlot + "_" + whichDst + "_" + outName + ".pdf").c_str());}
    else if (isMC == 1) {can1->SaveAs((outDir + whichPlot + "_" + whichDst + "t_" + outName + ".pdf").c_str());}
    can1->Close();
  }
  ////////////////////////////////////////////////////////////////////////////////
  //////////////////// END OF DRAW AND SAVE HISTOGRAMS ///////////////////////////
  ////////////////////////////////////////////////////////////////////////////////

  
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////// NSIGTABLE AND EFFICIENCY PLOTS ///////////////////////////
  //////////////////////////// NOT YET CLEAN UP!!! ///////////////////////////////
  //////////////////////////////////////////////////////////////////////////////// 

  // for nsigtable, we want to combine all these histograms, extract the value & put in 2D plot
  if (whichPlot == "nsigtable") {

    if (isMC == 0) {RFile = new TFile((outDir + whichPlot + "_" + whichDst + "_" + outName + "_nrectab.root").c_str(), "recreate");}
    else if (isMC == 1) {RFile = new TFile((outDir + whichPlot + "_" + whichDst + "t_" + outName + "_nrectab.root").c_str(), "recreate");}      
    
    // Save your output in a textfile
    // this text file save all the necessary information
    myfile.open ((outDir + whichPlot + "_" + whichDst + "_" + outName + "_infofile.txt").c_str());
    
    // this text file save only Nsignal and its uncertainty
    Nsigfile.open ((outDir + whichPlot + "_" + whichDst + "_" + outName + "_Nsigfile.txt").c_str());
    
    // this file save necessary information to calculate efficiency
    efffile.open ((outDir + whichPlot + "_" + whichDst + "_" + outName + "_efffile.txt").c_str());
    
    for (int i = 0; i < Nsigafter.size(); i++) {
      // write/save myfile to check the values. Easy for debug   
      myfile << "range: " << Nsigafter[i].second << " " << "TotIntegralr: " << v_totintegralr[i].first
	     << " " << "TotIntegralw: " << v_totintegralw[i].first << " " << "SF: " << v_SF[i].first
	     << " " << "Nsignalb4: " << v_Nsigb4[i].first << " "
	     << "Nsigafter: " << Nsigafter[i].first
	     << " " << "unCert: " << uncerNsigafter[i].first << " " << "\n";
      
      // save the signal and its uncert in this file
      Nsigfile << Nsigafter[i].first << " " << uncerNsigafter[i].first << "\n";    
    } // end of saving Nsignal in the text file
    
    if (isMC == 1) {
      // include true histogram
      // save the value in for all of them
      for (int row = 0; row < 11; row++) {
	// if use charm MC
	//TH1F *hh = (TH1F *) inFile->Get((Varhist3 + toStr(row)).c_str()); // the truedstaryptbin
	// if use D0 MC
	hh = (TH1F *) inFile->Get((Varhist4 + toStr(row)).c_str()); // the trueDstarHHpiyptbin from _beauty42
	
	//TH1F *hh = (TH1F *) inFile->Get((Varhist5 + toStr(row)).c_str()); // the trueDstarHHpiyptbin from _semitight4 charm
	//TH1F *hh = (TH1F *) inFile->Get((Varhist6 + toStr(row)).c_str()); // the trueDstarHHpiyptbin from _semitight4 beauty
	
	for (int col = 0; col < 6; col++) {
	  // bincontent always start from 1      
	  truth.push_back({hh->GetBinContent(col + 1), row * 6 + col});
	  //cout << "hh->GetBinContent(col+1): " << hh->GetBinContent(col + 1) << " " << "bin: " << col +1 << " " << "index: " << row * 6 + col << endl;
	  uncertruth.push_back({hh->GetBinError(col + 1), row * 6 + col});
	  //cout << "hh->GetBinError = " << hh->GetBinError(col + 1) << " " << "index: " << row * 6 + col << endl;
	  //cout << "hh->GetBinContent(col+1): " << hh->GetBinContent(col + 1) << " " << "bin: " << col +1 << " " << "hh->GetBinError = " << hh->GetBinError(col +1) << " " << "index: " << row * 6 + col << endl;
	} // end of col
      } // end of row
      
      // for Dstar
      //div = 1;
      // uncomment this line if calc MC eff. using charm MC
      //BR = 0.0267; // for D* (0.68*0.04) valid for MB n MBc
      //uncerBR = BR * ( sqrt(std::pow( (0.005 / 0.68), 2) + std::pow( (0.00031 / 0.04), 2)) );
      // uncomment this line if calc MC eff. using D0 MC
      //BR = 0.6; // for D* (0.68*1) @ 0.6 (drp calculation) valid for MBD0
      //uncerBR = sqrt(std::pow( (0.00031 / 0.6), 2));
    
      // makes sure the truth and reco in the same coordinate
      if (truth.size() == Nsigafter.size()) {
	for (int i = 0; i < Nsigafter.size(); i++) {
	  //std::cout << Nsigafter[i].second << " " << Nsigafter[i].first  << " " << truth[i].first << " " << (((float(Nsigafter[i].first) / float(truth[i].first)) / BR) / div) << " efficiency" << std::endl;
	  // save Nsignal, Nsignal_uncertainty, truth, truth_uncertainty inside efffile
	  efffile << Nsigafter[i].first << " " << uncerNsigafter[i].first << " "
		  << truth[i].first << " " << uncertruth[i].first << " "
	    // use for xsec calc. comment this line if want to calculate MC efficiency
		  << (float(Nsigafter[i].first) / float(truth[i].first)) << "\n";
	  // use for MC eff. commment this line if want to calculate efficiency for cross section
	  //<< (((float(Nsigafter[i].first) / float(truth[i].first)) / BR) / div) << "\n"; // uncomment for MC eff.
	}
      }
      efffile.close();
    } // end of isMC == 1

    myfile.close();
    Nsigfile.close();   
    
    if (isMC == 0) {std::cout << "Now reading textfile " << (outDir + whichPlot + "_" + whichDst + "_" + outName + "_Nsigfile.txt").c_str() << std::endl;}
    else if (isMC == 1) {std::cout << "Now reading textfile " << (outDir + whichPlot + "_" + whichDst + "_" + outName + "_efffile.txt").c_str() << std::endl;}
    
    tree = new TTree("tree", "");
    if (isMC == 0) {tree->ReadFile((outDir + whichPlot + "_" + whichDst + "_" + outName + "_Nsigfile.txt").c_str(), "Nsigafter:uncerNsigafter");}  // 2 columns
    else if (isMC == 1) {tree->ReadFile((outDir + whichPlot + "_" + whichDst + "_" + outName + "_efffile.txt").c_str(), "Nsigafter:uncerNsigafter:truth:uncertruth:eff");}  // 5 column
  
    tree->SetBranchAddress("Nsigafter", &NsigafterDD);
    tree->SetBranchAddress("uncerNsigafter", &UncerNsigafterDD);
  
    if (isMC == 1) {
      tree->SetBranchAddress("truth", &TruthDD);
      tree->SetBranchAddress("uncertruth", &UncerTruthDD);
      tree->SetBranchAddress("eff", &EffDD);
    }

    nevent = tree->GetEntries();

    cout << "entries = " << nevent << endl;

    // Loop over all events
    for (Int_t zz = 0.; zz < nevent; zz++)
      {
	tree->GetEntry(zz);
	v_Nsigafter.push_back(NsigafterDD);
	v_uncerNsigafter.push_back(UncerNsigafterDD);
      
	// fordatatable comment
	if (isMC == 1) {
	  v_truth.push_back(TruthDD);
	  v_uncertruth.push_back(UncerTruthDD);
	  v_eff.push_back(EffDD);
	}
      }
    
    h_nume = new TH2D("N_", "Nsig", 6, 0., 3.0, 12, 0, 12); // nBinX, minX, maxX, nBinY, minY, maxY
  
    if (isMC == 1) {
      h_deno = new TH2D("Ndeno_", "", 6, 0., 3.0, 12, 0, 12); //  nBinX, minX, maxX, nBinY, minY, maxY
      h_deff = new TH2D("eff_", "", 6, 0., 3.0, 12, 0, 12); //  nBinX, minX, maxX, nBinY, minY, maxY
    }
  
    for (int iR = 1; iR < 12; ++iR) {
      for (int iC = 1; iC < 7; ++iC) {
	h_nume->SetBinContent(iC, iR, v_Nsigafter.at(6 * (iR - 1) + (iC - 1))); //indexX,indexY,value
	h_nume->SetBinError(iC, iR, v_uncerNsigafter.at(6 * (iR - 1) + (iC - 1)));

	if (isMC == 1) {
	  h_deno->SetBinContent(iC, iR, v_truth.at(6 * (iR - 1) + (iC - 1))); //indexX, indexY, value
	  h_deno->SetBinError(iC, iR, v_uncertruth.at(6 * (iR - 1) + (iC - 1))); //indexX, indexY, value
	  h_deff->SetBinContent(iC, iR, v_eff.at(6 * (iR - 1) + (iC - 1))); //indexX, indexY, value
	}
      } // end of col
    } // end of row
  
    if (whichDst == "deltamr") {
      if (h_nume) {
	ploTitle2D = "N_{D*->K#pi#pi} #Deltam_{r}";
      }
    }
    else if (whichDst == "deltam") {
      if (h_nume) {
	ploTitle2D = "N_{D*->K#pi#pi} #Deltam";
      }
    }  
  
    c00 = new TCanvas("c00", "c00", 200, 10, 1000, 800);
    c01 = new TCanvas("c01", "c01", 200, 10, 1000, 800);
    c02 = new TCanvas("c02", "c02", 200, 10, 1000, 800);

    gStyle->SetPalette(kMint);
    //gStyle->SetPalette(2);  
    TColor::InvertPalette();
    TGaxis::SetMaxDigits(3);  
    gStyle->SetPaintTextFormat(".6g");
    c00->cd();
    //styleCan(c00, 0.045, 0.11, 0.11, 0.035, 0, 0);  //top, bot,left, right
    styleCan(c00, 0.08, 0.11, 0.08, 0.13, 0, 0);  
    styleHist2D(h_nume, zMin2D, zMin2D, ploTitle2D, xTitle2D, yTitle2D, marSiz2D, yMin2D, yMax2D, xMin2D, xMax2D, useCol2D, yOff2D, xOff2D, zTitle2D);
    drawVar(c00, h_nume, "colztexte");
    //stylePal(h_nume, c00, x12D, x22D, y12D, y22D);
    drawCan(c00, (whichPlot + "_" + whichDst + "_" + outName + "_nrectab").c_str(), outDir.c_str());

    if (isMC == 1) {
      c01->cd();
      // Ntrue
      styleCan(c01, 0.08, 0.11, 0.08, 0.13, 0, 0);    
      styleHist2D(h_deno, zMin2D, zMin2D, "Ntrue_{D*->Kpipi}", xTitle2D, yTitle2D, marSiz2D, yMin2D, yMax2D, xMin2D, xMax2D, useCol2D, yOff2D, xOff2D, zTitle2D);  
      drawVar(c01, h_deno, "colztexte");
      //stylePal(h_deno, c01, x12D, x22D, y12D, y22D);  
      drawCan(c01, (whichPlot + "_" + whichDst + "t_" + outName + "_ntruetab").c_str(), outDir.c_str());

      gStyle->SetPalette(kCherry);
      TColor::InvertPalette();  
      gStyle->SetPaintTextFormat(".2g");
      //styleHist2D(h_deff, 0., 1., title.c_str() + whichPlot, "|y|", "p_{T} (GeV)", 1.2, 1., 11., 0., 2.5, kRed +1, 1.1, 1., "entries");
      styleHist2D(h_deff, zMin2D, zMax2D, "eff_{D*->K#pi#pi} in MCD0", xTitle2D, yTitle2D, marSiz2D, yMin2D, yMax2D, xMin2D, xMax2D, useCol2D, yOff2D, xOff2D, zTitle2D);
      drawVar(c02, h_deff, "colztexte");
    } // end of isMC == 1
    
    RFile->cd();
    h_nume->Write();
    
    if (isMC == 1) {
      h_deno->Write();
      h_deff->Write();
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////// Calculate uncertainties using TEfficiency /////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////
    
    if (isMC == 1) {
      
      hist1 = new TH1D("hist1", "", 72, 0, 72.);
      hist2 = new TH1D("hist2", "", 72, 0, 72.);
      
      for (Int_t ii = 1; ii < 12; ++ii) {
	for (Int_t jj = 1; jj < 7; ++jj) {
	  
	  //cout << "h_deff->GetNbinsY() value = " << h_deff->GetNbinsY() << " " << "h_deff->GetNbinsX() value = " << h_deff->GetNbinsX() << endl;
	  //cout << "h_nume->GetNbinsX() value = " << h_nume->GetNbinsX() << endl;
	  //cout << "jj = " << jj << " " << "ii = " << ii << endl;
    
	  index = (6 * (ii - 1)) + (jj - 1);
	  //cout << "index = " << index << endl;
	  //cout << "Column: " << jj << " " << "Row: " << ii << " " << "index = " << index << endl;
	  
	  hist1->SetBinContent(index, h_nume->GetBinContent(jj,ii));
	  cout << "index: " << index << " " << "h_nume->GetBinContent: " << h_nume->GetBinContent(jj,ii) << endl;
	  
	  hist1->SetBinError(index, h_nume->GetBinError(jj,ii));
	  //cout << "h_nume->GetBinError: " << h_nume->GetBinError(jj,ii) << endl;
	  
	  hist2->SetBinContent(index, h_deno->GetBinContent(jj,ii));
	  //cout << "h_deno->GetBinContent: " << h_deno->GetBinContent(jj,ii) << endl;
	  
	  hist2->SetBinError(index, h_deno->GetBinError(jj,ii));
	  //cout << "h_deno->GetBinError: " << h_deno->GetBinError(jj,ii) << endl;
	  
	  // cout all of them
	  //cout << "indx: " << index << " " << "passed: " << h_nume->GetBinContent(jj,ii) << " " << "pasErr: " << h_nume->GetBinError(jj,ii) << " " << "true: " << h_deno->GetBinContent(jj,ii) << " " << "trueErr: " << h_deno->GetBinError(jj,ii) << endl;      
     
	}
      }
      
      pEff = 0;  
      if(TEfficiency::CheckConsistency(*hist1, *hist2)) {
	pEff = new TEfficiency(*hist1, *hist2);
      }
      
      pFile = new TFile((outDir + "Teffb4BR_" + whichDst + whichPlot + ".root").c_str(), "recreate");
      //h_pass and h_total are valid and consistent histograms
      //if (TEfficiency::CheckConsistency(h_nume, h_deno)) {
      //pEff = new TEfficiency(h_nume, h_deno);
      //pEff->SetStatisticOption(TEfficiency::kBJeffrey);
      //pEff->SetStatisticOption(TEfficiency::kFNormal);
      // somehow if u use default/normal, u xdpt 65 bin eff yg diharapkan. kalau guna jeff dpt
      // this will write the TEfficiency object to "TEfffile.root"
      // AND pEff will be attached to the current directory
      pEff->SetName("g_Eff");
      pEff->Draw();
      
      pFile->cd();
      pEff->Write(); // save the eff n its uncertainty in this graph
      
      gr = new TGraphAsymmErrors(66);  
      //TEfficiency *teff = (TEfficiency *) (pFile->Get("g_EffJef"))->Clone();
      
      for (int kk = 0; kk < 66; ++kk) {
	
	// uncomment to include BR
	//Eff_afterBR = pEff->GetEfficiency(kk) / BR / div;
	//Uncer_afterBRHigh = std::abs(Eff_afterBR) * ( sqrt( std::pow(pEff->GetEfficiencyErrorUp(kk) / pEff->GetEfficiency(kk), 2.) + std::pow(uncerBR / BR, 2)) );
	//Uncer_afterBRLow = std::abs(Eff_afterBR) * ( sqrt( std::pow(pEff->GetEfficiencyErrorLow(kk) / pEff->GetEfficiency(kk), 2.) + std::pow(uncerBR / BR, 2)) );
	
	// does not include BR
	Eff_afterBR = pEff->GetEfficiency(kk);
	Uncer_afterBRHigh = std::abs(Eff_afterBR) * ( sqrt( std::pow(pEff->GetEfficiencyErrorUp(kk) / pEff->GetEfficiency(kk), 2.)) );
	Uncer_afterBRLow = std::abs(Eff_afterBR) * ( sqrt( std::pow(pEff->GetEfficiencyErrorLow(kk) / pEff->GetEfficiency(kk), 2.)) );
	
	//cout << kk << " " <<  "Checkpoint1: " << Uncer_afterBRHigh << endl;
	//cout << kk << " " <<  "Checkpoint2: " << Uncer_afterBRLow << endl;
	
	//gr->SetPoint(kk, kk, pEff->GetEfficiency(kk));
	gr->SetPoint(kk, kk, Eff_afterBR);    
	gr->SetPointError(kk, 0, 0, Uncer_afterBRLow, Uncer_afterBRHigh);
	
	// get the average uncert for up and low
	aveUncerUpLow = (Uncer_afterBRHigh + Uncer_afterBRLow) / 2.;
	//cout << kk << " " <<  "Checkpoint3: " << aveUncerUpLow << endl;
	
	v_effafterBR.push_back(Eff_afterBR);
	v_aveuncert.push_back(aveUncerUpLow);       
      }
      
      gr->SetName("graf");
      c03 = new TCanvas("c03", "c03", 200, 10, 1000, 800);
      c03->cd();
      gr->Draw("ap");
      c03->Update();
      
      // uncomment this to check if our conversion 2D->1D is ok
      //c03->SaveAs((outDir + "graf1DafterBR_" + whichDst + whichPlot + ".root").c_str());    
      
      //////////////////////////////////////////////////////////////////////////////////////////////////
      //////////////////////////// Save Efficiency and error in a nice histo ///////////////////////////
      //////////////////////////////////////////////////////////////////////////////////////////////////
      
      // full range
      h_deffafterBR = new TH2D("effnerr_", "", 6, 0., 3.0, 12, 0, 12);
      h_deffafterBR3D = new TH2D("effnerr3D_", "", 6, 0., 3.0, 12, 0, 12);
      
      // our range
      //h_deffafterBR = new TH2D("effnerr_", "", 5, 0., 2.5, 10, 1, 11);
      
      // for full range
      for (int iR = 1; iR < 12; ++iR) {
	for (int iC = 1; iC < 7; ++iC) {
	  h_deffafterBR->SetBinContent(iC, iR, v_effafterBR.at(6 * (iR - 1) + (iC - 1))); 
	  h_deffafterBR->SetBinError(iC, iR, v_aveuncert.at(6 * (iR - 1) + (iC - 1)));
	  //cout << "Column: " << iC << " " << "Row: " << iR << " " << "eff = " << v_eff.at(6 * (iR - 1) + (iC - 1)) << " " << "index: " << 6 * (iR - 1) + (iC - 1) << endl;
	  
	  // 3D histo
	  h_deffafterBR3D->SetBinContent(iC, iR, v_effafterBR.at(6 * (iR - 1) + (iC - 1)));      
	}
      }
      
      c04 = new TCanvas("c04", "c04", 200, 10, 1000, 800);
      c05 = new TCanvas("c05", "c05", 200, 10, 7000, 5000);
      
      gStyle->SetPalette(kCherry);
      //TColor::InvertPalette();  
      gStyle->SetPaintTextFormat(".2g");
      styleCan(c04, 0.08, 0.11, 0.08, 0.13, 0, 0);
      //styleCan(c04, 0.045, 0.11, 0.11, 0.035, 0, 0);
      
      // save plot only at the range yg kita nk
      //styleHist(h_deffafterBR, 0., 1., title.c_str() + whichPlot, "|y|", "p_{T} (GeV)", 1.4, 1., 11., 0., 2.5, kRed +1, 1.1, 1.);
      //styleHist2D(h_deffafterBR, 0., 1., title.c_str(), "|y|", "p_{T} (GeV)", 1.2, 1., 11., 0., 2.5, kRed +1, 1.1, 1., "entries");
      styleHist2D(h_deffafterBR, zMin2D, zMax2D, "eff_{D*->K#pi#pi} in MCD0", xTitle2D, yTitle2D, marSiz2D, yMin2D, yMax2D, xMin2D, xMax2D, useCol2D, yOff2D, xOff2D, "efficiency");
  
      drawVar(c04, h_deffafterBR, "colztexte");
      drawCan(c04, (outName + "_nefftab").c_str(), outDir.c_str());
  
      // 3D plot
      //styleHist2D(h_deffafterBR3D, 0., 1., title.c_str() + whichPlot, "|y|", "p_{T} (GeV)", 1.4, 1., 11., 0., 2.5, kRed +1, 1.8, 1.7, "entries");
      styleHist2D(h_deffafterBR3D, zMin2D, zMax2D, "eff_{D*->K#pi#pi} in MCD0", xTitle2D, yTitle2D, marSiz2D, yMin2D, yMax2D, xMin2D, xMax2D, useCol2D, 1.8, 1.7, "efficiency");  
      drawVar(c05, h_deffafterBR3D, "lego2 fb");
      drawCan(c05, (outName + "_neff3Dtab").c_str(), outDir.c_str());

      RFile->cd();
      h_deffafterBR->Write();
    } // end of isMC == 1

  gROOT->ProcessLine(".q");  
   
  } // end of whichPlot == "nsigtable" 
}// end of code

// BR from PDG online (latest)
// D*->D0pi = (67.7 +- 0.5)% = 0.677 +- 0.0050
// D0->Kpi = (3.95 +- 0.031)% = 0.0395 +- 0.00031
// D* BR = 0.0267 or 2.67 +- 0.124% (0.677 * 0.0395 = 0.0267 +- 0.00124)
