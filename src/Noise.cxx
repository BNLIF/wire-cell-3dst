#include "WCP3dST/Noise.h"
#include "TRandom.h"
#include "TVirtualFFT.h"

#include <iostream>

void WCPPIONEER::Calculate_Electronic_Noise(TH1F *h_nois, TGraph *g_noise){
  const Int_t nbin = h_nois->GetNbinsX();
  double value_re[nbin];
  double value_im[nbin];

  
  
  for (Int_t i=0;i!=nbin;i++){
    double freq = 2./nbin*i;
    if (i>nbin/2.) freq = 2./nbin * (nbin-i);
    //    double phi = gRandom->Uniform(-3.1415926,3.1415926);
    //double r = gRandom->Gaus(0,g2->Eval(freq)
    //value_re[i] = 62.6*sqrt(2.)*cos(phi)/nbin;
    //value_im[i] = 62.6*sqrt(2.)*sin(phi)/nbin;
    value_re[i] = gRandom->Gaus(0,g_noise->Eval(freq) * sqrt(nbin/1024.))/nbin;
    value_im[i] = gRandom->Gaus(0,g_noise->Eval(freq) * sqrt(nbin/1024.))/nbin;
  }

  
  
  Int_t n = nbin;
  TVirtualFFT *ifft = TVirtualFFT::FFT(1,&n,"C2R M K");
  ifft->SetPointsComplex(value_re,value_im);
  ifft->Transform();
  TH1 *fb = TH1::TransformHisto(ifft,0,"Re");

  //std::cout << nbin << std::endl;
  
  for (Int_t i=0;i!=nbin;i++){
    h_nois->SetBinContent(i+1,fb->GetBinContent(i+1));
  }
}
