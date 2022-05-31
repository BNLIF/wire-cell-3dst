void plot_compare(int seed = 1){

  gStyle->SetOptStat(0);
  gStyle->SetLabelSize(0.07,"Y");
  gStyle->SetTitleSize(0.07,"Y");
  gStyle->SetLabelSize(0.07,"X");
  gStyle->SetTitleSize(0.07,"X");
  gStyle->SetNdivisions(506,"X");
  gStyle->SetNdivisions(506,"Y");


  
  TFile *file = new TFile(Form("./out_files/output_%d.root",seed));
  TCanvas *c1 = new TCanvas("c1","c1",800,800);
  c1->Divide(2,2);
  c1->cd(1);
  TH1F *htot = (TH1F*)file->Get("h_tot");
  TH1F *he = (TH1F*)file->Get("he");
  TH1F *hh = (TH1F*)file->Get("hh");
  TH1F *hge = (TH1F*)file->Get("hge");
  TH1F *hgh = (TH1F*)file->Get("hgh");

  htot->Draw();
  htot->SetXTitle("time (ns)");
  //  htot->SetYTitle("e #dot V/ns");
  htot->SetYTitle("current (A)");
  //htot->SetTitle(Form("Field Response x=%d nm, gain=%d",int(x), int(gain)));
  htot->SetTitle("Field Response: track");
  htot->SetLineWidth(2);
  htot->SetLineStyle(2);
  htot->SetLineColor(8);

  htot->SetLabelSize(0.07,"Y");
  htot->SetTitleSize(0.07,"Y");
  htot->SetLabelSize(0.07,"X");
  htot->SetTitleSize(0.07,"X");
  htot->SetNdivisions(506,"X");
  htot->SetNdivisions(506,"Y");
  
  
  
  
  hh->Draw("same");
  hh->SetLineWidth(2);
  hh->SetLineColor(1);

  he->Draw("same");
  he->SetLineWidth(2);
  he->SetLineColor(2);
  
  hge->Draw("same");
  hge->SetLineColor(6);
  hge->SetLineWidth(2);

  hgh->Draw("same");
  hgh->SetLineColor(4);
  hgh->SetLineWidth(2);
  htot->Draw("same");

  TLegend *le2 = new TLegend(0.6,0.6,0.89,0.89);
  le2->AddEntry(he,"Ion. elec.","l");
  le2->AddEntry(hh,"Ion. hole","l");
  le2->AddEntry(hge,"Gain elec.","l");
  le2->AddEntry(hgh,"Gain hole","l");
  le2->AddEntry(htot,"Total","l");
  le2->Draw();

  c1->cd(2);
  TGraph *g_ele = (TGraph*)file->Get("g_ele");
  g_ele->Draw("AL");
  g_ele->SetTitle("Electronics Response");
  g_ele->GetXaxis()->SetTitle("Time (ns)");
  g_ele->GetYaxis()->SetTitle("mV/fC");
  
  c1->cd(3);
  TH1F *h_nois = (TH1F*)file->Get("h_nois");
  h_nois->Draw();
  h_nois->GetXaxis()->SetRangeUser(0,30);
  h_nois->SetTitle("Simulated Waveform");
  h_nois->SetXTitle("Time (ns)");
  h_nois->SetYTitle("mV");


  h_nois->SetLabelSize(0.07,"Y");
  h_nois->SetTitleSize(0.07,"Y");
  h_nois->SetLabelSize(0.07,"X");
  h_nois->SetTitleSize(0.07,"X");
  h_nois->SetNdivisions(506,"X");
  h_nois->SetNdivisions(506,"Y");
  
  
  TGraph *g_signal = (TGraph*)file->Get("g_signal");
  g_signal->Draw("Lsame");
  g_signal->SetLineColor(2);
 

  c1->cd(4);
  TH1F *h_sig = (TH1F*)file->Get("h_sig");
  TH1F *h_sig_true = (TH1F*)file->Get("h_sig_true");

  h_sig->Draw();
  h_sig->SetXTitle("time (ns)");
  h_sig->SetYTitle("fC");
  h_sig->SetTitle("Truth vs. Reco");
  h_sig_true->Draw("same");
  h_sig_true->SetLineColor(2);

  h_sig->SetLabelSize(0.07,"Y");
  h_sig->SetTitleSize(0.07,"Y");
  h_sig->SetLabelSize(0.07,"X");
  h_sig->SetTitleSize(0.07,"X");
  h_sig->SetNdivisions(506,"X");
  h_sig->SetNdivisions(506,"Y");

  
  TLegend *le1 = new TLegend(0.6,0.6,0.89,0.89);
  le1->SetHeader("480 e = 0.077 fC");
  le1->AddEntry(h_sig,Form("Reco: %4.2f", h_sig->GetSum()),"l");
  le1->AddEntry(h_sig_true,Form("Truth: %4.2f", h_sig_true->GetSum()),"l");
  le1->Draw();
  
}
