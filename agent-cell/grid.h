#pragma once
#include "config.h"
#include <vector>

using namespace Config;

enum class CellType { 
	Empty, 
	Grass, 
	Rabbit, 
	Fox
};

struct Cell
{
	CellType type = CellType::Empty;
	int entityIndex = -1;
};

extern std::vector<Cell> grid;

Cell& GetCell(int x, int y);
bool  InBounds(int x, int y);
void  ClearCell(int x, int y);
void  SetCell(int x, int y, CellType t, int idx);
void  InitGrid();
