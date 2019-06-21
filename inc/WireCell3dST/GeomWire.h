#ifndef GEOMWIRE_3DST_h
#define GEOMWIRE_3DST_h

#include <vector>
#include <set>

namespace WireCell3DST {

  struct Coordinates{int x; int y; int z;};

  struct DataMeasureStructure{
//	double t_begin; 
//	double t_end;
	std::vector<double> time;
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

    int set_index(int index=-1); //if return value is<0, then not giving the index correctly
    void set_channel(int ichannel){_ichannel = ichannel;}
    void set_xcoord(int ix){ _ix = ix;}
    void set_ycoord(int iy){ _iy = iy;}
    void set_zcoord(int iz){ _iz = iz;}

    int get_index(){return _index;}
    int get_channel() const {return _ichannel;}
    int get_xcoord() const {return _ix;}
    int get_ycoord() const {return _iy;}
    int get_zcoord() const {return _iz;}
    Coordinates get_coord();

    bool CheckValidity() const {//(const GeomWire& wire) const{
	
	    if(_ix==0&&_iy>0&&_iz>0)
		    return true;
	    else if(_ix>0&&_iy==0&&_iz>0)
		    return true;
	    else if(_ix>0&&_iy>0&&_iz==0)
		    return true;
	    else
		    return false;

    }


    ////
    bool operator<(const GeomWire& wire) const{
	    //shall check the validity of the GeomWire wire??? e.g. check whether ix=-1 iy=-1 and iz=-1
	    int tocompare_x = wire.get_xcoord();
	    int tocompare_y = wire.get_ycoord();
	    int tocompare_z = wire.get_zcoord();
	    if(!(wire.CheckValidity()))
		    return false;
	    if(_ix==0&&_iy>0&&_iz>0)//along axis
	    {
		    if(_ix==tocompare_x)
		    {
			if(_iz<tocompare_z)
				return true;
			else if(_iz==tocompare_z)
			{
				if(_iy<tocompare_y)
					return true;
				else
                                    return false;
			}
			else 
				return false;
		    }
		    else 
			    return true;
	    }
	    else if(_ix>0&&_iy==0&&_iz>0)
	    {
		    if(tocompare_x==0)
			    return false;
		    if(_iy==tocompare_y)
		    {
			if(_iz<tocompare_z)
				return true;
			else if(_iz==tocompare_z)
			{
				if(_ix<tocompare_x)
					return true;
				else
                                    return false;
			}
			else
				return false;

		    }
		    else return true;
	    }
	    else if(_ix>0&&_iy>0&&_iz==0)
	    {
		    if(tocompare_x==0||tocompare_y==0)
			    return false;
		    if(_iz==tocompare_z)
		    {
			    if(_iy<tocompare_y)
				    return true;
			    else if(_iy<tocompare_y)
			    {
				if(_ix<tocompare_x)
					return true;
				else
                                    return false;
			    }
			    else
				    return false;
		    }
		    else
			    return false;
	    }
	    else
		    return false;//invalid this wire

/*

		    //
	    if(_ix<tocompare_x)
		    return true;
	    else if(_ix==tocompare_x)
	    {
		    if(_iy<tocompare_y)
			    return true;
		    else if(_iy==tocompare_y)
		    {
			    if(_iz<tocompare_z)
				return true;
			    else 
				    return false;

		    }
		    else 
			    return false;
	    }
	    else
		    return false;
*/
    }



  private:
    int _index; // index in the vector 
    int _ichannel; // electronic channel
    int _ix; //the coordinate 
    int _iy;
    int _iz;


  };

  struct compareDataMeasure{
	  bool operator()(DataMeasureStructure ma, DataMeasureStructure mb){
		  if(ma.time.size()>0&&mb.time.size()>0)
			  return (ma.time[0]<mb.time[0]);
		  else 
			  return false;
	  }
  };

  struct compareWire{
	  bool operator()(const GeomWire wa, const GeomWire wb){
		  if(wa.CheckValidity()&&wb.CheckValidity())
		  {
			  return (wa)<(wb);
		  }
		  else
			  return false;
	  }
  };


  typedef std::vector<DataMeasureStructure>  DataMeasureVect;
  typedef std::set<DataMeasureStructure, compareDataMeasure>  DataMeasureSet;

  typedef std::set<GeomWire, compareWire> GeomWireSet;
  typedef std::vector<int> GeomWireVect;
  typedef std::vector<const GeomWire*> GeomWireSelection;

  // for wires through a cell, there are x, y, z three wires. as we have more than one class for wires, so define a struct with template 
 /*
  template <typename T>
  struct ObjectXYZ{
		T x; 
		T y;
		T z;	
  };
*/
}

#endif 
