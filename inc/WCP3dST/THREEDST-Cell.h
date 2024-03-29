#ifndef THREEDSTCELL_h
#define THREEDSTCELL_h

#include <vector>

namespace WCP3DST {
  class THREEDSTCell {
  public:
    THREEDSTCell(int index);
    ~THREEDSTCell();
    int get_index(){return index;};
  private:
    int index;
  };
}

#endif 
