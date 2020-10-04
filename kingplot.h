#include <iostream>
#include <vector>
#include <string>
#include "TOrdCollection.h"
#include "TObjArray.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TFile.h"
#include "TCut.h"
#include "TTree.h"
#include "TLegend.h"
using std::cout;
using std::endl;

class VarInfo{
 private:
  int fDimension[2];
  int fNchannel;
  int fND;
  int fRebin;
  std::string fGraphname;
  bool fLogx;
  bool fLogy;
  int fId;

 public:
  const char* fName;
  const char* fTitle;
  const char* fXtitle;
  int fNbin;
  double fXlow;
  double fXhigh;
  
  

  VarInfo(int n,const char  *name, const char *xtitle, int rebin, double xlow=-5, double xhigh=-5, int id=-5, bool logy=false, bool logx=false, std::string graphname="untitled");
  VarInfo(int m,int n, const char  *name, const char *xtitle, int rebin, double xlow=-5, double xhigh=-5, int id=-5, bool logy=false, bool logx=false, std::string graphname="untitled");
  VarInfo(const char  *Name,const char* Title,int Bin, double Xlow, double Xup, const char *Xtitle, int n, int id=-5);
  void setBin(int Bin) { fNbin=Bin;}
  void setRange(double xlow, double xhigh){ fXlow=xlow; fXhigh=xhigh;}
  int  getNchannel(){ return fNchannel;}
  friend class KingPlot;
};


class KingPlot{
 private:

  TCanvas *fCan;
  TLegend *fLeg;
  const char * fWeight;
  TFile *fFile;
  TTree *fTree;
  std::string fPath;
  std::string fSuffix;
  std::string fPrefix;
  TCut *fCuts;
  int currentVar;
  int TTnvars;
  int nvars;

  bool fStyleSet;
  std::vector<VarInfo> fInfos;
  TCollection *vars;
  TObjArray *varhists;
  std::vector<VarInfo> fTTinfos;
  TCollection *TTvars;
  TObjArray *TTvarhists;

 public:
  KingPlot(){ fFile=0; fCan=0; nvars=0; fSuffix=""; fPrefix="";vars=new TOrdCollection(20); TTvars=new TOrdCollection(20); fStyleSet=false; TTnvars=0; fCuts=0;}
  void createfromtree(VarInfo varin);
  void settree(const char *name){ fTree=(TTree*)fFile->Get(name);}
  void setweight(const char *name) { fWeight=name;}
  void setcuts(TCut *cuts) { fCuts=cuts; cout<<fCuts[0]<<endl;}
  void setpicpath(std::string path) {fPath=path;}
  void setinputfile(const char  *name);
  void setpresuffix(std::string pre, std::string post){ fPrefix=pre;fSuffix=post;}
  void load(VarInfo varin);
  void load(int n,const char  *name, const char *xtitle,int rebin, double xlow=-5, double xhigh=-5, int id=-5, bool logy=false, bool logx=false, std::string graphname="untitled");
  void load(int m,int n, const char  *name, const char *xtitle, int rebin, double xlow=-5, double xhigh=-5, int id=-5, bool logy=false, bool logx=false, std::string graphname="untitled");
  void plotall();
  void plot(const char  *name);
  void drawN();
  void plot1array(int N,TH1F **hist);
  void plottree();
  void drawN(int N, TH1F** hist, const char *xtitle="", int rebin=1,double xrange_low=-1,double xrange_high=-1,int id=-1 ,bool logy=false, bool logx=false, std::string graphname="untitled");
};

