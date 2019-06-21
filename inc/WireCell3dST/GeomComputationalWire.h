#ifndef GROMCOMPUTEWIRE_3DST_H
#define GROMCOMPUTEWIRE_3DST_H

#include "GeomWire.h"

namespace WireCell3DST{

	class GeomComputationalWire: public GeomWire{

	public:
		GeomComputationalWire(int ichannel, int ix, int iy, int iz);
		~GeomComputationalWire();

		int InitializeWireData(DataMeasureStructure wireData);
		DataMeasureStructure getWireData(){return _wireData;};


	private:
		DataMeasureStructure _wireData;
		

	};

}

#endif
