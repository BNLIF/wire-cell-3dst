#include "WCP3dST/Signal.h"
#include "TRandom.h"

#include <iostream>

void WCPPIONEER::cal_track(double x_start, double x_end, double scale, double gain, TH1F *h_tot, TH1F* he, TH1F *hh, TH1F *hge, TH1F *hgh, int flag_random , double x_cathode){
  

  TH1F *he1 = (TH1F*)he->Clone("he1");
  TH1F *hh1 = (TH1F*)hh->Clone("hh1");
  TH1F *hge1 = (TH1F*)hge->Clone("hge1");
  TH1F *hgh1 = (TH1F*)hgh->Clone("hgh1");

  std::cout << x_end << " " << x_cathode << std::endl;
  
  for (Int_t i=x_start; i<x_end+1; i++){
    he1->Reset();
    hh1->Reset();
    hge1->Reset();
    hgh1->Reset();

    double q = 65;
    if(flag_random==1) q = gRandom->Gaus(65*3,94)/3.;
    if (q < 0) continue;

    cal_field(i*1., gain, q, he1, hh1, hge1, hgh1, flag_random, x_cathode);

    //    if (q==0) std::cout << he1->GetSum() << " " << hh1->GetSum() << std::endl;
    
    he->Add(he1,1);
    hh->Add(hh1,1);
    hge->Add(hge1,1);
    hgh->Add(hgh1,1);
  }

  h_tot->Add(he,1);
  h_tot->Add(hh,1);
  h_tot->Add(hgh,1);
  h_tot->Add(hge,1);
  
  delete he1;
  delete hh1;
  delete hge1;
  delete hgh1;

  

  
  
}

void WCPPIONEER::cal_field(double x, double gain, double q, TH1F *he, TH1F *hh, TH1F *hge, TH1F *hgh, int flag_random, double x_cathode){

  double x_anode = 0;
  //double x_cathode = 120;
  double x_gain = 2; // 1 um

  double v_e = 50 / 0.5; // um/ns
  double v_h = 50 / 0.6; // um/ns

  double e_w = 1./(x_cathode - x_anode) * (q/6.24e9); // 1V/120 um ...

  if (x >= x_anode && x <= x_cathode){
    double t11 = (x_cathode - x)/v_h;
    double curr_h = v_h * e_w;

    double t21 = x/v_e;
    double curr_e = v_e * e_w;

    double t1 = (x-x_gain)/v_e;
    double t2 = x/v_e;
    double t3 = t1 + (x_cathode - x_gain)/v_h;

    double random = 1;
    if (flag_random && gain >0 && q > 0)
      random = gRandom->Gaus(1, 1./sqrt(q*gain));
    
    double curr_ge = gain * v_e * e_w *random;
    double curr_gh = gain * v_h * e_w *random;
    
    for (Int_t i = 0;i!=hh->GetNbinsX();i++){
      double temp_t = hh->GetBinCenter(i+1);
      if (temp_t < t11) hh->SetBinContent(i+1,curr_h);
      if (temp_t < t21) he->SetBinContent(i+1,curr_e);
      if (temp_t >= t1 && temp_t < t2) hge->SetBinContent(i+1,curr_ge);
      if (temp_t >= t1 && temp_t < t3) hgh->SetBinContent(i+1,curr_gh);
    }
  }
}

