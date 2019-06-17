#ifndef GEOMPHYSICALWIRE_3DST_H
#define GEOMPHYSICALWIRE_3DST_H

#include "GeomWire.h"

namespace WireCell3DST{

	class GeomPhysicalWire: public GeomWire{

	public:

		GeomPhysicalWire(int ichannel, int ix, int iy, int iz);
		~GeomPhysicalWire();
		int InitializeWireDataSet(const DataMeasureSet& inputs);
		int addWireDataSet(const DataMeasureSet& inputs);//return the # of DataMeasureStructure added
		int addSingleWireData(DataMeasureStructure input);

//		int getWireDataSet(DataMeasureSet& wireDataset);
		DataMeasureSet getWireDataSet(){return _wireDataSet;};//It seems that after c++11, this way in almost as effecient as the one above


		
	private:
		DataMeasureSet _wireDataSet;

	};

}


#endif
