void plot_filter(){
  TFile *file = new TFile("output.root");
  // TH1F *h_nois = (TH1F*)file->Get("h_nois");
  // TH1F *h1 = new TH1F("h1","h1",100,-15,15);
  // for (Int_t i=0;i!=h_nois->GetNbinsX();i++){
  //   h1->Fill(h_nois->GetBinContent(i+1));
  // }
  // h1->Draw();
  // h1->Fit("gaus");


  TGraph *g_noise = (TGraph*)file->Get("g_noise");
  TGraph *g_signal = (TGraph*)file->Get("g_signal");

  Int_t nbin = 1024;
  
  TH1F *h1 = new TH1F("h1","h1",nbin,0,nbin/2.);
  TH1F *h2 = new TH1F("h2","h2",nbin,0,2.);
  for (Int_t i=0;i!=h1->GetNbinsX();i++){
    if (h1->GetBinCenter(i+1)<20.)
      h1->SetBinContent(i+1,g_signal->Eval(h1->GetBinCenter(i+1)));
  }
  
  //  h1->Draw();
  TH1 *hr = h1->FFT(0,"MAG");
  
  hr->Draw();
  for (Int_t i=0;i!=nbin;i++){
    double freq = 2./nbin*i;
    if (i>nbin/2.) freq = 2./nbin*(nbin-i);
    double content = pow(hr->GetBinContent(i+1),2)/(pow(hr->GetBinContent(i+1),2) + pow(g_noise->Eval(freq)*sqrt(nbin/1024.),2));
    //h1->SetBinContent(i+1,content);
    h2->SetBinContent(i+1,content);
  }

  double scale = 1./h2->GetBinContent(1);
  h2->Scale(scale);

  h2->Draw("hist");

  h2->SetTitle("S^{2}/(S^{2}+N^{2})  512 ns");
  h2->SetXTitle("Freq (GHz)");
  // Gaussian Filter ...
  TF1 *f1 = new TF1("f1","exp(-[0]*x*x)",0,1);
  f1->SetParameter(0,4.);
  f1->Draw("same");
  h2->SetLineColor(1);
  f1->SetLineColor(4);

  TF1 *f2 = new TF1("f2","exp(-[0]*pow(x,[1]))",0,1);
  f2->SetParameter(0,1588.);
  f2->SetParameter(1,11.80);
  // f2->SetParameter(2,0);
  //  f2->SetParameter(3,2);
  // h2->Fit(f2,"","+",0,0.56);
  f2->Draw("same");
  h2->GetXaxis()->SetRangeUser(0,1);

  TLegend *le1 = new TLegend(0.6,0.6,0.89,0.89);
  le1->SetFillColor(10);
  le1->AddEntry(h2,"Simulation","l");
  le1->AddEntry(f1,"Gauss F.","l");
  le1->AddEntry(f2,"Wiener F.","l");
  le1->Draw();


  TCanvas *c2 = new TCanvas("c2","c2",800,600);
  TH1F *h3 = new TH1F("h3","h3",400,-20.,20.);
  TH1F *h4 = new TH1F("h4","h4",400,-20.,20.);
  {
    const Int_t nbin = 400.; 
    double value_re[nbin];
    double value_im[nbin];
    
    for (Int_t i=0;i!=nbin;i++){
      double freq = 2./nbin*i*10.;
      if (i>nbin/2.) freq = 2./nbin * (nbin-i);
      value_re[i] = f1->Eval(freq);
      value_im[i] = 0.;
    }
    Int_t n = nbin;
    TVirtualFFT *ifft = TVirtualFFT::FFT(1,&n,"C2R M K");
    ifft->SetPointsComplex(value_re,value_im);
    ifft->Transform();
    TH1 *fb = TH1::TransformHisto(ifft,0,"Re");
    //    fb->Draw();
    for (Int_t i=0;i!=nbin;i++){
      int bin = i+nbin/2.;
      if (bin>=nbin) bin-=nbin;
      h3->SetBinContent(bin+1,fb->GetBinContent(i+1));
    }
    
    for (Int_t i=0;i!=nbin;i++){
      double freq = 2./nbin*i*10.;
      if (i>nbin/2.) freq = 2./nbin * (nbin-i);
      value_re[i] = f2->Eval(freq);
      value_im[i] = 0.;
    }

    ifft->SetPointsComplex(value_re,value_im);
    ifft->Transform();
    TH1 *fb1 = TH1::TransformHisto(ifft,0,"Re");

    for (Int_t i=0;i!=nbin;i++){
      int bin = i+nbin/2.;
      if (bin>=nbin) bin-=nbin;
      h4->SetBinContent(bin+1,fb1->GetBinContent(i+1));
    }
    
    
  }


  
  h3->Draw();
  h4->Draw("same");
  h4->SetLineColor(2);

  h3->GetYaxis()->SetRangeUser(-10,25);
  h3->SetXTitle("Time (ns)");
  h3->SetTitle("Filters");
  h3->SetLineColor(4);
  h4->SetLineColor(2);
  h3->SetLineWidth(2);
  h4->SetLineWidth(2);

  TLegend *le2 = new TLegend(0.6,0.6,0.89,0.89);
  le2->AddEntry(h3,"Gauss F.","l");
  le2->AddEntry(h4,"Wiener F.","l");
  le2->Draw();
    
}
