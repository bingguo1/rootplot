#include "TLegend.h"
#include "style.h"
TCanvas *c1=new TCanvas("c1","",1);
std::string path="pics/";

// not twod histogram ,TH2D TH2F, but two d histogram ARRAY
void draw2D(int M,int N,TH1F* hist[][4], const char *xtitle="", int rebin=-1,double xrange_low=-1,double xrange_high=-1,double id=-1, double ymax=-1,bool logy=false, bool logx=false, std::string graphname="untitled"){


}


void draw1Dof2D(int M,int N,TH1F** hist, const char *xtitle="", int rebin=-1,double xrange_low=-1,double xrange_high=-1,double id=-1, double ymax=-1,bool logy=false, bool logx=false, std::string graphname="untitled"){

  

}
