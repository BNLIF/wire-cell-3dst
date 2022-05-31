#include "WCP3dST/Signal.h"
#include "TRandom.h"
#include "WCPRess/LassoModel.h"
#include "WCPRess/ElasticNetModel.h"
#include <Eigen/Dense>
#include <TVirtualFFT.h>
#include <TFile.h>
#include <iostream>

#include <set>
#include <map>

using namespace Eigen;

double WCPPIONEER::detect_t0(TH1F *h_sig, double threshold){
  double t0 = -1;

  int start_bin, max_bin, end_bin;
  std::vector<std::tuple<int, int, int, int> > identified_hits;

  for (Int_t i=0;i<h_sig->GetNbinsX();i++){
    double content = h_sig->GetBinContent(i+1);
    if (content > threshold){
      max_bin = i;
      start_bin = i;
      bool flag_continue = true;
      while(flag_continue){
	if (start_bin - 1 >= 0 ){
	  if (h_sig->GetBinContent(start_bin) > threshold * 0.1){
	    start_bin --;
	  }else{
	    flag_continue = false;
	  }
	}else
	  flag_continue = false;
      }
      for (end_bin = i; end_bin < h_sig->GetNbinsX(); end_bin++){
	if (h_sig->GetBinContent(end_bin+1) > h_sig->GetBinContent(max_bin+1))
	  max_bin = end_bin;
	if (h_sig->GetBinContent(end_bin+1) < threshold * 0.1)
	  break;
      }

      double sum = 0;
      for (int j= start_bin; j<= end_bin;j++){
	sum += h_sig->GetBinContent(j+1);
      }

      //std::cout << sum << std::endl;

      if (sum > threshold*10.)
	identified_hits.push_back(std::make_tuple(start_bin, max_bin, end_bin, sum));
      //std::cout << start_bin << " " << max_bin << " " << end_bin << " " << sum << std::endl;
      
      i = end_bin +1;
    }
  }

  if (identified_hits.size()>0){
    double max = 0;
    for (size_t i=0;i!=identified_hits.size();i++){
      if (std::get<3>(identified_hits.at(i)) > max){
	max = std::get<3>(identified_hits.at(i));
	t0 = h_sig->GetBinCenter(std::get<0>(identified_hits.at(i))+1);
      }
    }
    //    t0 = h_sig->GetBinCenter(std::get<0>(identified_hits.front())+1);
  }

  //  std::cout << threshold << " " << t0 << " " << identified_hits.size() << std::endl;

  // std::cout << identified_hits.size() << std::endl;
  
  return t0;
}


void WCPPIONEER::l1_fit(TH1F *h_nois, TGraph *g_resp, TH1F *h_sig, double gain, TH1F *h_sig_true){
  const int nbin = h_sig->GetNbinsX();
  double t_min = h_sig->GetBinCenter(1);
  double t_max = h_sig->GetBinCenter(nbin);

  std::vector<double> vals_x;
  // std::vector<double> vals_xmin;
  // std::vector<double> vals_xmax;
  std::vector<double> vals_y;
  std::vector<double> vals_yth;
  for (Int_t i=0;i!=h_nois->GetNbinsX();i++){
    double t = h_nois->GetBinCenter(i+1);
    double content = h_nois->GetBinContent(i+1);
    if (t >= t_min && t<=t_max+20){
      vals_x.push_back(t);
      // vals_xmin.push_back(h_nois->GetBinLowEdge(i+1));
      // vals_xmax.push_back(h_nois->GetBinLowEdge(i+1) + h_nois->GetBinWidth(i+1));
      vals_y.push_back(content);

      if (fabs(content) > 2.8*3){
	vals_yth.push_back(fabs(content)/2.8);
      }else{
	vals_yth.push_back(0);
      }
    }
  }
  int nbin_fit = vals_x.size();

  //WCPPIONEER::interpolate(vals_x, vals_y, h_sig->GetBinWidth(1));

  
  VectorXd W = VectorXd::Zero(nbin_fit);
  MatrixXd G = MatrixXd::Zero(nbin_fit, nbin);

  //  std::cout << nbin_fit << " " << nbin << " " << gain << std::endl;

  // check threshold ...
  for (int i = 0; i!=nbin_fit; i++){
    double sum = vals_yth.at(i);
    double max = vals_yth.at(i);
    if (i >0) {
      sum += vals_yth.at(i-1);
      if (vals_yth.at(i-1)> max) max = vals_yth.at(i-1);
    }
    if (i < nbin_fit-1) {
      sum += vals_yth.at(i+1);
      if (vals_yth.at(i+1) > max) max = vals_yth.at(i+1);
    }
    
    if (!(max > 4 && sum >6)) vals_yth.at(i) = 0;
  }

  std::map<int, double> indices;
  
  for (Int_t i=0;i!=nbin_fit;i++){
    if (i==0){
      if (vals_yth.at(i) >0 ) {
	// indices.insert(0);
	// indices.insert(1);
	// indices.insert(2);
	// indices.insert(3);

	double max = 0;
	for (Int_t k=0;k!=4;k++){
	  if (k < nbin_fit)
	    if (max < vals_yth.at(k)) max = vals_yth.at(k); 
	}
	for (Int_t k=0;k!=4;k++){
	  if (k < nbin_fit)
	    if (vals_yth.at(k) > 0)
	      indices[i] = max;
	}
      }
    }else{
      if (vals_yth.at(i) >0 && vals_yth.at(i-1) ==0 ) {

	double max = 0;
	for (Int_t k=0;k!=4;k++){
	  if (i+k < nbin_fit)
	    if (max < vals_yth.at(i+k)) max = vals_yth.at(i+k); 
	}
	indices[i] = max;
	for (Int_t k=1;k!=4;k++){
	  if (i-k>=0) indices[i-k] = max; //.insert(i-k);
	  if (i+k < nbin_fit)
	    if (vals_yth.at(i+k) > 0 ) indices[i+k] = max; //.insert(i+k);
	}
      }
    }
  }

  //std::cout << indices.size() << std::endl;

  
  
  for (Int_t i=0;i!=nbin_fit;i++){

    double scale = 1;
    auto it = indices.find(i);
    if (it != indices.end()) {
      double max = 20;
      if (max < it->second) max = it->second;
      scale = 20 / max;
      if (scale < 0.1) scale = 0.1;
      //      std::cout << i << " " << scale << std::endl;
      //scale = 1.0;
      //std::cout << i << " " << indices[i] << std::endl;
    }
    
    double error = sqrt(2.8*2.8+ pow(vals_y.at(i)*0.02,2)); // 2% uncertainty ...
    
    W(i) = vals_y.at(i) / error / gain / scale;
    double t1 = vals_x.at(i);
    // double t1_min = vals_xmin.at(i);
    // double t1_max = vals_xmax.at(i);

    //    std::cout << t1 << " " << t1_min << " " << t1_max << std::endl;
    
    for (Int_t j=0; j!=nbin; j++){
      double t2 = h_sig->GetBinCenter(j+1);
      double t2_min = h_sig->GetBinLowEdge(j+1);
      double t2_max = t2_min + h_sig->GetBinWidth(j+1);
      
      double sum = 0, sum1 = 0;
      // for (Int_t k=0;k!=10;k++){
      // 	// 	double t = t1_min + (k+0.5)/10.*(t1_max - t1_min);
      // 	//if (t>=t2){
      // 	double t = t2_min + (k+0.5)/10.*(t2_max - t2_min);
      // 	if (t1 >=t){
      // 	  sum += g_resp->Eval(t1-t);
      // 	  sum1 ++;
      // 	}
      // }
      if (t1 > t2){
      	sum = g_resp->Eval(t1-t2);
      	sum1 = 1;
      }
      
      
      if (sum1 > 0){
	//      if (t1 > t2)
	//	std::cout << g_resp->Eval(t1-t2) << " " << sum/sum1 << std::endl;
	//	G(i,j) = g_resp->Eval(t1-t2) /2.8 / 6241. * 200; // fC and normalize by ENC
	G(i,j) = sum/sum1 /error / 6241. * 200 / scale; // fC and normalize by ENC
      }else
	G(i,j) = 0;
    }
  }

  double lambda = 1.0;
  WCP::LassoModel m2(lambda, 100000, 0.05);
  m2.SetData(G, W);
  m2.Fit();
  VectorXd beta = m2.Getbeta();

  VectorXd Wp = G * beta;

  VectorXd beta_true = beta;
  
  for (int i=0;i!=nbin;i++){
    // std::cout << beta(i) << std::endl;
    h_sig->SetBinContent(i+1,beta(i) * gain * 200./6241.);
    beta_true(i) = h_sig_true->GetBinContent(i+1)/gain/200.*6241.;
  }

  
  VectorXd Wpp = G * beta_true;
  for (Int_t i=0;i!=nbin_fit;i++){
    //    std::cout << i << " " << vals_yth.at(i) << " " << W(i) << " " << Wp(i)  << " " << Wpp(i) << std::endl;
  }
  
  
}

void WCPPIONEER::interpolate(std::vector<double>& vals_x, std::vector<double>& vals_y, double bin_width){
  double old_width = (vals_x.back()-vals_x.front())*1.0/(vals_x.size()-1);
  TH1F *htemp1 = new TH1F("htemp1","htemp1",vals_x.size(),vals_x.front() - old_width/2. , vals_x.back() + old_width/2.);
  for (Int_t i=0;i!=vals_x.size();i++){
    htemp1->SetBinContent(i+1, vals_y.at(i));
  }
  TH1 *htemp1_r = htemp1->FFT(0,"MAG");
  TH1 *htemp1_ph = htemp1->FFT(0,"PH");

  int new_nbins = vals_x.size() * int(old_width/bin_width);
  // hold the signal 
  TH1F *htemp2 = new TH1F("htemp2","htemp2", new_nbins , vals_x.front() - old_width/2. , vals_x.back() + old_width/2.);

  const Int_t old_nbin = htemp1->GetNbinsX();
  const Int_t nbin = htemp2->GetNbinsX();
  Int_t shift = nbin/old_nbin/2.;

  // std::cout << "Interpolate " << nbin << " " << old_nbin << " " << shift << std::endl;
  
  double value_re[nbin];
  double value_im[nbin];
  for (Int_t i=0;i!=nbin;i++){
    if (i < old_nbin/2. || i > nbin - old_nbin/2.){
      value_re[i] = htemp1_r->GetBinContent(i+1) * cos(htemp1_ph->GetBinContent(i+1))/old_nbin ;
      value_im[i] = htemp1_r->GetBinContent(i+1) * sin(htemp1_ph->GetBinContent(i+1))/old_nbin ;
    }else{
      value_re[i] = 0;
      value_im[i] = 0;
    }
  }

  Int_t n = nbin;
  TVirtualFFT *ifft = TVirtualFFT::FFT(1,&n,"C2R M K");
  ifft->SetPointsComplex(value_re,value_im);
  ifft->Transform();
  TH1 *fb = TH1::TransformHisto(ifft,0,"Re");

  for (Int_t i=0;i!=nbin;i++){
    int bin_num = i+1-shift;
    if (bin_num <0) bin_num += nbin;
    
    htemp2->SetBinContent(i+1,fb->GetBinContent(bin_num));
  }


  vals_x.clear();
  vals_y.clear();
  for (Int_t i=0;i!=htemp2->GetNbinsX();i++){
    vals_x.push_back(htemp2->GetBinCenter(i+1));
    vals_y.push_back(htemp2->GetBinContent(i+1));
  }

  // TFile *file1 = new TFile("temp.root","RECREATE");
  // htemp1->SetDirectory(file1);
  // htemp2->SetDirectory(file1);
  // file1->Write();
  // file1->Close();
  
  
  delete fb;
  delete ifft;
  
  delete htemp1;
  delete htemp2;
  delete htemp1_r;
  delete htemp1_ph;
  
  //  std::cout << vals_x.front() << " " << vals_x.back() << " " << bin_width << " " << (vals_x.back()-vals_x.front())*1.0/(vals_x.size()-1) << std::endl;
}


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

