#include "WCP3dST/GeomCell.h"


using namespace WCP3DST;

GeomCell::GeomCell(int ix, int iy, int iz)
	:_ix(ix)
	,_iy(iy)
	,_iz(iz)
{
}

GeomCell::~GeomCell()
{
}

int GeomCell::set_index(int index)
{
	_index = index;
	return _index;
}

Coordinates GeomCell::get_coord() const
{
	Coordinates c1 = {_ix, _iy, _iz};
	return c1;
}

Coordinates GeomCell::get_xwire()
{
	Coordinates c1 = {0, _iy, _iz};
	return c1;
}

Coordinates GeomCell::get_ywire() 
{
	Coordinates c1 = {_ix, 0, _iz};
	return c1;
}

Coordinates GeomCell::get_zwire()
{
	Coordinates c1 = {_ix, _iy, 0};
	return c1;
}

int GeomCell::InitializeCellData(DataMeasureStructure cellData)
{
//	_cellData.t_begin = cellData.t_begin;
//        _cellData.t_end = cellData.t_end;
	_cellData.time = cellData.time;
        _cellData.charges = cellData.charges; //copy the vector. Will it cause memory problem in the future???

        return (int) _cellData.charges.size();

}
