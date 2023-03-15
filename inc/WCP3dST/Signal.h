#ifndef SIGNAL_PIONEER_h
#define SIGNAL_PIONEER_h

#include "TH1F.h"
#include "TGraph.h"
#include "TF1.h"

namespace WCPPIONEER{
  void decon_wf(TH1F *h_nois, TGraph *g_ele, TF1 *filter, TH1F *h_decon);

  void cal_field(double x, double gain, double q, TH1F *he, TH1F *hh, TH1F *hge, TH1F *hgh, int flag_random = 1, double x_cathode = 120);

  void cal_track(double x_start, double x_end, double scale, double gain, TH1F *htot, TH1F *he, TH1F *hh, TH1F *hge, TH1F *hgh, int flag_random = 1, double x_cathode = 120, double dt = 0);

  void l1_fit(TH1F *h_nois, TGraph *g_resp, TH1F *h_sig, double gain, TH1F* h_sig_true);

  double detect_t0(TH1F *h_sig, double threshold, std::vector<std::tuple<int, int, int, double> > &identified_hits);

  void interpolate(std::vector<double>& vals_x, std::vector<double>& vals_y, double bin_width);


  void hit_reco(TH1F *h_sig, double threshold, TH1F *h_decon, TH1F *h_sig_true);

  void gauss_fit(TH1F *h_decon, double threshold, std::vector<std::tuple<int, int, int, double> > &identified_hits, std::vector<std::tuple<double, double, double, double > > &fitted_hits);
  
}

#endif
