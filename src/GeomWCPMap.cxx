#include "WCP3dST/GeomWCPMap.h"
#include <vector>

using namespace WCP3DST;

Tiling::Tiling()
{
}

Tiling::~Tiling()
{
}

void Tiling::CreateCell(GeomDataSource& gds, GeomWireSelection xwires, GeomWireSelection ywires, GeomWireSelection zwires)
{
	std::map<int, std::vector<Coordinates>> temp_xwire_cellcoord_map;
	std::map<int, std::vector<Coordinates>> temp_ywire_cellcoord_map;
	std::map<int, std::vector<Coordinates>> temp_zwire_cellcoord_map;
	//assume that the wire selections are sorted ???
	for(unsigned int xi=0; xi<xwires.size(); xi++) //what the advantage of iterator or index?
//	for(GeomWireSelection::iterator itx=xwire.begin(); itx!=xwires.end(); itx++)
	{
		for(unsigned int yi=0; yi<ywires.size(); yi++)
		{
			Coordinates crossing={-1, -1, -1};
			if(gds.wiresCrossCoord(*xwires[xi], *ywires[yi], crossing))
			{
				if(temp_xwire_cellcoord_map.find(xi)==temp_xwire_cellcoord_map.end())
				{//not found
					std::vector<Coordinates> tempCoords_x;
					tempCoords_x.push_back(crossing);
					temp_xwire_cellcoord_map[xi]=tempCoords_x;
				}
				else
					temp_xwire_cellcoord_map[xi].push_back(crossing);

				if(temp_ywire_cellcoord_map.find(yi)==temp_ywire_cellcoord_map.end())
				{//not found
					std::vector<Coordinates> tempCoords_y;
					tempCoords_y.push_back(crossing);
					temp_ywire_cellcoord_map[yi]=tempCoords_y;
				}
				else
					temp_ywire_cellcoord_map[yi].push_back(crossing);
			}
		}

		for(unsigned int zi=0; zi<zwires.size(); zi++)
		{
			Coordinates crossing={-1, -1, -1};
			if(gds.wiresCrossCoord(*xwires[xi], *zwires[zi], crossing))
			{
				if(temp_xwire_cellcoord_map.find(xi)==temp_xwire_cellcoord_map.end())
				{//not found
					std::vector<Coordinates> tempCoords_x;
					tempCoords_x.push_back(crossing);
					temp_xwire_cellcoord_map[xi]=tempCoords_x;
				}
				else
				{//found, then need to check whether this crossing point exists already
					bool exist = false;
					for(unsigned int ipoint=0; ipoint<temp_xwire_cellcoord_map.size(); ipoint++)
					{
						if(crossing.x==temp_xwire_cellcoord_map[xi][ipoint].x
								&&crossing.y==temp_xwire_cellcoord_map[xi][ipoint].y
								&&crossing.z==temp_xwire_cellcoord_map[xi][ipoint].z)
						{
							exist=true;
							break;
						}
					}
					if(!exist)
						temp_xwire_cellcoord_map[xi].push_back(crossing);
				}
				if(temp_zwire_cellcoord_map.find(zi)==temp_zwire_cellcoord_map.end())
				{//not found
					std::vector<Coordinates> tempCoords_z;
					tempCoords_z.push_back(crossing);
					temp_zwire_cellcoord_map[zi]=tempCoords_z;
				}
				else
					temp_zwire_cellcoord_map[zi].push_back(crossing);
			}
		}
	}


	//another loop over y and z
	
}
