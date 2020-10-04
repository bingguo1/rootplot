#include "TLegend.h"

void draw2withR(TH1* hist1, TH1 *hist2, const char *xtitle="", int rebin=-1,double xrange_low=-1,double xrange_high=-1,double id=-1, double ymax=-1,bool logy=false, bool logx=false, std::string graphname="untitled"){

  TCanvas *thisc=new TCanvas("thisc","",800,800);
  if(logy) thisc->SetLogy();
  else thisc->SetLogy(0);
  if(logx) thisc->SetLogx();
  else thisc->SetLogx(0);
  std::cout<<"hist0:"<<hist1->GetEntries()<<std::endl;  
  std::cout<<"hist1:"<<hist2->GetEntries()<<std::endl;
  hist1->GetXaxis()->SetTitle(xtitle);
  hist1->GetYaxis()->SetTitle("Ratio");
  if(rebin!=-1) { hist1->Rebin(rebin); hist2->Rebin(rebin);}
  if(xrange_low!=xrange_high) hist1->GetXaxis()->SetRangeUser(xrange_low,xrange_high);
  

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.45,  1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.13);
  pad1->SetRightMargin(0.1);
  //  pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad


  hist1->Sumw2();
  hist2->Sumw2();
  TH1F *hratio=(TH1F*)hist1->Clone();
  hratio->Divide(hist2);
  int nbin=hist1->GetNbinsX();
  for(int i=0;i<nbin;i++){
    std::cout<<"i:"<<i<<",content:"<<hist1->GetBinContent(i+1)<<endl;
    std::cout<<"i:"<<i<<",content:"<<hist2->GetBinContent(i+1)<<endl;
    std::cout<<"i:"<<i<<",content:"<<hratio->GetBinContent(i+1)<<endl;
  }

  float max=hist1->GetMaximum()>hist2->GetMaximum()?hist1->GetMaximum():hist2->GetMaximum();
  hist1->SetLineWidth(2);
  hist2->SetLineWidth(2);
  hist1->SetStats(0);
  hist1->SetLineColor(kBlue);
  hist2->SetLineColor(kRed);
  //  hist2->SetMarkerStyle(20);
  hist2->SetMarkerSize(0.6);
  hist1->SetMaximum(max*1.07);
  hist1->GetXaxis()->SetTitleFont(23);
  hist1->GetXaxis()->SetTitleSize(30);
  hist1->GetXaxis()->SetTitleOffset(2);
  hist1->GetXaxis()->SetLabelFont(23);
  hist1->GetXaxis()->SetLabelSize(25);
  hist1->GetYaxis()->SetTitleFont(23);
  hist1->GetYaxis()->SetTitleSize(30);
  hist1->GetYaxis()->SetLabelFont(23);
  hist1->GetYaxis()->SetLabelSize(25);  
  hist1->GetYaxis()->SetTitleOffset(1.55);
  //  hist1->GetYaxis()->SetMaxDigits(3);
  hist1->GetXaxis()->SetTitle("E (GeV)");
  hist1->Draw("e1");
  hist2->Draw("e1 same");
  

  TLegend *legend;

  ////from left to right, the legend will be signed id 1,2,3,4,5, default is 5, 1 is most left,3 is middle
  if(id==111) legend = new TLegend(.12, .70, .3, .90);
  else if(id==333) legend=new TLegend(.48, .70, .64, .90);
  else legend = new TLegend(.66, .70, .89, .88);
  legend->SetFillColor(0);
  legend->SetTextSize(0.04);
  //legend->SetNColumns(2);

  legend->AddEntry(hist1, "coh#pi+/- Evis ratio");
  legend->AddEntry(hist2, "flux#nu_{#mu}/#bar{#nu}_{#mu} Enu ratio");
  legend->Draw();

  
  thisc->cd();
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.35);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.13);
  pad2->SetRightMargin(0.1);
  pad2->SetBottomMargin(0.2);
  pad2->SetGridy(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad

  hratio->SetLineColor(kBlack);
  hratio->GetXaxis()->SetTitle(xtitle);
  hratio->GetYaxis()->SetTitle("Ratio");
  //  hratio->GetYaxis()->SetRangeUser(0.8,1.2);
  hratio->SetMarkerStyle(21);
  hratio->SetStats(0);
  hratio->GetXaxis()->SetTitle("E  (GeV)");
  hratio->Draw("e1");
  
  hratio->GetYaxis()->SetTitle("Double R");
  //  hratio->GetYaxis()->SetNdivisions(505);
  hratio->GetYaxis()->SetTitleSize(25);
  hratio->GetYaxis()->SetTitleFont(23);
  hratio->GetYaxis()->SetTitleOffset(1.55);
  hratio->GetYaxis()->SetLabelFont(23); // Absolute font size in pixel (precision 3)
  hratio->GetYaxis()->SetLabelSize(20);

  // X axis ratio plot settings
  hratio->GetXaxis()->SetTitleSize(25);
  hratio->GetXaxis()->SetTitleFont(23);
  hratio->GetXaxis()->SetTitleOffset(4.);
  hratio->GetXaxis()->SetLabelFont(23); // Absolute font size in pixel (precision 3)
  hratio->GetXaxis()->SetLabelSize(20);

  TLegend *leg2=new TLegend(.62, .85, .88, .95);
  leg2->SetFillColor(0);
  leg2->SetTextSize(0.07);
  leg2->AddEntry(hratio, "(coh#pi +/-) / (flux#nu_{#mu}/#bar{#nu}_{#mu})");
  leg2->Draw();




  std::string s(hist1->GetName());
  if(graphname.compare("untitled")!=0) s=graphname;

  std::string s1;
  s1=path+s+".png";
  thisc->Print(s1.c_str());

  //  thisc->SetLogy();
  //  s1=path+s+"_logy.pdf";
  //  thisc->Print(s1.c_str());


}

