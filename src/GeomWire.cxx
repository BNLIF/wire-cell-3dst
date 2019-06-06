#include "GeomWire.h"

using namespace WireCell3DST

//GeomWire::GeomWire(int index, int channel, int ix, int iy, int iz)
GeomWire::GeomWire(int channel, int ix, int iy, int iz)
//	: _index(index)
	:_channel(channel)
	,_ix(ix)
	,_iy(iy)
	,_iz(iz)
{
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
