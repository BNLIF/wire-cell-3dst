#include <iostream>
#include "WCP3dST/THREEDST-Cell.h"
using namespace WCP3DST;
using namespace std;




int main(int argc, char* argv[])
{
  THREEDSTCell cell1(1);
  cout << cell1.get_index() << endl;
  cout<<"hello world"<<endl;
  
  return 0;
}
