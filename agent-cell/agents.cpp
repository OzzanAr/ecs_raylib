#include "agents.h" 

std::vector<Grass> grasses;
std::vector<Rabbit> rabbits;
std::vector<Fox> foxes;

void SpawnGrass(int x, int y) {
    if (!InBounds(x, y) || GetCell(x, y).type != CellType::Empty) return;

    int idx = grasses.size();
    grasses.push_back({ x, y, true, 0 });

    SetCell(x, y, CellType::Grass, idx);
}

void SpawnRabbit(int x, int y) {
    if (!InBounds(x, y) || GetCell(x, y).type != CellType::Empty) return;

    int idx = rabbits.size();
    rabbits.push_back({ x, y, 10, 0, true });

    SetCell(x, y, CellType::Rabbit, idx);
}

void SpawnFox(int x, int y) {
    if (!InBounds(x, y) || GetCell(x, y).type != CellType::Empty) return;

    int idx = foxes.size();
    foxes.push_back({ x, y, 15, 0, true });

    SetCell(x, y, CellType::Fox, idx);
}