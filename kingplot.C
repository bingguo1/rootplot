#include <string>
#include <cstdlib>
#include "TLegend.h"
#include "kingplot.h"
#include "/home2/bing/utilities/style.h"
using std::cout;
using std::endl;
VarInfo::VarInfo(int n,const char  *name, const char *xtitle, int rebin, double xlow, double xhigh, int id, bool logy, bool logx, std::string graphname){
  fName=name;
  fXtitle=xtitle;
  fDimension[0]=1;
  fDimension[1]=n;
  fND=1;
  fNchannel=n;
  fGraphname=graphname;
  fRebin=rebin;
  fXlow=xlow;
  fXhigh=xhigh;
  fLogx=logx;
  fLogy=logy;
  fId=id;
}

VarInfo::VarInfo(int m,int n,const char  *name, const char *xtitle, int rebin, double xlow, double xhigh, int id, bool logy, bool logx, std::string graphname){
  fName=name;
  fXtitle=xtitle;
  fDimension[0]=m;
  fDimension[1]=n;
  fND=2;
  fNchannel=n;
  fGraphname=graphname;
  fRebin=rebin;
  fXlow=xlow;
  fXhigh=xhigh;
  fLogx=logx;
  fLogy=logy;
  fId=id;
}

VarInfo::VarInfo(const char  *name,const char* title,int Bins, double Xlow, double Xup, const char *Xtitle, int n, int id){
  // this function is used to create histograms and project from tree 
  // don't load this VarInfo into kingplot
  fName=name;
  fTitle=title;
  fXtitle=Xtitle;
  fNbin=Bins;
  fXlow=Xlow;
  fXhigh=Xup;
  fDimension[0]=1;
  fDimension[1]=n;
  fND=1;
  fNchannel=n;
  fRebin=1;
  fLogx=false;
  fLogy=false;
  fId=id;
  fGraphname="untitled";
  
}


void KingPlot::setinputfile(const char  *name){
  fFile=new TFile(name);  
  if(fFile->IsZombie()){
    cout<<"failed openning file!"<<endl;
    exit(-1);
  }
}


void KingPlot::load(VarInfo varin){

  if(fFile==0){ std::cerr<<" file name not defined! "<<std::endl; return;}
  fInfos.push_back(varin);
  nvars++;
  TH1F *hist;
  int m=varin.fDimension[0];
  int n=varin.fDimension[1];
  varhists=new TObjArray(varin.fNchannel);
  if(m>1) {
    for(int i=0;i<m;i++){
      for(int j=0;j<n;j++){
	//cout<<"j:"<<j<<endl;
	bool exist=fFile->GetListOfKeys()->Contains(Form("%s%d%d",varin.fName,i,j));
	if(!exist) {cout<<"this object does not exist in the file!!!!!!!!!!!!!"<<endl; exit(-1);}
	hist=(TH1F*) fFile->Get(Form("%s%d%d",varin.fName,i,j));
	//      cout<<"j:"<<j<<": "<< hist->GetEntries()<<endl;
	varhists->Add(hist);
      }
    }
  }
  else {
    for(int j=0;j<n;j++){
      hist=(TH1F*) fFile->Get(Form("%s%d",varin.fName,j));
      varhists->Add(hist);
    }
  }
    
  varhists->SetName(varin.fName);
  vars->Add(varhists);
  varhists->Print();
  //  vars->Print();
  
}

void KingPlot::load(int n,const char  *name, const char *xtitle,int rebin, double xlow, double xhigh, int id, bool logy, bool logx, std::string graphname){

  VarInfo varin(n,name,xtitle,rebin,xlow,xhigh,id,logy,logx,graphname);
  load(varin);

}

void KingPlot::load(int m,int n, const char  *name, const char *xtitle,int rebin, double xlow, double xhigh, int id, bool logy, bool logx, std::string graphname){
  VarInfo varin(m,n,name,xtitle,rebin,xlow,xhigh,id,logy,logx,graphname);
  load(varin);

}

// the following will create histogram and then 

void KingPlot::createfromtree(VarInfo varin){

  if(fFile==0){ std::cerr<<" file name not defined! "<<std::endl; exit(-1);}
  if(fTree==0){std::cerr<<" tree  not loaded! "<<std::endl; exit(-1);}
  if(fCuts==0) {std::cerr<<"cuts  not loaded! "<<std::endl; exit(-1);}

  fTTinfos.push_back(varin);
  TTnvars++;
  TH1F *hist;
  int n=varin.fDimension[1];
  TTvarhists=new TObjArray(n);


  for(int j=0;j<n;j++){
    
    hist=new TH1F(Form("%s%d",varin.fName,j),varin.fTitle,varin.fNbin,varin.fXlow,varin.fXhigh);
    fTree->Project(Form("%s%d",varin.fName,j),varin.fName,fWeight*fCuts[j]);
    //    tree->Project(Form("%sbeforeNN%d",var[j]->fName,i),Form("%s",var[j]->fName),wt*onecut*Form("mode==%d",i));    
    TTvarhists->Add(hist);
    //    cout<<"j:"<<j<<",inte:"<< hist->Integral(0,100)<<endl;
  }

  TTvarhists->SetName(varin.fName);
  TTvars->Add(TTvarhists);
  TTvarhists->Print();
}




void KingPlot::plotall(){

  std::cout<<"going to plot following vars' histograms:"<<std::endl;
  vars->Print();
  if(fCan==0) {fCan=new TCanvas("fCan","",1); cout<<"built canvas"<<endl;}
  TIter myiter(vars);
  int ivar=0;

  while(varhists=(TObjArray*)myiter.Next()){

    currentVar=ivar;
    const int m=fInfos[ivar].fDimension[0];
    const int n=fInfos[ivar].fDimension[1];
    for(int i=0;i<m;i++){
      TH1F *hist[n];
      for(int j=0;j<n;j++){
        hist[j]=(TH1F*)varhists->At(i*n+j);
      }
      plot1array(n,hist);
    }
    ivar++;

  }// while end
}

void KingPlot::plottree(){
  std::cout<<"going to plot following vars' histograms:"<<std::endl;
  TTvars->Print();
  if(fCan==0) {fCan=new TCanvas("fCan","",1); cout<<"built canvas"<<endl;}
  TIter myiter(TTvars);
  int ivar=0;

  while(TTvarhists=(TObjArray*)myiter.Next()){
    //currentVar=ivar;
    const int n=fTTinfos[ivar].fDimension[1];
    TH1F *hist[n];
    for(int j=0;j<n;j++){
      hist[j]=(TH1F*)TTvarhists->At(j);
    }
    fCan->Clear();
    VarInfo a=fTTinfos[ivar];
    drawN(a.fNchannel,hist,a.fXtitle, a.fRebin, a.fXlow, a.fXhigh, a.fId, a.fLogy, a.fLogx, a.fGraphname);
    ivar++;
  }

}


void KingPlot::plot1array(int N,TH1F **hist){

  VarInfo a=fInfos[currentVar];
  fCan->Clear();
  drawN(a.fNchannel,hist,a.fXtitle, a.fRebin, a.fXlow, a.fXhigh, a.fId, a.fLogy, a.fLogx, a.fGraphname);

}

void KingPlot::drawN(int N, TH1F** hist, const char *xtitle, int rebin,double xrange_low,double xrange_high,int id ,bool logy, bool logx, std::string graphname){

  //  if(!fStyleSet) { usestyle(); fStyleSet=true;}
  if(fCan==0) {fCan=new TCanvas("fCan","",1); cout<<"built canvas"<<endl;}
  usestyle();
  
  gStyle->SetLabelSize(0.040,"xyz");
  gStyle->SetTitleSize(0.045,"xyz");
  gStyle->SetTitleFont(22,"xyz");
  gStyle->SetLabelFont(22,"xyz");

  if(logy) fCan->SetLogy();
  else fCan->SetLogy(0);
  if(logx) fCan->SetLogx();
  else fCan->SetLogx(0);

  for(int i=0;i<N;i++){
    hist[i]->SetLineWidth(2);
    hist[i]->GetXaxis()->SetTitle(xtitle);
    hist[i]->GetYaxis()->SetTitle("Events");
    if(rebin!=1) hist[i]->Rebin(rebin);
    if(xrange_low!=xrange_high) hist[i]->GetXaxis()->SetRangeUser(xrange_low,xrange_high);
  }
  TH1F *hBac=(TH1F*)hist[1]->Clone();
  for(int i=2;i<N;i++){
    hBac->Add(hist[i]);
  }
  //  hist[0]->Sumw2();
  //  hist[0]->Scale(hBac->Integral()/hist[0]->Integral());
  
  int maxN=0;
  float max=hist[0]->GetMaximum();
  for(int i=1;i<N;i++){
    if(hist[i]->GetMaximum()>hist[maxN]->GetMaximum())
      {  maxN=i;max=hist[maxN]->GetMaximum();}
  }

  max=max>hBac->GetMaximum()?max:hBac->GetMaximum();

  hist[0]->SetMarkerStyle(20);
  hist[0]->SetMarkerSize(0.3);
  hist[0]->Sumw2();
  hist[0]->SetMarkerColor(kBlack);
  hist[1]->SetLineColor(kGreen);
  hist[2]->SetLineColor(kBlue);
  hist[3]->SetLineColor(kRed);
  hBac->SetLineColor(kBlack);
  hist[0]->SetMaximum(max*1.07);
  hist[0]->SetMinimum(0);
  hist[0]->Draw("e1");
  hist[0]->GetXaxis()->SetTitleSize(0.045);
  hist[0]->GetYaxis()->SetTitleSize(0.045);
  hist[0]->GetXaxis()->SetLabelSize(0.04);
  hist[0]->GetYaxis()->SetLabelSize(0.04);
  hist[0]->GetXaxis()->SetTitleFont(22);
  hist[0]->GetYaxis()->SetTitleFont(22);
  hist[0]->GetXaxis()->SetLabelFont(22);
  hist[0]->GetYaxis()->SetLabelFont(22);  

  for(int i=1;i<N;i++){
    hist[i]->Draw("same");
  }
  hBac->Draw("same");

  ////from left to right, the legend will be signed id 1,2,3,4,5, default is 5, 1 is most left,3 is middle
  if(id==111) fLeg = new TLegend(.12, .70, .3, .90);
  else if(id==333) fLeg=new TLegend(.48, .70, .64, .90);
  else fLeg = new TLegend(.75, .70, .93, .90);
  fLeg->SetFillColor(0);
  fLeg->SetFillStyle(0);
  fLeg->SetTextSize(0.03);
  //fLeg->SetNColumns(2);
  fLeg->AddEntry(hist[0], "coh#pi");
  fLeg->AddEntry(hist[1], "DIS");
  fLeg->AddEntry(hist[2], "QE");
  fLeg->AddEntry(hist[3], "RES");
  fLeg->AddEntry(hBac, "Bkg");
  fLeg->Draw();

  std::string s(hist[0]->GetName());
  if(graphname.compare("untitled")!=0) s=graphname;

  std::string s1;
  s1=fPrefix+fPath+s+fSuffix+".png";
  cout<<"s1:"<<s1<<endl;
  fCan->Print(s1.c_str());

}



