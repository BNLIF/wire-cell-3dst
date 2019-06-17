#ifndef GEOMWIRE_3DST_h
#define GEOMWIRE_3DST_h

#include <vector>
#include <set>

namespace WireCell3DST {

  struct Coordinates{int x; int y; int z;};

  struct DataMeasureStructure{
	double t_begin; 
	double t_end;
	std::vector<int> charges;
  };

  class GeomWire{
  /*
   * the wire geometry is defined as below:
   * wire(x, y, z):
   * e.g if a wire in along the x axis, then take x as 0 and y, z will be the coordinate of the point that the wire projecits to the yz plane. But please remember that the origin point of the coordinate in yz plane is (1,1) becuase 0 is used to represent the case when the wire the in parallel with one of the axis. 
   * Similarly, if a wire is wire (1,0,1), it means that it is along y axis and in the xz plane, it's (1,1)
   * _ix, _iy,_iz in this class represent the x, y, z in wire(x, y, z)
   *
   */


  public:
//    GeomWire(int index=-1);
    GeomWire(int ichannel, int ix=-1, int iy=-1, int iz=-1);
//    GeomWire(int index=-1, int channel=-1, int ix=-1, int iy=-1, int iz=-1);
    ~GeomWire();

    int get_index(){return _index;};
    int get_channel(){return _ichannel;};
    int get_xcoord(){return _ix;};
    int get_ycoord(){return _iy;};
    int get_zcoord(){return _iz;};
    Coordinates get_coord();

    int set_index(int index=-1); //if return value is<0, then not giving the index correctly


  private:
    int _index; // index in the vector 
    int _ichannel; // electronic channel
    int _ix; //the coordinate 
    int _iy;
    int _iz;


  };


  typedef std::vector<DataMeasureStructure>  DataMeasureSet;

  typedef std::set<GeomWire> GeomWireSet;
  typedef std::vector<int> GeomWireVect;

}

#endif 
