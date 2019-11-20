#ifndef GEOMDATASOURCE_3DST_h
#define GEOMDATASOURCE_3DST_h

#include <iostream>
#include <sstream>
#include <istream>
#include <vector>
#include <map>

#include "GeomWire.h"
#include "GeomCell.h"
#include "GeomPhysicalWire.h"
#include "GeomComputationalWire.h"


namespace WCP3DST {

	class GeomDataSource {

	public:
		GeomDataSource();
//		GeomDataSource(const char* filename);
		~GeomDataSource();

		void add_wire(GeomWire& wire);
		const GeomWireSet& get_wireset() const{return _wireset;}
//		const GeomWireVect& get_wirevect() const;

//		void load(std::istream &data);
//
		bool wiresCrossCoord(const GeomWire& wire1, const GeomWire& wire2, Coordinates& coord);

	private:
		GeomWireSet _wireset;
//		GeomWireVect _wirevect;


//		mutable std::map<GeomWire, GeomCellSet> PhysWire2CellSetMap;
//		mutable std::map<GeomCell, ObjectXYZ<GeomComputationalWire>> Cell2CompWireMap;


//		bool buildPhysWCPSetMap();
//		bool buildCellCompWireMap();
	};



}



#endif



