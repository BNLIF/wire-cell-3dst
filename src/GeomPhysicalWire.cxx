#include "WireCell3dST/GeomPhysicalWire.h"

using namespace WireCell3DST;

GeomPhysicalWire::GeomPhysicalWire(int ichannel, int ix, int iy, int iz)
	:GeomWire(ichannel, ix, iy, iz)
{
	_wireDataSet.clear();
}

GeomPhysicalWire::~GeomPhysicalWire()
{
	_wireDataSet.clear();
}


int GeomPhysicalWire::InitializeWireDataSet(const DataMeasureSet& inputs)
{
        _wireDataSet.clear();
        int Ninputs = addWireDataSet(inputs);
        return Ninputs;
}

int GeomPhysicalWire::addWireDataSet(const DataMeasureSet& inputs)
{
        int Ninputs = inputs.size();
        for(int i=0; i<Ninputs; i++)
                _wireDataSet.push_back(inputs[i]);

        return Ninputs;
}

int GeomPhysicalWire::addSingleWireData(DataMeasureStructure input)
{
         _wireDataSet.push_back(input);
         return 1;
}


