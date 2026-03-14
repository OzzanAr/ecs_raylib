#pragma once
#include <vector>
#include "grid.h"

struct Grass {
    int x, y;
    bool grown = true;
    int regrowTimer = 0;
};

struct Rabbit {
    int x, y;
    int energy = 10;
    int reproduceCounter = 0;
    bool alive = true;
};

struct Fox {
    int x, y;
    int energy = 15;
    int reproduceCounter = 0;
    bool alive = true;
};

// The authoritative storage — one flat array per type
extern std::vector<Grass>  grasses;
extern std::vector<Rabbit> rabbits;
extern std::vector<Fox>    foxes;

// Spawn functions register agents into both the array and the grid
void SpawnGrass(int x, int y);
void SpawnRabbit(int x, int y);
void SpawnFox(int x, int y);
