#include <iostream>

#include "WCP3dST/Noise.h"
#include "WCP3dST/Signal.h"

#include "TRandom.h"
#include "TFile.h"
#include "TVirtualFFT.h"
#include "TTree.h"

using namespace WCPPIONEER;
using namespace std;

int main(int argc, char* argv[])
{

  int flag_noise = 1;
  int flag_fluct = 1;
  double gain = 9;
  double t0 = 6.31;
  int seed = 0;
  double norm = 1.;
  int nbin = 250;
  double x1 = 60; // um
  double x2 = 1.5; // ns
  double scale_2nd = 0.9;
  int capacitance = 4;
  for(Int_t i = 1; i < argc; i++){
    switch(argv[i][1]){
    case 'n':
      flag_noise = atoi(&argv[i][2]);
      break;
    case 'f':
      flag_fluct = atoi(&argv[i][2]);
      break;
    case 'g':
      gain = atof(&argv[i][2]);
      break;
    case 't':
      t0 = atof(&argv[i][2]);
      break;
    case 's':
      seed = atoi(&argv[i][2]);
      break;
    case 'm':
      norm = atof(&argv[i][2]);
      break;
    case 'b':
      nbin = atoi(&argv[i][2]);
      break;
    case 'x':
      x1 = atof(&argv[i][2]);
      break;
    case 'y':
      x2 = atof(&argv[i][2]);
      break;
    case 'z':
      scale_2nd = atof(&argv[i][2]);
      break;
    case 'c':
      capacitance = atoi(&argv[i][2]);
      break;
    }
  }


  std::cout << "Gain: " << gain << std::endl;
  
  gRandom->SetSeed(seed);

  t0 = gRandom->Uniform(6.0,6.5);
  
  
  Double_t x[500]={0.025, 0.075, 0.125, 0.175, 0.225, 0.275, 0.325, 0.375, 0.425, 0.475, 0.525, 0.575, 0.625, 0.675, 0.725, 0.775, 0.825, 0.875, 0.925, 0.975, 1.025, 1.075, 1.125, 1.175, 1.225, 1.275, 1.325, 1.375, 1.425, 1.475, 1.525, 1.575, 1.625, 1.675, 1.725, 1.775, 1.825, 1.875, 1.925, 1.975, 2.025, 2.075, 2.125, 2.175, 2.225, 2.275, 2.325, 2.375, 2.425, 2.475, 2.525, 2.575, 2.625, 2.675, 2.725, 2.775, 2.825, 2.875, 2.925, 2.975, 3.025, 3.075, 3.125, 3.175, 3.225, 3.275, 3.325, 3.375, 3.425, 3.475, 3.525, 3.575, 3.625, 3.675, 3.725, 3.775, 3.825, 3.875, 3.925, 3.975, 4.025, 4.075, 4.125, 4.175, 4.225, 4.275, 4.325, 4.375, 4.425, 4.475, 4.525, 4.575, 4.625, 4.675, 4.725, 4.775, 4.825, 4.875, 4.925, 4.975, 5.025, 5.075, 5.125, 5.175, 5.225, 5.275, 5.325, 5.375, 5.425, 5.475, 5.525, 5.575, 5.625, 5.675, 5.725, 5.775, 5.825, 5.875, 5.925, 5.975, 6.025, 6.075, 6.125, 6.175, 6.225, 6.275, 6.325, 6.375, 6.425, 6.475, 6.525, 6.575, 6.625, 6.675, 6.725, 6.775, 6.825, 6.875, 6.925, 6.975, 7.025, 7.075, 7.125, 7.175, 7.225, 7.275, 7.325, 7.375, 7.425, 7.475, 7.525, 7.575, 7.625, 7.675, 7.725, 7.775, 7.825, 7.875, 7.925, 7.975, 8.025, 8.075, 8.125, 8.175, 8.225, 8.275, 8.325, 8.375, 8.425, 8.475, 8.525, 8.575, 8.625, 8.675, 8.725, 8.775, 8.825, 8.875, 8.925, 8.975, 9.025, 9.075, 9.125, 9.175, 9.225, 9.275, 9.325, 9.375, 9.425, 9.475, 9.525, 9.575, 9.625, 9.675, 9.725, 9.775, 9.825, 9.875, 9.925, 9.975, 10.025, 10.075, 10.125, 10.175, 10.225, 10.275, 10.325, 10.375, 10.425, 10.475, 10.525, 10.575, 10.625, 10.675, 10.725, 10.775, 10.825, 10.875, 10.925, 10.975, 11.025, 11.075, 11.125, 11.175, 11.225, 11.275, 11.325, 11.375, 11.425, 11.475, 11.525, 11.575, 11.625, 11.675, 11.725, 11.775, 11.825, 11.875, 11.925, 11.975, 12.025, 12.075, 12.125, 12.175, 12.225, 12.275, 12.325, 12.375, 12.425, 12.475, 12.525, 12.575, 12.625, 12.675, 12.725, 12.775, 12.825, 12.875, 12.925, 12.975, 13.025, 13.075, 13.125, 13.175, 13.225, 13.275, 13.325, 13.375, 13.425, 13.475, 13.525, 13.575, 13.625, 13.675, 13.725, 13.775, 13.825, 13.875, 13.925, 13.975, 14.025, 14.075, 14.125, 14.175, 14.225, 14.275, 14.325, 14.375, 14.425, 14.475, 14.525, 14.575, 14.625, 14.675, 14.725, 14.775, 14.825, 14.875, 14.925, 14.975, 15.025, 15.075, 15.125, 15.175, 15.225, 15.275, 15.325, 15.375, 15.425, 15.475, 15.525, 15.575, 15.625, 15.675, 15.725, 15.775, 15.825, 15.875, 15.925, 15.975, 16.025, 16.075, 16.125, 16.175, 16.225, 16.275, 16.325, 16.375, 16.425, 16.475, 16.525, 16.575, 16.625, 16.675, 16.725, 16.775, 16.825, 16.875, 16.925, 16.975, 17.025, 17.075, 17.125, 17.175, 17.225, 17.275, 17.325, 17.375, 17.425, 17.475, 17.525, 17.575, 17.625, 17.675, 17.725, 17.775, 17.825, 17.875, 17.925, 17.975, 18.025, 18.075, 18.125, 18.175, 18.225, 18.275, 18.325, 18.375, 18.425, 18.475, 18.525, 18.575, 18.625, 18.675, 18.725, 18.775, 18.825, 18.875, 18.925, 18.975, 19.025, 19.075, 19.125, 19.175, 19.225, 19.275, 19.325, 19.375, 19.425, 19.475, 19.525, 19.575, 19.625, 19.675, 19.725, 19.775, 19.825, 19.875, 19.925, 19.975, 20.025, 20.075, 20.125, 20.175, 20.225, 20.275, 20.325, 20.375, 20.425, 20.475, 20.525, 20.575, 20.625, 20.675, 20.725, 20.775, 20.825, 20.875, 20.925, 20.975, 21.025, 21.075, 21.125, 21.175, 21.225, 21.275, 21.325, 21.375, 21.425, 21.475, 21.525, 21.575, 21.625, 21.675, 21.725, 21.775, 21.825, 21.875, 21.925, 21.975, 22.025, 22.075, 22.125, 22.175, 22.225, 22.275, 22.325, 22.375, 22.425, 22.475, 22.525, 22.575, 22.625, 22.675, 22.725, 22.775, 22.825, 22.875, 22.925, 22.975, 23.025, 23.075, 23.125, 23.175, 23.225, 23.275, 23.325, 23.375, 23.425, 23.475, 23.525, 23.575, 23.625, 23.675, 23.725, 23.775, 23.825, 23.875, 23.925, 23.975, 24.025, 24.075, 24.125, 24.175, 24.225, 24.275, 24.325, 24.375, 24.425, 24.475, 24.525, 24.575, 24.625, 24.675, 24.725, 24.775, 24.825, 24.875, 24.925, 24.975};

  Double_t y[500]={122.26, 123.891, 121.73, 113.018, 94.7812, 74.2528, 56.4373, 43.6046, 33.0555, 24.7851, 18.2085, 13.4214, 10.1599, 8.50494, 6.97288, 5.95731, 5.3044, 4.56881, 4.08133, 3.62264, 3.0748, 2.52723, 2.09044, 1.51133, 1.08445, 0.953321, 0.96978, 1.05937, 1.10607, 1.09935, 1.06797, 1.05868, 1.01432, 0.959666, 0.918407, 0.880808, 0.862903, 0.883741, 0.927755, 0.915434, 0.897603, 0.883844, 0.880678, 0.873951, 0.863199, 0.867875, 0.886082, 0.927245, 0.944489, 0.944603, 0.920077, 0.890674, 0.86644, 0.856585, 0.846303, 0.836249, 0.831749, 0.832317, 0.839134, 0.853728, 0.870639, 0.900509, 0.936295, 0.969995, 0.99261, 1.01212, 1.00425, 0.973689, 0.924023, 0.87567, 0.851811, 0.869442, 0.90757, 0.934197, 0.949153, 0.939613, 0.918611, 0.892788, 0.870253, 0.849932, 0.837782, 0.837393, 0.844409, 0.855282, 0.867326, 0.879517, 0.886308, 0.882179, 0.87118, 0.863178, 0.860305, 0.864048, 0.872365, 0.87777, 0.880575, 0.879944, 0.872232, 0.861245, 0.856784, 0.857578, 0.864207, 0.871989, 0.873983, 0.871032, 0.864216, 0.854782, 0.846514, 0.841122, 0.837365, 0.836136, 0.83674, 0.838612, 0.842553, 0.845786, 0.844994, 0.841337, 0.836408, 0.832799, 0.831051, 0.831704, 0.83532, 0.840957, 0.8472, 0.850486, 0.85059, 0.846024, 0.840675, 0.836938, 0.835556, 0.837036, 0.841583, 0.848079, 0.853387, 0.857042, 0.856045, 0.851609, 0.846614, 0.841647, 0.83806, 0.836503, 0.836388, 0.836952, 0.837918, 0.839444, 0.842086, 0.84493, 0.846086, 0.846443, 0.846346, 0.845664, 0.846235, 0.846887, 0.847389, 0.847055, 0.845937, 0.843667, 0.841524, 0.840752, 0.841477, 0.843441, 0.843977, 0.842925, 0.840745, 0.838502, 0.83617, 0.83467, 0.834672, 0.835874, 0.838049, 0.839877, 0.840188, 0.839282, 0.838061, 0.836805, 0.835857, 0.835085, 0.834056, 0.833095, 0.832626, 0.832797, 0.833877, 0.835269, 0.83647, 0.837323, 0.837279, 0.836284, 0.835116, 0.834009, 0.832841, 0.832132, 0.832014, 0.832433, 0.833091, 0.833519, 0.833615, 0.833611, 0.833412, 0.83306, 0.832623, 0.832176, 0.831849, 0.831751, 0.831714, 0.831582, 0.831601, 0.8317, 0.831827, 0.831944, 0.832038, 0.832233, 0.832487, 0.832786, 0.833111, 0.833715, 0.834363, 0.83497, 0.835368, 0.835387, 0.83548, 0.83535, 0.834873, 0.834214, 0.833442, 0.832668, 0.83243, 0.832789, 0.83342, 0.834132, 0.834533, 0.834463, 0.834284, 0.834043, 0.834046, 0.834166, 0.8342, 0.834282, 0.8344, 0.834451, 0.83424, 0.834183, 0.834335, 0.834832, 0.835363, 0.835493, 0.835194, 0.834699, 0.834397, 0.834212, 0.834205, 0.834077, 0.833838, 0.833567, 0.833276, 0.833109, 0.833172, 0.833314, 0.833382, 0.83332, 0.832941, 0.832386, 0.83198, 0.831683, 0.83155, 0.831643, 0.83181, 0.831956, 0.831982, 0.831868, 0.831649, 0.831422, 0.831172, 0.831022, 0.830996, 0.831073, 0.831262, 0.831464, 0.831635, 0.831749, 0.831764, 0.831626, 0.831396, 0.831174, 0.831078, 0.831144, 0.831281, 0.831401, 0.831493, 0.831547, 0.831513, 0.831452, 0.831407, 0.831524, 0.831861, 0.83225, 0.832576, 0.832767, 0.832737, 0.832531, 0.832393, 0.832286, 0.832283, 0.83241, 0.832547, 0.832645, 0.832676, 0.832599, 0.832454, 0.832264, 0.832044, 0.83192, 0.831889, 0.831837, 0.831815, 0.831852, 0.831924, 0.832037, 0.832061, 0.831961, 0.831752, 0.831562, 0.831423, 0.831427, 0.831566, 0.831741, 0.831908, 0.831959, 0.831902, 0.831772, 0.831709, 0.83169, 0.83172, 0.831762, 0.831759, 0.831817, 0.831934, 0.832033, 0.832089, 0.832121, 0.832078, 0.831994, 0.831905, 0.831822, 0.831825, 0.831881, 0.83194, 0.832012, 0.831974, 0.831811, 0.831585, 0.831367, 0.831202, 0.831168, 0.831208, 0.83123, 0.831223, 0.831154, 0.831072, 0.830995, 0.83094, 0.830919, 0.830951, 0.831018, 0.831076, 0.831113, 0.831109, 0.831078, 0.831031, 0.830973, 0.830926, 0.830915, 0.830937, 0.830995, 0.831077, 0.831141, 0.831189, 0.831208, 0.831182, 0.831132, 0.831089, 0.831067, 0.8311, 0.831158, 0.831225, 0.831313, 0.831366, 0.83136, 0.831339, 0.831312, 0.831285, 0.831296, 0.831318, 0.831334, 0.83135, 0.831356, 0.831347, 0.831367, 0.831406, 0.831451, 0.831468, 0.831435, 0.83136, 0.83129, 0.831266, 0.831271, 0.831293, 0.831284, 0.831252, 0.83121, 0.831175, 0.831138, 0.83113, 0.831154, 0.831168, 0.831177, 0.831147, 0.831091, 0.831039, 0.831006, 0.831005, 0.831036, 0.831059, 0.831069, 0.831085, 0.831095, 0.831112, 0.831143, 0.831144, 0.831112, 0.831056, 0.830987, 0.830945, 0.830932, 0.830941, 0.830961, 0.830976, 0.830975, 0.830959, 0.830942, 0.830925, 0.830917, 0.83091, 0.830918, 0.830945, 0.830978, 0.831014, 0.831042, 0.831053, 0.831035, 0.831012, 0.830978, 0.830952, 0.830958, 0.830993, 0.831049, 0.831108, 0.83114, 0.831144, 0.831134, 0.831092, 0.831042, 0.831012, 0.830992, 0.830989, 0.831005, 0.831018, 0.831027, 0.831027, 0.831016, 0.831008, 0.83101, 0.831006, 0.831004, 0.830996, 0.830978, 0.830962, 0.83095, 0.830946, 0.830945, 0.830942, 0.830927, 0.830915, 0.830907, 0.830905, 0.830915, 0.830939, 0.83096, 0.830965, 0.830957, 0.830929, 0.830897, 0.830876, 0.830872, 0.830888, 0.830913, 0.830926, 0.830925, 0.830912, 0.83089, 0.830874, 0.830867};

  Double_t y1[500]={139.325, 138.58, 128.852, 106.961, 82.4087, 61.7836, 46.2751, 34.3924, 25.161, 18.5232, 13.3847, 10.0938, 7.60229, 6.11173, 5.1132, 4.31782, 3.76158, 3.04978, 2.46712, 1.98182, 1.7169, 1.49868, 1.33888, 1.25719, 1.20771, 1.13213, 1.08143, 1.06699, 1.09741, 1.14498, 1.16173, 1.12673, 1.07345, 1.03877, 1.04035, 1.09357, 1.16247, 1.21263, 1.21444, 1.17654, 1.13922, 1.08274, 1.04328, 1.04735, 1.10323, 1.16304, 1.18666, 1.16387, 1.11496, 1.06606, 1.03205, 1.02867, 1.0689, 1.13441, 1.18299, 1.19701, 1.17073, 1.12279, 1.07542, 1.04317, 1.03126, 1.02994, 1.03215, 1.03748, 1.04114, 1.04333, 1.04285, 1.04488, 1.0462, 1.0476, 1.04823, 1.04641, 1.04234, 1.03863, 1.03831, 1.03962, 1.03841, 1.03267, 1.02896, 1.03212, 1.0445, 1.05903, 1.07285, 1.08386, 1.08836, 1.08468, 1.074, 1.06316, 1.05731, 1.05387, 1.05634, 1.06548, 1.07643, 1.08018, 1.07298, 1.06146, 1.05302, 1.0543, 1.06284, 1.07179, 1.07474, 1.07249, 1.06499, 1.05655, 1.04926, 1.04671, 1.04954, 1.05405, 1.05769, 1.05703, 1.05421, 1.05156, 1.04954, 1.04757, 1.04455, 1.04059, 1.03635, 1.03217, 1.03014, 1.03034, 1.03152, 1.03235, 1.0335, 1.03492, 1.03579, 1.03574, 1.03634, 1.03751, 1.03833, 1.03764, 1.03503, 1.03241, 1.03031, 1.02959, 1.02953, 1.0299, 1.03044, 1.03045, 1.02983, 1.02895, 1.02821, 1.02792, 1.02812, 1.02882, 1.02956, 1.02976, 1.02921, 1.02796, 1.02651, 1.02553, 1.02535, 1.02563, 1.02586, 1.02586, 1.02582, 1.02574, 1.02581, 1.0261, 1.02643, 1.02666, 1.02673, 1.02655, 1.02649, 1.02685, 1.02777, 1.02895, 1.02979, 1.02979, 1.02929, 1.02878, 1.02847, 1.02808, 1.0278, 1.02816, 1.02908, 1.02998, 1.03039, 1.03005, 1.02928, 1.02829, 1.02768, 1.02764, 1.02806, 1.0288, 1.02929, 1.02942, 1.02912, 1.029, 1.02917, 1.02958, 1.03011, 1.03081, 1.03132, 1.03144, 1.03097, 1.03012, 1.02915, 1.02819, 1.0275, 1.02726, 1.0276, 1.02818, 1.02844, 1.02837, 1.02816, 1.02799, 1.02786, 1.02786, 1.02809, 1.02824, 1.02835, 1.02839, 1.02842, 1.02828, 1.02793, 1.02753, 1.02726, 1.02717, 1.02724, 1.02742, 1.02771, 1.02812, 1.02837, 1.02825, 1.02769, 1.02703, 1.02665, 1.02663, 1.02682, 1.02695, 1.02691, 1.02682, 1.02669, 1.02656, 1.02636, 1.02617, 1.02603, 1.02587, 1.02571, 1.02561, 1.02557, 1.02552, 1.02549, 1.02551, 1.02554, 1.02553, 1.0255, 1.0255, 1.02556, 1.02562, 1.02564, 1.02561, 1.02551, 1.02541, 1.02534, 1.02531, 1.02534, 1.02539, 1.02545, 1.02549, 1.02552, 1.0255, 1.02547, 1.02547, 1.02548, 1.02549, 1.02547, 1.02543, 1.02541, 1.02547, 1.02558, 1.0257, 1.02578, 1.02583, 1.02579, 1.02569, 1.02561, 1.02566, 1.0258, 1.02591, 1.02591, 1.02584, 1.02581, 1.02588, 1.02604, 1.02626, 1.02645, 1.02654, 1.02648, 1.02634, 1.02619, 1.02607, 1.02603, 1.02613, 1.02633, 1.02649, 1.02651, 1.02638, 1.02622, 1.02607, 1.02603, 1.02608, 1.02618, 1.02628, 1.02631, 1.02627, 1.02614, 1.02599, 1.02592, 1.02596, 1.02611, 1.0263, 1.02641, 1.0264, 1.02629, 1.02616, 1.02609, 1.02605, 1.02597, 1.02586, 1.0258, 1.02585, 1.02592, 1.02595, 1.02593, 1.02593, 1.02596, 1.02603, 1.02615, 1.02627, 1.02634, 1.02631, 1.02621, 1.02605, 1.0259, 1.02581, 1.02583, 1.02593, 1.02603, 1.02607, 1.02601, 1.02591, 1.02581, 1.02575, 1.02573, 1.02576, 1.02583, 1.02587, 1.02588, 1.02583, 1.02576, 1.0257, 1.02567, 1.02567, 1.02567, 1.0257, 1.02571, 1.02568, 1.02561, 1.02554, 1.02548, 1.02545, 1.02544, 1.02544, 1.02544, 1.02542, 1.0254, 1.0254, 1.02542, 1.02542, 1.02541, 1.02538, 1.02537, 1.02537, 1.02538, 1.02539, 1.02541, 1.02543, 1.02545, 1.02547, 1.02547, 1.02545, 1.02543, 1.02543, 1.02544, 1.02546, 1.02546, 1.02545, 1.02542, 1.0254, 1.02538, 1.02536, 1.02535, 1.02538, 1.02542, 1.02545, 1.02545, 1.02544, 1.02543, 1.02544, 1.02546, 1.02547, 1.02547, 1.02548, 1.02548, 1.02551, 1.02555, 1.0256, 1.02563, 1.02564, 1.02565, 1.02566, 1.02567, 1.02566, 1.02566, 1.02567, 1.02569, 1.02569, 1.02568, 1.02565, 1.02563, 1.02563, 1.02565, 1.02571, 1.02577, 1.02581, 1.02581, 1.02577, 1.02572, 1.02569, 1.0257, 1.02574, 1.02578, 1.02579, 1.02578, 1.02575, 1.02572, 1.0257, 1.02568, 1.02567, 1.02565, 1.02565, 1.02563, 1.0256, 1.02558, 1.0256, 1.02564, 1.02567, 1.02568, 1.02569, 1.02571, 1.02572, 1.02572, 1.02569, 1.02564, 1.02561, 1.02559, 1.02561, 1.02564, 1.02564, 1.02562, 1.02558, 1.02556, 1.02554, 1.02554, 1.02553, 1.02555, 1.02556, 1.02558, 1.02558, 1.02554, 1.02549, 1.02544, 1.02543, 1.02543, 1.02546, 1.02548, 1.0255, 1.02549, 1.02548, 1.02545, 1.02542, 1.0254, 1.02541, 1.02542, 1.02543, 1.02542, 1.02539, 1.02536, 1.02535, 1.02535, 1.02536, 1.02537, 1.02537, 1.02536, 1.02535, 1.02535, 1.02535, 1.02535, 1.02535};
  Double_t y2[500]={163.697, 152.836, 120.517, 86.1412, 62.0014, 44.5427, 32.0942, 23.2423, 16.8232, 12.5316, 9.34649, 7.08991, 5.67814, 4.50093, 3.16493, 2.71437, 2.29682, 1.90559, 1.60505, 1.41393, 1.32769, 1.36078, 1.37828, 1.35524, 1.34928, 1.34765, 1.3407, 1.36717, 1.44785, 1.4609, 1.39651, 1.38914, 1.3976, 1.36742, 1.33226, 1.33506, 1.35931, 1.37235, 1.36247, 1.34011, 1.32587, 1.33574, 1.3496, 1.36372, 1.37664, 1.37241, 1.36826, 1.37184, 1.37219, 1.36054, 1.34553, 1.3431, 1.35711, 1.3923, 1.44153, 1.46918, 1.46492, 1.43381, 1.39837, 1.36815, 1.34961, 1.34884, 1.36435, 1.38946, 1.40122, 1.39697, 1.38542, 1.37629, 1.36341, 1.35091, 1.3369, 1.32867, 1.3282, 1.32926, 1.33065, 1.33091, 1.3286, 1.32681, 1.32685, 1.3276, 1.32869, 1.33093, 1.33277, 1.33165, 1.33123, 1.33071, 1.32937, 1.32736, 1.32656, 1.32692, 1.32788, 1.32871, 1.32884, 1.3282, 1.32766, 1.32766, 1.3274, 1.32731, 1.32858, 1.33144, 1.33413, 1.33547, 1.33724, 1.33916, 1.34006, 1.33924, 1.33663, 1.33321, 1.33, 1.32788, 1.32798, 1.32901, 1.32919, 1.32943, 1.32905, 1.32832, 1.32756, 1.32713, 1.32682, 1.32669, 1.32652, 1.32631, 1.32605, 1.32614, 1.32685, 1.32743, 1.32753, 1.32775, 1.32803, 1.32802, 1.32759, 1.32732, 1.32708, 1.32714, 1.32751, 1.32788, 1.32814, 1.32831, 1.32832, 1.32813, 1.32798, 1.32805, 1.32836, 1.32833, 1.32808, 1.3275, 1.32689, 1.32669, 1.32673, 1.32683, 1.32688, 1.32681, 1.32671, 1.32639, 1.32626, 1.3265, 1.32658, 1.32633, 1.32624, 1.32651, 1.32685, 1.32723, 1.32744, 1.32742, 1.32717, 1.32702, 1.32688, 1.3269, 1.32707, 1.3272, 1.32715, 1.32694, 1.32668, 1.32642, 1.32631, 1.32641, 1.32647, 1.32654, 1.32666, 1.32675, 1.32672, 1.32656, 1.3264, 1.32632, 1.32625, 1.32621, 1.32633, 1.32649, 1.32665, 1.32662, 1.32646, 1.32629, 1.32619, 1.32611, 1.32604, 1.32592, 1.32586, 1.32588, 1.32594, 1.32598, 1.326, 1.32594, 1.32586, 1.32584, 1.32585, 1.32589, 1.32595, 1.32598, 1.32594, 1.32589, 1.32588, 1.32588, 1.32587, 1.32588, 1.32592, 1.32597, 1.32602, 1.32606, 1.3261, 1.32618, 1.32623, 1.32621, 1.32614, 1.32607, 1.32608, 1.3262, 1.32633, 1.32651, 1.32671, 1.32688, 1.32694, 1.32691, 1.32678, 1.32658, 1.32643, 1.32648, 1.32663, 1.32671, 1.32679, 1.3268, 1.32671, 1.32653, 1.32637, 1.32622, 1.32609, 1.32601, 1.32595, 1.32595, 1.32599, 1.32597, 1.32591, 1.32586, 1.32584, 1.32584, 1.32589, 1.32596, 1.326, 1.326, 1.32598, 1.32597, 1.32599, 1.32605, 1.32612, 1.32616, 1.32614, 1.32613, 1.32615, 1.32615, 1.32611, 1.32605, 1.32598, 1.32593, 1.32591, 1.32592, 1.32596, 1.32601, 1.32604, 1.32602, 1.32598, 1.32596, 1.32595, 1.32592, 1.32588, 1.32588, 1.32591, 1.32593, 1.32597, 1.32599, 1.32599, 1.32596, 1.32594, 1.3259, 1.32589, 1.32588, 1.32589, 1.32589, 1.32589, 1.32587, 1.32586, 1.32588, 1.3259, 1.3259, 1.32589, 1.32588, 1.32587, 1.32587, 1.32586, 1.32585, 1.32585, 1.32584, 1.32584, 1.32586, 1.32589, 1.3259, 1.32591, 1.3259, 1.32589, 1.32589, 1.32589, 1.32589, 1.32589, 1.32591, 1.32594, 1.32596, 1.32596, 1.32597, 1.32596, 1.32595, 1.32594, 1.32593, 1.3259, 1.32591, 1.32593, 1.32594, 1.32593, 1.32593, 1.32593, 1.32591, 1.3259, 1.32589, 1.3259, 1.3259, 1.32591, 1.32592, 1.32593, 1.32591, 1.32588, 1.32586, 1.32586, 1.32588, 1.32589, 1.32589, 1.32588, 1.32588, 1.32588, 1.32588, 1.32588, 1.32587, 1.32586, 1.32588, 1.3259, 1.32593, 1.32595, 1.32596, 1.32596, 1.32593, 1.32589, 1.32587, 1.32586, 1.32587, 1.32588, 1.32588, 1.32589, 1.32588, 1.32586, 1.32585, 1.32584, 1.32584, 1.32583, 1.32584, 1.32585, 1.32586, 1.32586, 1.32586, 1.32585, 1.32584, 1.32583, 1.32584, 1.32584, 1.32584, 1.32585, 1.32586, 1.32588, 1.32588, 1.32587, 1.32586, 1.32585, 1.32584, 1.32584, 1.32585, 1.32587, 1.32588, 1.32589, 1.32588, 1.32587, 1.32585, 1.32584, 1.32583, 1.32584, 1.32584, 1.32584, 1.32584, 1.32584, 1.32585, 1.32585, 1.32585, 1.32584, 1.32584, 1.32584, 1.32584, 1.32585, 1.32586, 1.32585, 1.32584, 1.32584, 1.32584, 1.32585, 1.32585, 1.32585, 1.32586, 1.32586, 1.32586, 1.32586, 1.32585, 1.32584, 1.32584, 1.32585, 1.32586, 1.32586, 1.32586, 1.32586, 1.32585, 1.32585, 1.32585, 1.32584, 1.32584, 1.32584, 1.32584, 1.32584, 1.32584, 1.32584, 1.32584, 1.32583, 1.32583, 1.32583, 1.32583, 1.32583, 1.32583, 1.32583, 1.32583, 1.32583, 1.32583, 1.32583, 1.32583, 1.32583, 1.32583, 1.32583, 1.32584, 1.32584, 1.32583, 1.32583, 1.32583, 1.32584, 1.32584, 1.32584, 1.32584, 1.32584, 1.32584, 1.32583, 1.32583, 1.32583, 1.32583, 1.32583, 1.32583, 1.32583, 1.32583, 1.32583, 1.32584, 1.32585, 1.32586, 1.32587, 1.32586, 1.32585, 1.32585, 1.32584, 1.32585, 1.32587, 1.32588, 1.32589, 1.32588};
  

  
  
  TGraph *g_noise;
  if (capacitance == 4){
    g_noise = new TGraph(500,x,y);
  }else if(capacitance == 6){
    g_noise = new TGraph(500,x,y1);
  }else if(capacitance == 10){
    g_noise = new TGraph(500,x,y2);
  }else{
    g_noise = new TGraph(500,x,y);
  }
  
  //  TGraph *g_noise = new TGraph(500,x,y);
  TH1F *h_nois = new TH1F("h_nois","h_nois",1024,0,512);
  TH1F *h_decon = new TH1F("h_decon","h_decon",5120,0,512);
  //TH1F *h_decon = new TH1F("h_decon","h_decon",1024,0,512);
  //  TH1F *h_nois = new TH1F("h_nois","h_nois",1024,0,512);


  //std::cout << h_nois->GetNbinsX() << std::endl;

  if (flag_noise==1)
    // calculate noise 
    Calculate_Electronic_Noise(h_nois, g_noise);

  // calculate RMS of noise
  // TH1F *h2 = new TH1F("h2","h2",100,-6,6);
  // for (Int_t i=0;i!=h_nois->GetNbinsX();i++){
  //   h2->Fill(h_nois->GetBinContent(i+1));
  // }

  TF1 *filter_gauss = new TF1("gauss","exp(-[0]*x*x)",0,5);
  filter_gauss->SetParameter(0,4.);
  //filter_gauss->SetParameter(0,0.01);
  TF1 *filter_wiener = new TF1("wiener","exp(-[0]*pow(x,[1]))",0,5);
  filter_wiener->SetParameter(0,1588.);
  filter_wiener->SetParameter(1,11.80);

  
  
  
  // simulate induced current ...
  TH1F *h_tot = new TH1F("h_tot","h_tot",8000,0,8.);
  TH1F *he = (TH1F*)h_tot->Clone("he");
  TH1F *hh = (TH1F*)h_tot->Clone("hh");
  TH1F *hge = (TH1F*)h_tot->Clone("hge");
  TH1F *hgh = (TH1F*)h_tot->Clone("hgh");
  
  cal_track(0,x1,1,gain,h_tot,he, hh, hge, hgh, flag_fluct,120);


  TH1F *h_tot2 = new TH1F("h_tot2","h_tot2",8000,0,8.);
  TH1F *he2 = (TH1F*)h_tot2->Clone("he2");
  TH1F *hh2 = (TH1F*)h_tot2->Clone("hh2");
  TH1F *hge2 = (TH1F*)h_tot2->Clone("hge2");
  TH1F *hgh2 = (TH1F*)h_tot2->Clone("hgh2");
  
  cal_track(x1,120,1,gain,h_tot2,he2, hh2, hge2, hgh2, flag_fluct,120,x2);
  h_tot->Add(h_tot2, scale_2nd);
  // he->Add(he2);
  // hh->Add(hh2);
  // hge->Add(hge2);
  // hgh->Add(hgh2);
  
  // convolute with electronics response ...

  //Double_t ele_x[50]={-0.0702028, 0, 0.210608, 0.304212, 0.366615, 0.49142, 0.522621, 0.616225, 0.678627, 0.74103, 0.772231, 0.865835, 0.928237, 0.99064, 1.05304, 1.11544, 1.17785, 1.33385, 1.45866, 1.73947, 1.83307, 1.92668, 2.05148, 2.17629, 2.23869, 2.36349, 2.4883, 2.5819, 2.73791, 2.86271, 3.01872, 3.20593, 3.45554, 3.76755, 4.01716, 4.36037, 4.85959, 5.26521, 5.67083, 6.20125, 6.66927, 7.29329, 7.79251, 8.51014, 9.25897, 10.3198, 11.2871, 11.7863, 12, 13};
  //Double_t ele_y[50]={0, 0, -0.486902, -2.30353, -4.6156, -7.42312, -11.3867, -14.9374, -18.4055, -22.0387, -25.3417, -31.7825, -35.4983, -38.3058, -40.205, -42.3519, -44.2511, -45.1594, -45.5723, -42.1042, -39.7921, -37.1498, -33.7642, -30.4613, -27.5712, -23.3599, -19.8918, -16.0934, -12.7904, -10.2306, -7.67084, -4.20273, -1.64294, 0.17369, 1.4123, 2.23804, 2.40319, 1.82517, 1.16458, 0.503986, 0.17369, -0.156606, 0.00854214, 0.00854214, 0.00854214, 0.0911162, 0.17369, 0.0911162, 0, 0};
  // TGraph *g_ele = new TGraph(50, ele_x, ele_y);


  Double_t ele_x[252]={-0.025,0,0.025,0.075,0.125,0.175,0.225,0.275,0.325,0.375,0.425,0.475,0.525,0.575,0.625,0.675,0.725,0.775,0.825,0.875,0.925,0.975,1.025,1.075,1.125,1.175,1.225,1.275,1.325,1.375,1.425,1.475,1.525,1.575,1.625,1.675,1.725,1.775,1.825,1.875,1.925,1.975,2.025,2.075,2.125,2.175,2.225,2.275,2.325,2.375,2.425,2.475,2.525,2.575,2.625,2.675,2.725,2.775,2.825,2.875,2.925,2.975,3.025,3.075,3.125,3.175,3.225,3.275,3.325,3.375,3.425,3.475,3.525,3.575,3.625,3.675,3.725,3.775,3.825,3.875,3.925,3.975,4.025,4.075,4.125,4.175,4.225,4.275,4.325,4.375,4.425,4.475,4.525,4.575,4.625,4.675,4.725,4.775,4.825,4.875,4.925,4.975,5.025,5.075,5.125,5.175,5.225,5.275,5.325,5.375,5.425,5.475,5.525,5.575,5.625,5.675,5.725,5.775,5.825,5.875,5.925,5.975,6.025,6.075,6.125,6.175,6.225,6.275,6.325,6.375,6.425,6.475,6.525,6.575,6.625,6.675,6.725,6.775,6.825,6.875,6.925,6.975,7.025,7.075,7.125,7.175,7.225,7.275,7.325,7.375,7.425,7.475,7.525,7.575,7.625,7.675,7.725,7.775,7.825,7.875,7.925,7.975,8.025,8.075,8.125,8.175,8.225,8.275,8.325,8.375,8.425,8.475,8.525,8.575,8.625,8.675,8.725,8.775,8.825,8.875,8.925,8.975,9.025,9.075,9.125,9.175,9.225,9.275,9.325,9.375,9.425,9.475,9.525,9.575,9.625,9.675,9.725,9.775,9.825,9.875,9.925,9.975,10.025,10.075,10.125,10.175,10.225,10.275,10.325,10.375,10.425,10.475,10.525,10.575,10.625,10.675,10.725,10.775,10.825,10.875,10.925,10.975,11.025,11.075,11.125,11.175,11.225,11.275,11.325,11.375,11.425,11.475,11.525,11.575,11.625,11.675,11.725,11.775,11.825,11.875,11.925,11.975,12.025,12.075,12.125,12.175,12.225,12.275,12.325,12.375,12.425,12.475};
  Double_t ele_y[252]={0,0,-0.0574223,-0.173766,-0.288611,-0.404955,-0.765841,-1.73697,-3.07336,-4.8046,-5.92861,-7.05412,-11.4766,-13.374,-15.4247,-18.2043,-21.105,-25.5326,-28.9723,-32.3286,-35.3052,-37.6025,-39.3512,-40.9609,-42.6424,-44.1647,-44.5253,-44.8171,-45.1075,-45.2959,-45.4606,-45.3709,-44.7526,-44.1358,-43.5176,-42.9008,-42.2825,-41.2269,-39.9911,-38.6089,-37.1968,-35.8393,-34.4822,-33.1422,-31.8182,-30.4958,-28.2049,-26.3463,-24.6583,-23.0404,-21.6503,-20.2617,-18.4021,-16.3738,-15.1805,-14.1227,-13.0634,-12.03,-11.0037,-10.0293,-9.20819,-8.38856,-7.55413,-6.62861,-5.7016,-4.77609,-4.00679,-3.49478,-2.98127,-2.46927,-1.95576,-1.53001,-1.23815,-0.947777,-0.65591,-0.365543,-0.0736759,0.210283,0.459142,0.706501,0.95536,1.20272,1.43154,1.55108,1.67213,1.79168,1.91272,2.03227,2.15332,2.2425,2.2598,2.27559,2.29288,2.30867,2.32596,2.34175,2.35904,2.37483,2.39212,2.38086,2.31035,2.23835,2.16785,2.09585,2.02535,1.95335,1.88285,1.80885,1.72817,1.64599,1.56531,1.48313,1.40245,1.32027,1.23959,1.15901,1.09749,1.03447,0.972949,0.909928,0.848407,0.785387,0.723866,0.660845,0.599324,0.536303,0.4876,0.451563,0.417027,0.38099,0.346454,0.310417,0.275881,0.239844,0.205308,0.170282,0.144567,0.117352,0.0916365,0.0644215,0.0387061,0.0114911,-0.0142243,-0.0414392,-0.0671546,-0.0943696,-0.120085,-0.1473,-0.145741,-0.12995,-0.11266,-0.096869,-0.0795786,-0.0637877,-0.0464973,-0.0307065,-0.0134161,0.00237472,0.00891704,0.00816724,0.00891704,0.00816724,0.00891704,0.00816724,0.00891704,0.00816724,0.00891704,0.00816724,0.00891704,0.00816724,0.00891704,0.00816724,0.00891704,0.00816724,0.00891704,0.00816724,0.00891704,0.00816724,0.00891704,0.00816724,0.00891704,0.00816724,0.00891704,0.00816724,0.00891704,0.00816724,0.00891704,0.009415,0.0140568,0.0171989,0.0218407,0.0249828,0.0296246,0.0327667,0.0374085,0.0405506,0.0451924,0.0483346,0.0529763,0.0561185,0.0607602,0.0639024,0.0685441,0.0716863,0.076328,0.0794702,0.0841119,0.0872541,0.091935,0.0954535,0.100472,0.10399,0.109008,0.112527,0.117545,0.121063,0.126081,0.1296,0.134618,0.138136,0.143154,0.146673,0.151691,0.155209,0.160227,0.163746,0.168764,0.172282,0.167796,0.158775,0.151255,0.142234,0.134713,0.125693,0.118172,0.109152,0.101631,0.0926105,0.0749904,0.0529219,0.032353,0.0102845,0,-0,0,-0,0,-0,0,-0,0,-0};
  // TGraph *g_ele = new TGraph(252,ele_x,ele_y);

  Double_t ele_y1[252]={0, 0,-0.0695965,-0.195681,-0.334874,-0.460959,-0.73444,-1.2916,-1.99876,-3.16339,-4.23105,-7.18579,-8.57073,-9.45948,-10.3614,-13.4504,-15.4706,-17.321,-19.6054,-21.8379,-24.033,-25.6818,-27.0661,-28.5186,-29.7811,-30.8356,-31.7515,-32.4413,-33.0566,-33.4745,-33.9055,-34.0378,-34.0633,-34.0757,-34.0838,-33.6528,-33.2349,-32.8151,-32.4238,-32.0193,-31.6279,-30.7468,-29.7254,-28.7919,-27.9231,-27.0387,-26.1168,-25.1818,-24.2174,-23.1829,-22.1946,-21.2596,-20.3819,-19.6326,-18.8963,-17.8946,-16.7429,-15.4099,-14.357,-13.5811,-12.8183,-12.2808,-11.7946,-11.2954,-10.7498,-9.94742,-9.18522,-8.64811,-8.12411,-7.587,-7.08785,-6.60759,-6.14043,-5.66017,-5.28995,-4.93522,-4.5936,-4.23887,-3.91983,-3.60378,-3.30085,-2.9848,-2.68186,-2.42749,-2.19529,-1.94999,-1.71779,-1.47249,-1.30176,-1.1531,-1.01754,-0.868871,-0.733312,-0.584645,-0.449086,-0.315269,-0.228196,-0.128014,-0.0409406,0.059241,0.146314,0.246496,0.333569,0.433751,0.496997,0.538456,0.566807,0.608266,0.636617,0.678076,0.706427,0.747886,0.776237,0.817696,0.830056,0.83661,0.830056,0.83661,0.830056,0.83661,0.830056,0.83661,0.830056,0.83661,0.830056,0.83661,0.830056,0.83661,0.814034,0.80164,0.776138,0.763743,0.738241,0.725847,0.700344,0.68795,0.662447,0.650053,0.62455,0.614599,0.591967,0.582444,0.559812,0.550289,0.527657,0.518134,0.495503,0.485979,0.463348,0.453824,0.431193,0.421669,0.399038,0.389514,0.366883,0.35736,0.336079,0.328912,0.308636,0.301469,0.281194,0.274027,0.253751,0.246584,0.226309,0.219142,0.198866,0.191699,0.171424,0.164257,0.143981,0.142166,0.135612,0.142166,0.135612,0.142166,0.135612,0.142166,0.135612,0.142166,0.135612,0.142166,0.135612,0.142166,0.135612,0.142166,0.135612,0.142166,0.129362,0.126091,0.109712,0.106441,0.0900615,0.0867904,0.0704113,0.0671402,0.0507611,0.04749,0.0311108,0.0278398,0.0114606,0.00818958,-0.0,0.0,-0.0,0.0,-0.0,0.0,-0.0,0.0,-0.0,0.0,-0.0,0.0,-0.0,0.0,-0.0,0.0,-0.0,0.0,-0.0,0.0,-0.0,0.0,-0.0,0.0,-0.0,0.0,-0.0,0.0,-0.0,0.0,-0.0,0.0,-0.0,0.0,-0.0,0.0,-0.0,0.0,-0.0,0.0,-0.0,0.0,-0.0,0.0,-0.0,0.0,-0.0,0.0,-0.0,0.0};
  Double_t ele_y2[252]={0,0,-0.0186936,-0.0600101,-0.0973972,-0.138714,-0.487795,-0.850251,-1.20878,-1.72046,-2.55964,-3.50127,-4.52311,-5.71062,-6.37272,-7.0459,-7.90722,-8.77247,-10.7672,-11.9975,-13.058,-14.1582,-15.205,-16.0702,-17.0097,-18.3635,-19.3355,-20.0285,-20.4692,-20.9139,-21.3109,-21.6449,-21.9749,-22.2346,-22.2769,-22.3232,-22.3655,-22.4117,-22.3287,-22.1481,-21.9635,-21.7828,-21.5536,-21.252,-20.9464,-20.6448,-20.3309,-20.0174,-19.7,-19.3866,-18.9556,-18.4263,-17.9637,-17.5967,-17.2258,-16.8589,-16.488,-15.9059,-15.2399,-14.6169,-14.2924,-13.9718,-13.6473,-13.2922,-12.8918,-12.4953,-12.107,-11.7484,-11.386,-11.0275,-10.6401,-10.2436,-9.8432,-9.44673,-9.16216,-8.8819,-8.5977,-8.31744,-8.00044,-7.67986,-7.35535,-7.05372,-6.85253,-6.65528,-6.4541,-6.25684,-6.05566,-5.84612,-5.63166,-5.42112,-5.20666,-4.99612,-4.81731,-4.65801,-4.49477,-4.33546,-4.17223,-4.01292,-3.84968,-3.69109,-3.52975,-3.37234,-3.211,-3.05359,-2.90216,-2.81218,-2.71827,-2.62829,-2.53437,-2.44439,-2.35048,-2.25782,-2.15624,-2.0586,-1.95702,-1.85938,-1.75781,-1.66354,-1.60689,-1.55416,-1.49751,-1.44479,-1.38814,-1.33541,-1.27876,-1.22604,-1.16625,-1.0967,-1.02322,-0.953673,-0.880194,-0.810644,-0.737165,-0.681835,-0.644919,-0.611933,-0.575018,-0.542032,-0.505117,-0.472131,-0.435216,-0.40223,-0.365314,-0.341107,-0.323517,-0.309857,-0.292267,-0.278607,-0.261017,-0.247357,-0.229767,-0.216107,-0.194836,-0.174666,-0.150566,-0.130395,-0.106295,-0.0861242,-0.062024,-0.0418534,-0.0177532,0.000960383,0.0155739,0.026258,0.0408716,0.0515556,0.0661692,0.0768532,0.0914668,0.102151,0.116764,0.127448,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.139871,0.137907,0.132732,0.122268,0.115732,0.105268,0.0987323,0.0882676,0.0817323,0.0712676,0.0647323,0.0542676,0.0477323,0.0372676,0.0307324,0.0202676,0.0137324,0.00326762,0.0,-0.0,0.0,-0.0,0.0,-0.0,0.0,-0.0,0.0,-0.0};



  TGraph *g_ele;

  if (capacitance == 4){
    g_ele = new TGraph(252,ele_x,ele_y);
  }else if (capacitance == 6){
    g_ele = new TGraph(252,ele_x,ele_y1);
  }else if (capacitance == 10){
    g_ele = new TGraph(252,ele_x,ele_y2);
  }else{
    g_ele = new TGraph(252,ele_x,ele_y);

  }

  

  TGraph *g_signal = new TGraph();
  for (Int_t i=0;i!=h_tot->GetNbinsX();i++){
    g_signal->SetPoint(i,h_tot->GetBinCenter(i+1),h_tot->GetBinContent(i+1));
  }

  TH1F *hele = new TH1F("hele","hele",1000,0,20);
  TH1F *hsig = new TH1F("hsig","hsig",1000,0,20);
  for (Int_t i=0;i!=hele->GetNbinsX();i++){
    if (hsig->GetBinCenter(i+1) >= t0)
      hsig->SetBinContent(i+1,g_signal->Eval(hsig->GetBinCenter(i+1)-t0) * 1e6 * hsig->GetBinWidth(i+1)*norm);
    hele->SetBinContent(i+1,g_ele->Eval(hele->GetBinCenter(i+1)));
  }
  TH1 *hele_r = hele->FFT(0,"MAG");
  TH1 *hele_p = hele->FFT(0,"PH");

  TH1 *hsig_r = hsig->FFT(0,"MAG");
  TH1 *hsig_p = hsig->FFT(0,"PH");

  TGraph *g_signal_conv = new TGraph();
  {
    const Int_t nbin = hele->GetNbinsX();
    double value_re[nbin];
    double value_im[nbin];
    for (Int_t i=0;i!=nbin;i++){
      double freq = 2./nbin*i;
      if (i>nbin/2.) freq = 2./nbin * (nbin-i);

      // std::cout << freq << std::endl;
      //    double phi = gRandom->Uniform(-3.1415926,3.1415926);
      //double r = gRandom->Gaus(0,g2->Eval(freq)
      //value_re[i] = 62.6*sqrt(2.)*cos(phi)/nbin;
      //value_im[i] = 62.6*sqrt(2.)*sin(phi)/nbin;

      value_re[i] = hele_r->GetBinContent(i+1) * hsig_r->GetBinContent(i+1) * cos(hele_p->GetBinContent(i+1) + hsig_p->GetBinContent(i+1))/nbin;
      value_im[i] = hele_r->GetBinContent(i+1) * hsig_r->GetBinContent(i+1) * sin(hele_p->GetBinContent(i+1) + hsig_p->GetBinContent(i+1))/nbin;
  }
    Int_t n = nbin;
    TVirtualFFT *ifft = TVirtualFFT::FFT(1,&n,"C2R M K");
    ifft->SetPointsComplex(value_re,value_im);
    ifft->Transform();
    TH1 *fb = TH1::TransformHisto(ifft,0,"Re");
    //fb->Draw();
    for (Int_t i=0;i!=fb->GetNbinsX();i++){
      g_signal_conv->SetPoint(i,hele->GetBinCenter(i+1), fb->GetBinContent(i+1) );
    }
    delete ifft;
    delete fb;
  }

  delete hele_r;
  delete hele_p;
  delete hsig_r;
  delete hsig_p;


  double sum[85];
  
  
  // add to the noise ...
  for (Int_t i=0;i!=h_nois->GetNbinsX();i++){
    Double_t t = h_nois->GetBinCenter(i+1);
    // Double_t content =  g_signal_conv->Eval(t-t0);
    // if (t-t0 <0) content= 0;
    Double_t content = g_signal_conv->Eval(t) ;
    if (t > 20) content = 0;
    h_nois->SetBinContent(i+1, h_nois->GetBinContent(i+1) + content);
  }

  decon_wf(h_nois,g_ele,filter_gauss,h_decon);

  for (Int_t i=0;i!=85;i++){
    sum[i] = 0;
    for (Int_t j=0;j!=60;j++){
      sum[i] += h_decon->GetBinContent(i*60+j+1);
    }
    //sum[i] -= 100*(h_decon->GetBinContent(i*100+1) + h_decon->GetBinContent(i*100+99+1))/2.;
    
    sum[i] *= 6241.;
  }
  

  TH1F *h_sig_true = new TH1F("h_sig_true","h_sig_true",250,0,25); // 100 ps
  TGraph *gtemp = new TGraph();
  for (Int_t i=0;i!=200;i++){
    //gtemp->SetPoint(i,h_sig_true->GetBinCenter(i+1)+t0,hsig->GetBinContent(2*i+1) + hsig->GetBinContent(2*i+2));
    h_sig_true->SetBinContent(i+1, (hsig->GetBinContent(5*i+1) + hsig->GetBinContent(5*i+2) + hsig->GetBinContent(5*i+3) + hsig->GetBinContent(5*i+4) + hsig->GetBinContent(5*i+5)) );
    //h_sig_true->SetBinContent(i+1, hsig->GetBinContent(i+1)  );
  }
  // for (Int_t i=0;i!=200;i++){
  //  if (h_sig_true->GetBinCenter(i+1) >= t0)
  //    h_sig_true->SetBinContent(i+1,gtemp->Eval(h_sig_true->GetBinCenter(i+1)));
  // }
  
    
  // L1 fitting ...
  TH1F *h_sig = new TH1F("h_sig","h_sig",nbin,0,25); // 100 ps

  l1_fit(h_nois, g_ele, h_sig, (gain + 1), h_sig_true);
  //l1_fit(h_nois, g_signal_conv, h_sig, gain + 1);

  //std::cout << h_sig->GetSum() << std::endl;
  
  //  double reco_t0 = detect_t0(h_sig,480/6241./5.*3. *(gain+1) );
  double reco_t0;
  
  TFile *file = new TFile(Form("./out_files/output_%d.root",seed),"RECREATE");
  //TFile *file = new TFile(Form("./output.root",seed),"RECREATE");
  h_nois->SetDirectory(file);
  h_tot->SetDirectory(file);
  h_sig->SetDirectory(file);
  h_sig_true->SetDirectory(file);
  
  he->SetDirectory(file);
  hh->SetDirectory(file);
  hge->SetDirectory(file);
  hgh->SetDirectory(file);

  h_decon->SetDirectory(file);
  
  g_ele->Write("g_ele");
  g_signal_conv->Write("g_signal");
  g_noise->Write("g_noise");

  TTree *T = new TTree("T","T");
  T->SetDirectory(file);
  T->Branch("flag_noise",&flag_noise,"flag_noise/I");
  T->Branch("flag_fluct",&flag_fluct,"flag_fluct/I");
  T->Branch("gain",&gain,"gain/D");
  T->Branch("t0",&t0,"t0/D");
  T->Branch("reco_t0",&reco_t0,"reco_t0/D");
  T->Branch("seed",&seed,"seed/I");
  T->Branch("norm",&norm,"norm/D");
  T->Branch("nbin",&nbin,"nbin/I");
  T->Branch("noise",sum,"noise[85]/D");
  T->Fill();
  
  //h2->SetDirectory(file);
  file->Write();
  file->Close();
  
  return 0;
}
