//plot phase space using tgraph
// usage: root -l phase_space_general.cxx

#include "/home/zulaiha/PhD/merge_code/PlotUtil.h"

void phase_space_general() {
  
  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(false);
  TGaxis::SetMaxDigits(2);

  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetHatchesLineWidth(2);
  
  std::vector<float> v_rapBin = {-5., -2.1, -2.0, -1., -0.5, 0., 0.5, 1., 2.0, 2.1, 3.5, 5.};  

  TH1D *h_phase = new TH1D("h_phase", "h_phase", v_rapBin.size() -1, v_rapBin.data());
  
  const string yTitle = "D meson p_{T} (GeV)";
  const string xTitle = "D meson (pseudo-)rapidity";
  const string mirror = "mirrored";
  const string from = "from";
  const string LHCb = "LHCb";  
  const double yMin = 0.5,
    yMax = 120.,
    yOff = 1.15,
    xOff = 1.,
    ylabSiz = 0.038,
    xlabSiz = 0.04,
    yTitSiz = 0.04,
    xTitSiz = 0.04,
    statHist = 0.,
    linSt = 1.,
    xlatex = 0.17,
    ylatex1 = 0.38,
    ylatex2 = 0.34,
    ylatex3 = 0.3;
  
  auto g_LHCb = std::make_unique<TGraphAsymmErrors>(1);
  // 1st index, x, y // x n y can be ANY point within the range that u want to shade  
  g_LHCb->SetPoint(0, 3., 10.); 

  // index, errxlow, errxhigh, errylow, erryhigh
  // 3 (any point) - 2.0 (xmin) = 1.0
  // 4.5 (xmax) - 3 (any point) = 1.5
  // 10. (any point) - 0.0 (ymin) = 10.
  // 15 (ymax) - 10. (any point) = 5
  g_LHCb->SetPointError(0, 1.0, 1.5, 10., 5.);

  // mirror from LHCb
  auto g_LHCbmir = std::make_unique<TGraphAsymmErrors>(1);
  g_LHCbmir->SetPoint(0, -3., 10.); 
  g_LHCbmir->SetPointError(0, -1., -1.5, 10., 5.);  
  
  auto g_ATLAS = std::make_unique<TGraphAsymmErrors>(1);
  g_ATLAS->SetPoint(0, 1., 90.);
  g_ATLAS->SetPointError(0, 3.1, 1.1, 86.5, 10.); 

  auto g_ALICE = std::make_unique<TGraphAsymmErrors>(1);
  g_ALICE->SetPoint(0, 1., 26.);
  g_ALICE->SetPointError(0, 1.5, -0.5, 26., 10.);   

  auto g_CMS5 = std::make_unique<TGraphAsymmErrors>(1);
  g_CMS5->SetPoint(0, 0., 90.);
  g_CMS5->SetPointError(0, 1., 1., 88., 10.);

  auto g_CMS13 = std::make_unique<TGraphAsymmErrors>(1);
  g_CMS13->SetPoint(0, 0., 90.);
  g_CMS13->SetPointError(0, 2.1, 2.1, 86., 10.);
  
  auto g_CMS7 = std::make_unique<TGraphAsymmErrors>(1);
  g_CMS7->SetPoint(0, 0., 90.);
  g_CMS7->SetPointError(0, 2.5, 2.5, 89., 30.);

  // Styling
  styleHist(h_phase, 0, 0, 0, 0, 0, yOff, xOff, "", yTitle, xTitle, ylabSiz, xlabSiz, yTitSiz, xTitSiz, statHist, linSt, yMin, yMax);    

  styleGraph(g_LHCb.get(), kOrange -2, 0.4, 1001, 0, 0, 1, 1); // 3001 for fill full
  styleGraph(g_LHCbmir.get(), kOrange -2, 0.4, 1001, 0, 0, 1, 1);
  //styleGraph(g_LHCbmir.get(), kPink -2, 0.3, 1001, 0, 0, 1, 1);    
  styleGraph(g_ATLAS.get(), kSpring -1, 0.4, 1001, 0, 0, 1, 1); 
  styleGraph(g_ALICE.get(), kAzure +9, 0.5, 1001, 0, 0, 1, 1); 
  styleGraph(g_CMS5.get(), kTeal +3, 1, 3753, 0, 0, 1, 1);
  styleGraph(g_CMS13.get(), kBlack, 0.5, 3735, 0, 0, 1, 1); 
  styleGraph(g_CMS7.get(), kPink -1, 0.4, 0., 0, 0, 1, 4);
  
  TLegend *leg1 = new TLegend(0.1, 0.91, 0.99, 0.98);

  leg1-> SetNColumns(3);
  leg1->AddEntry(g_CMS7.get(), "CMS 7 TeV", "f"); 
  leg1->AddEntry(g_CMS5.get(), "CMS 5 TeV", "f"); 
  leg1->AddEntry(g_CMS13.get(), "CMS 13 TeV", "f"); 
  leg1->AddEntry(g_ALICE.get(), "ALICE 7, 5 TeV", "f"); 
  leg1->AddEntry(g_LHCb.get(), "LHCb 7, 5, 13 TeV", "f"); 
  leg1->AddEntry(g_ATLAS.get(), "ATLAS 7 TeV", "f"); 

  styleLeg(leg1, 0, 0, 42, 0.03, 0, 0);
  
  TCanvas *c1 = new TCanvas("c1", "c1", 200, 10, 1000, 700);
  c1->SetLogy(1);
  
  h_phase->Draw("axis");
  g_LHCb->Draw("02");
  g_LHCbmir->Draw("02");  
  g_ATLAS->Draw("02");
  g_ALICE->Draw("02");
  g_CMS5->Draw("02");
  g_CMS13->Draw("02");
  g_CMS7->Draw("02");

  TLatex *txt1 = new TLatex();
  txt1->SetTextSize(0.04);
  txt1->SetNDC();
  txt1->SetTextFont(42);
  txt1->DrawLatex(xlatex, ylatex1, mirror.c_str());
  txt1->DrawLatex(xlatex, ylatex2, from.c_str());
  txt1->DrawLatex(xlatex, ylatex3, LHCb.c_str());
  
  leg1->Draw();
  c1->RedrawAxis();
  c1->SaveAs("phase_graph.pdf");
  gROOT->ProcessLine(".q");
}

