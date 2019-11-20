#ifndef GEOMPHYSICALWIRE_3DST_H
#define GEOMPHYSICALWIRE_3DST_H

#include "GeomWire.h"

namespace WCP3DST{

	class GeomPhysicalWire: public GeomWire{

	public:

		GeomPhysicalWire(int ichannel, int ix, int iy, int iz);
		GeomPhysicalWire(int ichannel, int ix, int iy, int iz, const DataMeasureVect& inputs);
		~GeomPhysicalWire();
		int InitializeWireDataSet(const DataMeasureVect& inputs);
		int addWireDataSet(const DataMeasureVect& inputs);//return the # of DataMeasureStructure added
		int addSingleWireData(DataMeasureStructure input);

//		int getWireDataSet(DataMeasureVect& wireDataset);
		DataMeasureSet getWireDataSet() const {return _wireDataSet;};//not sure whether I should return a adress here or return the value itself. If I return the value itself, does it mean that the set is copied and the copied value is returned
//		DataMeasureSet* getWireDataSet(){return &_wireDataSet;};


		
	private:
		DataMeasureSet _wireDataSet;

	};



	struct compareGeomPhysicsWire{
		bool operator()(const GeomPhysicalWire wa, const GeomPhysicalWire wb) const{
			DataMeasureSet::iterator ita=(wa.getWireDataSet()).begin();
			DataMeasureSet::iterator itb=(wb.getWireDataSet()).begin();
			if((*ita).time.size()>0&&(*itb).time.size()>0)
				return ((*ita).time[0]>(*itb).time[0]);
			else
				return false;
		}


	};

	struct compareGeomPhysicsWirePtr{
		bool operator()(const GeomPhysicalWire* wa, const GeomPhysicalWire* wb) const{
			if(wa && wb){
				DataMeasureSet::iterator ita=(wa->getWireDataSet()).begin();
				DataMeasureSet::iterator itb=(wb->getWireDataSet()).begin();
				if((*ita).time.size()>0&&(*itb).time.size()>0)
					return ((*ita).time[0]>(*itb).time[0]);
				else
					return false;
			}
			else 
				return false;
		}

	};

	typedef std::set<GeomPhysicalWire, compareGeomPhysicsWire> GeomPhysicalWireSet;
	typedef std::set<const GeomPhysicalWire*, compareGeomPhysicsWirePtr> GeomPhysicalWirePtrSet;

}


#endif
