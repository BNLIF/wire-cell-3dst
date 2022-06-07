#ifndef NOISE_PIONEER_h
#define NOISE_PIONEER_h

#include "TH1F.h"
#include "TGraph.h"

namespace WCPPIONEER{
  void Calculate_Electronic_Noise(TH1F *h_nois, TGraph *g_noise);

}

#endif
