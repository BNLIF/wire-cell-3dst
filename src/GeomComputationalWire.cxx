#include "WireCell3dST/GeomComputationalWire.h"

using namespace WireCell3DST;


GeomComputationalWire::GeomComputationalWire(int ichannel, int ix, int iy, int iz)
	:GeomWire(ichannel, ix, iy, iz)
{
}

GeomComputationalWire::~GeomComputationalWire()
{
}


int GeomComputationalWire::InitializeWireData(DataMeasureStructure wireData)
{
	_wireData.t_begin = wireData.t_begin;
	_wireData.t_end = wireData.t_end;
	_wireData.charges = wireData.charges; //copy the vector. Will it cause memory problem in the future???

	return (int) _wireData.charges.size();
}
