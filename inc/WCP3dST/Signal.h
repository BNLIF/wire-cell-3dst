#ifndef SIGNAL_PIONEER_h
#define SIGNAL_PIONEER_h

#include "TH1F.h"
#include "TGraph.h"

namespace WCPPIONEER{
  void cal_field(double x, double gain, double q, TH1F *he, TH1F *hh, TH1F *hge, TH1F *hgh, int flag_random = 1, double x_cathode = 120);

  void cal_track(double x_start, double x_end, double scale, double gain, TH1F *htot, TH1F *he, TH1F *hh, TH1F *hge, TH1F *hgh, int flag_random = 1, double x_cathode = 120);

  void l1_fit(TH1F *h_nois, TGraph *g_resp, TH1F *h_sig, double gain, TH1F* h_sig_true);

  void interpolate(std::vector<double>& vals_x, std::vector<double>& vals_y, double bin_width);
  
}

#endif
