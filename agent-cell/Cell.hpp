#ifndef CELL_HPP
#define CELL_HPP

enum class CellType { 
	Empty, 
	Grass, 
	Rabbit, 
	Fox
};

struct  Cell
{
	CellType type = CellType::Empty;
	int entityIndex = 1;
};

#endif
