#include "/home2/bing/utilities/gccroot.h"
//#include "asciiinfo2.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "kingplot.h"
#include "TCut.h"
using std::cout;
using std::endl;

int main(){
  
  KingPlot aa;
  aa.setpicpath("pic/");
  aa.setinputfile("afternn.root");
  aa.settree("nnTree");
  aa.setweight("weight");

  TCut onecut="NN>0.7";
  //  TCut onecut="1";
  TCut cuts[4];
  cuts[0]=onecut&&"mode==0";
  cuts[1]=onecut&&"mode==1";
  cuts[2]=onecut&&"mode==2";
  cuts[3]=onecut&&"mode==3";
  aa.setcuts(cuts);
  aa.setpresuffix("","postNN");

  const int NV=10;
  VarInfo *var[NV];

  var[0]=new VarInfo("zeta","",20,0,0.2,"#zeta",4);
  var[1]=new VarInfo("rhopi","",20,0,0.5,"#rho",4);
  var[2]=new VarInfo("T","",40,0,0.1,"t",4);
  var[3]=new VarInfo("misPt","",30,0,0.4,"misPt",4);
  var[4]=new VarInfo("thetaMupi","",30,0,1.4,"#theta_{#mu}^{#pi}",4,111);
  var[5]=new VarInfo("resPt","",30,-0.4,0.2,"intrinsic Pt - missing Pt",4);
  var[6]=new VarInfo("phimupi","",30,0,200,"#phi_{#mu}^{#pi}",4,111);
  var[7]=new VarInfo("phimispthad","",30,0,200,"#phi_{mispt}^{had}",4);
  var[8]=new VarInfo("ppi","",40,0,3,"p_{#pi}",4);
  var[9]=new VarInfo("Enu","",30,0,20,"E_{#nu}",4);


  for(int i=0;i<NV;i++){
    cout<<"i:"<<i<<endl;
    aa.createfromtree(*var[i]);
  }

  aa.plottree();


}
