#include "Grid.h"
#include "Globals.h"
#include <cstdlib>
Grid::Grid(int cols, int rows) : m_cols(cols), m_rows(rows)
{
}

void Grid::GenerateGrid()
{
	m_locations = new bool*[m_rows];
	for (int i = 0; i < m_rows; ++i)
	{
		m_locations[i] = new bool[m_cols];
	}
}

void Grid::ClearGrid()
{
	for (int i = 0; i < m_rows; ++i)
	{
		for (int j = 0; j < m_cols; ++j)
		{
			m_locations[i][j] = false;
		}
	}
}

//game start area x = 24
// game start area y = 64
// game height 480 wiTicksh 480
void Grid::PlaceMushrooms(std::vector<Mushroom> &p_Shrooms, int numToPlace)
{	
	for (int i = 0; i < numToPlace; ++i)
	{
		Mushroom mushroom = Mushroom();
		GridPoint newPoint = GetEmptyLocation();
		mushroom.load(newPoint.x * gCellSize + gGameStrtAreaX, (gGameStartAreaY - gCellSize + 480) - newPoint.y * gCellSize - gCellSize/2 , gCellSize, gCellSize, "mushroom");
		p_Shrooms.push_back(mushroom);
	}
}

GridPoint Grid::GetEmptyLocation()
{
	int randomNum = (rand() % 10);

	int column, row;

	bool found = false;

	while (!found)
	{
		column = (rand() % m_cols);
		row = (rand() % m_rows);

		if (!m_locations[row][column])
		{
			found = true;
			m_locations[row][column] = true;
		}
	}

	GridPoint g;
	g.x = column;
	g.y = row;

	return g;
}