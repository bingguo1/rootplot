#include <TStyle.h>
#include <TROOT.h>
#include <iostream>
void usestyle(){

  TStyle *bgStyle=new TStyle("bgStyle","My own style");


  bgStyle->SetCanvasColor(-1);
  bgStyle->SetPadColor(-1);
  bgStyle->SetFrameFillColor(-1);
  //  bgStyle->SetHistFillColor(-1);
  bgStyle->SetTitleFillColor(-1);
  bgStyle->SetFillColor(-1);
  bgStyle->SetFillStyle(4000);

  bgStyle->SetStatStyle(0);
  bgStyle->SetTitleStyle(0);

  bgStyle->SetFrameBorderMode(0);   // with out this, your canvas right and bottom border will be red and black
  bgStyle->SetPadBorderMode(0);
  bgStyle->SetPalette(1,0);
  bgStyle->SetOptStat(0);
  bgStyle->SetOptTitle(0);
  //  bgStyle->SetHistLineWidth(3);
  bgStyle->SetLabelSize(0.040,"xyz");
  bgStyle->SetTitleSize(0.045,"xyz");
  //  bgStyle->SetTitleXSize(0.035,"xyz");
  //  bgStyle->SetTitleYSize(0.035,"xyz");
  //  bgStyle->SetLineWidth(1);
  bgStyle->SetTitleFont(22,"xyz");
  bgStyle->SetLabelFont(22,"xyz");

  bgStyle->SetCanvasColor(0);
  //  bgStyle->SetCanvasBorderMode(0);
  //  bgStyle->SetCanvasBorderSize(0);
  //  bgStyle->SetLegendFillColor(0);
  bgStyle->SetLegendBorderSize(0);
  //  bgStyle->SetLegendTextSize(0.03);
  gROOT->ForceStyle(kTRUE);  // this line is needed for some parameter like hist line width
  gROOT->SetStyle("bgStyle");

  std::cout<<"*****************styles are set!^^^^^^^^^^^^^^^^^^"<<std::endl;
  return;


}
