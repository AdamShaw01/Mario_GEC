#include "Levelmap.h"

//when making a map remember: 0 = empty 1 = occupied

Levelmap::Levelmap(int map[MAP_HEIGHT][MAP_WIDTH])
{
	//allocate memory for the level map
	m_map = new int* [MAP_HEIGHT];
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		m_map[i] = new int[MAP_WIDTH];
	}

	//populate the array
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; j++)
		{
			m_map[i][j] = map[i][j];
		}
	}
}
Levelmap::~Levelmap()
{
	//delete all elements of the array
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		delete[] m_map[i];
	}
	delete[]m_map;
}
int Levelmap::GetTileAt(unsigned int h, unsigned int w)
{
	if (h < MAP_HEIGHT && w < MAP_WIDTH)
	{
		return m_map[h][w];
	}
	return 0;
}
void Levelmap::ChangeTileAt(unsigned int row, unsigned column, unsigned int new_value)
{

}