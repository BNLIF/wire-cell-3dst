#include "WCPRess/MarqFitAlg.h"

#include <iostream>

#include "TF1.h"
#include "TH1F.h"
#include "TFile.h"

int main(int argc, char* argv[])
{

  TF1 *f1 = new TF1("f1","gaus",0,1000);
  Double_t par[3];
  par[0] = 5;
  par[1] = 5;
  par[2] = 1;
  f1->SetParameters(par);

  TF1 *f2 = new TF1("f2","gaus",0,10);
  par[0] = 3;
  par[1] = 7;
  par[2] = 1;
  f2->SetParameters(par);
  
  TFile *file = new TFile("test_marqfit.root","RECREATE");
  TH1F *h1 = new TH1F("h1","h1",1000,0,10);
  float y[1000];
  for (Int_t i=0;i!=1000;i++){
    h1->SetBinContent(i+1,f1->Eval(h1->GetBinCenter(i+1)) + f2->Eval(h1->GetBinCenter(i+1)));
    y[i] = h1->GetBinContent(i+1);
  }
  h1->SetDirectory(file);

  const int nData = 1000;
  const int nParam = 6;

  float p[6]={4,500,100,1,700,100};
  float perr[6]={0.1,0.1,0.1,0.1,0.1,0.1};
  float lambda = 0.01;
  float chiSqr;
  float dchiSqr;

  gshf::MarqFitAlg *fitter;
  fitter->mrqdtfit(lambda, p, y, nParam, nData, chiSqr, dchiSqr);

  for (Int_t i=0;i!=nParam;i++){
    std::cout << p[i] << " ";// << par[1] << " " << par[2] << std::endl;
  }
  std::cout << std::endl;

  std::cout << lambda << " " << chiSqr << " " << dchiSqr << std::endl;

  TH1F *h2 = new TH1F("h2","h2",1000,0,10);
  par[0] = p[0];
  par[1] = p[1]/100.;
  par[2] = p[2]/100.;
  par[3] = p[3];
  par[4] = p[4]/100.;
  par[5] = p[5]/100.;
  f1->SetParameters(par);
  f2->SetParameters(&par[3]);
  for (Int_t i=0;i!=1000;i++){
    h2->SetBinContent(i+1,f1->Eval(h2->GetBinCenter(i+1)) + f2->Eval(h2->GetBinCenter(i+1)));
  }
  
  
  file->Write();
  file->Close();
  
 
  
  return 0;

}
