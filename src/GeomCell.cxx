#include <GeomCell.h>


use namespace WireCell3DST;

GeomCell::GeomCell(int ix, int iy; int iz)
	:_ix(ix)
	,_iy(iy)
	,_iz(iz)
{
}

GeomCell::~CeomCell()
{
}

int GeomCell::set_index(int index)
{
	_index = index;
	return _index;
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
