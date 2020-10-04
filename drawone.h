void drawTH1F(TH1F *hist, const char *xtitle="", int rebin=-1,double xrange_low=-1,double xrange_high=-1,double id=-1, double ymax=-1,bool logy=false, bool logx=false, std::string graphname="untitled"){

  c1->Clear();
  if(logy) c1->SetLogy();
  else c1->SetLogy(0);
  if(logx) c1->SetLogx();
  else c1->SetLogx(0);

  
  hist->GetXaxis()->SetTitle(xtitle);
  hist->GetYaxis()->SetTitle("Events");
  if(rebin!=-1) hist->Rebin(rebin);
  if(xrange_low!=xrange_high) hist->GetXaxis()->SetRangeUser(xrange_low,xrange_high);
  
  hist->Draw();

  TLegend *legend;

  ////from left to right, the legend will be signed id 1,2,3,4,5, default is 5, 1 is most left,3 is middle
  if(id==111) legend = new TLegend(.12, .70, .3, .90);
  else if(id==333) legend=new TLegend(.48, .70, .64, .90);
  else legend = new TLegend(.72, .70, .90, .90);
  legend->SetFillColor(42);
  legend->SetTextSize(0.03);

  //  legend->AddEntry(hSig,"Coh#pi-"); 
  //  legend->Draw();

  std::string s0(hist->GetName());
  if(graphname.compare("untitled")!=0) s0=graphname;
  std::string s1;
  
  s1=path+s0+".png";
  c1->Print(s1.c_str());

}

void drawTH2F(TH2F *hist, const char *xtitle="", const char *ytitle="",int rebin=-1,double xrange_low=-1,double xrange_high=-1,double yrange_low=-1,double yrange_high=-1,double id=-1,bool logy=false, bool logx=false, std::string graphname="untitled"){

  c1->Clear();
  if(logy) c1->SetLogy();
  else c1->SetLogy(0);
  if(logx) c1->SetLogx();
  else c1->SetLogx(0);


  hist->GetXaxis()->SetTitle(xtitle);
  hist->GetYaxis()->SetTitle(ytitle);
  if(rebin!=-1) hist->Rebin(rebin);
  if(xrange_low!=xrange_high) hist->GetXaxis()->SetRangeUser(xrange_low,xrange_high);
  if(yrange_low!=yrange_high) hist->GetYaxis()->SetRangeUser(yrange_low,yrange_high);

  hist->Draw("COLZ");

  TLegend *legend;

  ////from left to right, the legend will be signed id 1,2,3,4,5, default is 5, 1 is most left,3 is middle
  if(id==111) legend = new TLegend(.12, .70, .3, .90);
  else if(id==333) legend=new TLegend(.48, .70, .64, .90);
  else legend = new TLegend(.72, .70, .90, .90);
  legend->SetFillColor(42);
  legend->SetTextSize(0.03);

  //  legend->AddEntry(hSig,"Coh#pi-");
  //  legend->Draw();

  std::string s0(hist->GetName());
  if(graphname.compare("untitled")!=0) s0=graphname;
  std::string s1;

  s1=path+s0+".png";
  c1->Print(s1.c_str());

}
