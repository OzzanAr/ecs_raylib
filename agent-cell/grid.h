#ifndef GRID_H 
#define GRID_H 

#include "config.h"
#include "cell.h"
#include <vector>

using namespace Config;

std::vector<Cell> grid;

Cell& GetCell(int x, int y);
bool  InBounds(int x, int y);
void  ClearCell(int x, int y);
void  SetCell(int x, int y, CellType t, int idx);
void  InitGrid();

#endif
