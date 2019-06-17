#ifndef GEOMCELL_3DST_h
#define GEOMCELL_3DST_h

#include <iostream>

#include "GeomWire.h"


namespace WireCell3DST {



	class GeomCell {

	// Remember that to match the def in Wire, coord originate from (1,1,1)

	public:
//		GeomCell(int index=-1; int ix=-1, int iy=-1; int iz=-1);
		GeomCell(int ix=-1, int iy=-1, int iz=-1);
		~GeomCell();

		int get_index(){return _index;};
		int get_xcoord(){return _ix;};
		int get_ycoord(){return _iy;};
		int get_zcoord(){return _iz;};
		int set_index(int index=-1);
		Coordinates get_xwire(); //get the wire passing this cell and along x-axis
		Coordinates get_ywire();
		Coordinates get_zwire();

		int InitializeCellData(DataMeasureStructure cellData);
		DataMeasureStructure getCellData(){return _cellData;};

	private:
		int _index; //index in the vector
		int _ix; //coordinate		
		int _iy;
		int _iz;
		DataMeasureStructure _cellData;

	};

}

#endif

