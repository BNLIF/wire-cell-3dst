#include <iostream>
#include "WireCell3dST/THREEDST-Cell.h"
using namespace WireCell3DST;
using namespace std;




int main(int argc, char* argv[])
{
  THREEDSTCell cell1(1);
  cout << cell1.get_index() << endl;
  
  return 0;
}
