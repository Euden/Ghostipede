#ifndef _GRID_H_
#define _GRID_H_

#include <vector>
#include "Mushroom.h"
struct GridPoint
{
	int x;
	int y;
};

class Grid
{
public:
	Grid(int cols, int rows);
	
	void GenerateGrid();

	void ClearGrid();

	void PlaceMushrooms(std::vector<Mushroom> &p_MushroomArray, int numToPlace);

private:
	GridPoint GetEmptyLocation();

	int m_rows, m_cols;
	
	bool **m_locations;

};
#endif
