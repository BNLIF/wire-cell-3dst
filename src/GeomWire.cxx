#include "WCP3dST/GeomWire.h"

using namespace WCP3DST;

//GeomWire::GeomWire(int index, int channel, int ix, int iy, int iz)
GeomWire::GeomWire(int channel, int ix, int iy, int iz)
//	: _index(index)
	:_ichannel(channel)
	,_ix(ix)
	,_iy(iy)
	,_iz(iz)
{
//	_wireDataSet.clear();
}

GeomWire::~GeomWire()
{
}

Coordinates GeomWire::get_coord()
{
	Coordinates c1 = {_ix, _iy, _iz};
	return c1;
}

int GeomWire::set_index(int index)
{
	_index = index;
	return _index;
}

bool GeomWire::operator<(const GeomWire& wire) const{
    //shall check the validity of the GeomWire wire??? e.g. check whether ix=-1 iy=-1 and iz=-1
    int tocompare_x = wire.get_xcoord();
    int tocompare_y = wire.get_ycoord();
    int tocompare_z = wire.get_zcoord();
    if(!(wire.CheckWireValidity()))
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


