#ifndef GEOMWIRECELLMAP_3DST_H
#define GEOMWIRECELLMAP_3DST_H

#include "GeomWire.h"
#include "GeomCell.h"
#include "GeomDataSource.h"

#include <map>

namespace WCP3DST{

    typedef std::map<const GeomCell*, GeomWireSelection> GeomCell2WiresMap;
    typedef std::map<const GeomWire*, GeomCellSelection> GeomWire2CellsMap;

    class Tiling{
	public:
		Tiling();
		~Tiling();
		void CreateCell(const GeomDataSource& gds, GeomWireSelection wires);
		void CreateCell( GeomDataSource& gds, GeomWireSelection xwires, GeomWireSelection ywires, GeomWireSelection zwires);

		GeomWireSelection getWiresfromCell(const GeomCell* cell) const;
		GeomCellSelection getCellsfromWire(const GeomWire* wire) const;



	private:
		GeomCell2WiresMap celll2wiremap;
		GeomWire2CellsMap wire2cellmap;

    };

}


#endif

