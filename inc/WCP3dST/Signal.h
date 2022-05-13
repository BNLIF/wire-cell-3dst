#ifndef SIGNAL_PIONEER_h
#define SIGNAL_PIONEER_h

#include "TH1F.h"

namespace WCPPIONEER{
  void cal_field(double x, double gain, double q, TH1F *he, TH1F *hh, TH1F *hge, TH1F *hgh, int flag_random = 1, double x_cathode = 120);

  void cal_track(double x_start, double x_end, double scale, double gain, TH1F *htot, TH1F *he, TH1F *hh, TH1F *hge, TH1F *hgh, int flag_random = 1, double x_cathode = 120);
  
}

#endif
