#pragma once
#ifndef _LEVELMAP_H
#define _LEVELMAP_H
#include "Constants.h"
class Levelmap
{
public:
	Levelmap(int map[MAP_HEIGHT][MAP_WIDTH]);
	~Levelmap();

	int GetTileAt(unsigned int h, unsigned int w);
	void ChangeTileAt(unsigned int row, unsigned column, unsigned int new_value);
private:
	int** m_map;
};
#endif