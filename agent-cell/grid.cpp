#include "grid.h"

std::vector<Cell> grid(COLS* ROWS);

Cell& GetCell(int x, int y) {
	return grid[y * COLS + x];
}

bool  InBounds(int x, int y) {
	return x >= 0 && x < COLS && y >= 0 && y < ROWS;
}

void  ClearCell(int x, int y) { 
	grid[y * COLS + x] = { CellType::Empty, -1 }; 
}

void  SetCell(int x, int y, CellType t, int idx) { 
	grid[y * COLS + x] = { t, idx }; 
}

void  InitGrid() { 
	grid.assign(COLS * ROWS, { CellType::Empty, -1 }); 
}
