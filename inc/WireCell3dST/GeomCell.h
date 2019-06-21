#ifndef GEOMCELL_3DST_h
#define GEOMCELL_3DST_h

#include <iostream>
#include <vector>
#include <set>

#include "GeomWire.h"


namespace WireCell3DST {



	class GeomCell {

	// Remember that to match the def in Wire, coord originate from (1,1,1)

	public:
//		GeomCell(int index=-1; int ix=-1, int iy=-1; int iz=-1);
		GeomCell(int ix=-1, int iy=-1, int iz=-1);
		~GeomCell();

		int get_index(){return _index;}
		int get_xcoord() const {return _ix;}
		int get_ycoord() const {return _iy;}
		int get_zcoord() const {return _iz;}
		int set_index(int index=-1);
		Coordinates get_xwire(); //get the wire passing this cell and along x-axis
		Coordinates get_ywire();
		Coordinates get_zwire();

		int InitializeCellData(DataMeasureStructure cellData);
		DataMeasureStructure getCellData(){return _cellData;};

		bool CheckCellValidity() const
		{
			if(_ix>0&&_iy>0&&_iz>0)
				return true;
			else 
				return false;
		}

		bool operator=(const GeomCell& cell) const{
			if(CheckCellValidity()&&cell.CheckCellValidity())
			{
				if(_ix==cell.get_xcoord()&&_iy==cell.get_ycoord()&&_iz==cell.get_zcoord())
					return true;
				else
					return false;
			}
			else
				return false;
		}

	private:
		int _index; //index in the vector
		int _ix; //coordinate		
		int _iy;
		int _iz;
		DataMeasureStructure _cellData;

	};

	typedef std::set<GeomCell> GeomCellSet;
	typedef std::vector<int> GeomCellVect;
	typedef std::vector<const GeomCell*> GeomCellSelection;

}

#endif

