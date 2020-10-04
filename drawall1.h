#include "TLegend.h"
#include "style.h"
TCanvas *c1=new TCanvas("c1","",1);
std::string path="pics/";
void drawN(int N,TH1D** hist, const char *xtitle="", int rebin=-1,double xrange_low=-1,double xrange_high=-1,double id=-1, double ymax=-1,bool logy=false, bool logx=false, std::string graphname="untitled"){

  usestyle();
  c1->Clear();
  if(logy) c1->SetLogy();
  else c1->SetLogy(0);
  if(logx) c1->SetLogx();
  else c1->SetLogx(0);
  std::cout<<"hist0:"<<hist[0]->GetEntries()<<std::endl;
  std::cout<<"hist1:"<<hist[1]->GetEntries()<<std::endl;
  for(int i=0;i<N;i++){
    hist[i]->GetXaxis()->SetTitle(xtitle);
    hist[i]->GetYaxis()->SetTitle("Events");
    if(rebin!=-1) hist[i]->Rebin(rebin);
    if(xrange_low!=xrange_high) hist[i]->GetXaxis()->SetRangeUser(xrange_low,xrange_high);
  }

  int maxN=0;
  float max=hist[0]->GetMaximum();
  for(int i=1;i<N;i++){
    if(hist[i]->GetMaximum()>hist[maxN]->GetMaximum())
      {  maxN=i;max=hist[maxN]->GetMaximum();}
  }


  //  hist[0]->Scale(hist[1]->Integral()/hist[0]->Integral());
  hist[0]->SetLineColor(kBlue);
  hist[1]->SetLineColor(kBlack);
  if(N>2) hist[2]->SetLineColor(kRed);
  if(N>3) hist[3]->SetLineColor(kGreen);
  hist[0]->SetMaximum(max*1.07);
  hist[0]->Draw();
  for(int i=1;i<N;i++){
    hist[i]->Draw("same");
  }

  TLegend *legend;

  ////from left to right, the legend will be signed id 1,2,3,4,5, default is 5, 1 is most left,3 is middle
  if(id==111) legend = new TLegend(.12, .70, .3, .90);
  else if(id==333) legend=new TLegend(.48, .70, .64, .90);
  else legend = new TLegend(.62, .70, .80, .90);
  legend->SetFillColor(0);
  legend->SetTextSize(0.03);
  //legend->SetNColumns(2);
  legend->AddEntry(hist[0], "H tgt");
  legend->AddEntry(hist[1], "non-H tgt");
  //  legend->AddEntry(hist[0], "True (with true formula)");
  //  legend->AddEntry(hist[1], "True (with reco formula)");
  //  legend->AddEntry(hist[2], "Reco (with true formula)");
  //  legend->AddEntry(hist[3], "Reco (with reco formula)");

  legend->Draw();

  std::string s(hist[0]->GetName());
  if(graphname.compare("untitled")!=0) s=graphname;

  std::string s1;
  s1=path+s+".png";
  c1->Print(s1.c_str());



}

void drawall(TH1D** hist, const char *xtitle="", int rebin=-1,double xrange_low=-1,double xrange_high=-1,double id=-1, double ymax=-1,bool logy=false, bool logx=false, std::string graphname="untitled"){

  usestyle();
  c1->Clear();
  if(logy) c1->SetLogy();
  else c1->SetLogy(0);
  if(logx) c1->SetLogx();
  else c1->SetLogx(0);
  std::cout<<"hist0:"<<hist[0]->GetEntries()<<std::endl;  
  std::cout<<"hist1:"<<hist[1]->GetEntries()<<std::endl;
  for(int i=0;i<2;i++){
    hist[i]->SetLineWidth(2);
    hist[i]->GetXaxis()->SetTitle(xtitle);
    hist[i]->GetYaxis()->SetTitle("Events");
    if(rebin!=-1) hist[i]->Rebin(rebin);
    if(xrange_low!=xrange_high) hist[i]->GetXaxis()->SetRangeUser(xrange_low,xrange_high);
  }


  /*
  TH1F *hNC,*hNuMu,*hMC,*hBkg;  // nm means numu
  hNuMu=(TH1F*)hist[5]->Clone();
  hNuMu->Add(hist[6]);
  hNuMu->Add(hist[7]);
  hNuMu->Add(hist[9]);


  hNC=(TH1F*)hist[3]->Clone();
  hNC->Add(hist[8]);


  hBkg=(TH1F*)hNuMu->Clone();
  hBkg->Add(hNC);
  hBkg->Add(hist[0]);
  hBkg->Add(hist[2]);
  hBkg->Add(hist[4]);

  hMC=(TH1F*)hBkg->Clone();
  hMC->Add(hist[1]);

  double max=std::max(hMC->GetMaximum(), hist[10]->GetMaximum());


  hNuMu->SetLineColor(8);
  //  hNmcc->SetFillColor(8);
  //  hNmcc->SetFillStyle(3544);
  hBkg->SetLineColor(kRed);
  hNC->SetLineColor(kMagenta);
  //  hNC->SetFillColor(kMagenta);
  //  hNC->SetFillStyle(3781);
  hMC->SetLineColor(kBlack);
  //  hist[10]->SetLineColor(kBlack);
  hist[10]->SetLineColor(kBlack);
  hist[10]->SetMarkerStyle(20);
  hist[10]->SetMarkerSize(1);
  hist[10]->Sumw2();


  hist[1]->SetLineColor(4);
  hist[0]->SetLineColor(22);
  hist[2]->SetLineColor(7);
  hist[4]->SetLineColor(5);
  hist[1]->SetLineWidth(2);
  hist[0]->SetLineWidth(2);
  hist[2]->SetLineWidth(2);
  hist[4]->SetLineWidth(2);
  hNuMu->SetLineWidth(2);
  hBkg->SetLineWidth(2);
  hMC->SetLineWidth(2);
  hNC->SetLineWidth(2);
  hist[10]->SetLineWidth(2);

  if(ymax!=-1) hNuMu->SetMaximum(ymax*1.05);
  else hNuMu->SetMaximum(max*1.07);
  hNuMu->Draw("hist");
  hist[0]->Draw("hist same");
  hist[1]->Draw("hist same");
  hist[2]->Draw("hist same");
  hist[4]->Draw("hist same");
  hBkg->Draw("hist same");
  hNC->Draw("hist same");
  hist[10]->Draw("same");
  hMC->Draw("hist same");
  */
  //  hist[1]->Scale(hist[0]->Integral()/hist[1]->Integral());  
  float max=hist[0]->GetMaximum()>hist[1]->GetMaximum()?hist[0]->GetMaximum():hist[1]->GetMaximum();
  hist[0]->SetLineColor(kBlue);
  hist[1]->SetLineColor(kBlack);
  hist[0]->SetMaximum(max*1.07);
  hist[0]->Draw();
  hist[1]->Draw("same");
  

  TLegend *legend;

  ////from left to right, the legend will be signed id 1,2,3,4,5, default is 5, 1 is most left,3 is middle
  if(id==111) legend = new TLegend(.12, .70, .3, .90);
  else if(id==333) legend=new TLegend(.48, .70, .64, .90);
  else legend = new TLegend(.72, .70, .90, .90);
  legend->SetFillColor(0);
  legend->SetTextSize(0.03);
  //legend->SetNColumns(2);
  legend->AddEntry(hist[0], "True (beam frame)");
  legend->AddEntry(hist[1], "Reco (beam frame)");

  legend->Draw();

  std::string s(hist[0]->GetName());
  if(graphname.compare("untitled")!=0) s=graphname;

  std::string s1;
  s1=path+s+".png";
  c1->Print(s1.c_str());

  //  c1->SetLogy();
  //  s1=path+s+"_logy.pdf";
  //  c1->Print(s1.c_str());
}




