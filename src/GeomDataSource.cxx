#include <fstream>
#include <cassert>

#include "WireCell3dST/GeomDataSource.h"

using namespace WireCell3DST;

GeomDataSource::GeomDataSource()
{
	_wireset.clear();
}

GeomDataSource::~GeomDataSource()
{
	_wireset.clear();
}
/*
GeomDataSource::GeomDataSource(const char* filename)
{
	if(filename){
		std::ifstream geomtryfile(filename);
		this->load(geomtryfile);

	}

}


void GeomDataSource::load(std::istream &data)
{
	std::string line;
	
}
*/

void GeomDataSource::add_wire(GeomWire& wire)
{
	_wireset.insert(wire);
}

bool GeomDataSource::wiresCrossCoord(const GeomWire& wire1, const GeomWire& wire2, Coordinates& coord)
{
	if(!wire1.CheckValidity()||!wire2.CheckValidity())
		return false;
	//could simply the code below.By just comparing any coord same thenuse max.  will do it later. 
	if((wire1.get_xcoord()==0&&wire2.get_ycoord()==0)||(wire1.get_ycoord()==0&&wire2.get_xcoord()==0))
	{
		if(wire1.get_zcoord()==wire2.get_zcoord())
		{
			coord.x = std::max(wire1.get_xcoord(), wire2.get_xcoord());//non zero one. as we have check the validity, so 0 is minimum value, i.e non-zero is euqivalent to >0
			coord.y = std::max(wire1.get_ycoord(), wire2.get_ycoord());
			coord.z = wire1.get_zcoord();
			return true;

		}
		else return false;
	}
	else if((wire1.get_xcoord()==0&&wire2.get_zcoord()==0)||(wire1.get_zcoord()==0&&wire2.get_xcoord()==0))
	{
		if(wire1.get_ycoord()==wire2.get_ycoord())
		{
			coord.x = std::max(wire1.get_xcoord(), wire2.get_xcoord());
			coord.y = wire1.get_ycoord();
			coord.z = std::max(wire1.get_zcoord(), wire2.get_zcoord());
			return true;

		}
		else return false;
	}
	else if((wire1.get_ycoord()==0&&wire2.get_zcoord()==0)||(wire1.get_zcoord()==0&&wire2.get_ycoord()==0))
	{
		if(wire1.get_xcoord()==wire2.get_xcoord())
		{
			coord.x = wire2.get_xcoord();
			coord.y = std::max(wire1.get_ycoord(), wire2.get_ycoord());
			coord.z = std::max(wire1.get_zcoord(), wire2.get_zcoord());
			return true;

		}
		else return false;
	}
	else return false;

}
//GeomDataSource::
//GeomDataSource::
//GeomDataSource::


