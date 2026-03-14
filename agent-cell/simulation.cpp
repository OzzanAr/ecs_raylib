#include "simulation.h"
#include "systems.h"
#include "agents.h"
#include "grid.h"
#include "raylib.h"

void InitSimulation() {
    InitGrid();

    for (int i = 0; i < 80; i++)
        SpawnGrass(GetRandomValue(0, COLS - 1), GetRandomValue(0, ROWS - 1));
    for (int i = 0; i < 20; i++)
        SpawnRabbit(GetRandomValue(0, COLS - 1), GetRandomValue(0, ROWS - 1));
    for (int i = 0; i < 5; i++)
        SpawnFox(GetRandomValue(0, COLS - 1), GetRandomValue(0, ROWS - 1));
}

void StepSimulation() {
    // THIS ORDER IS SACRED — do not reorder casually
    UpdateGrass();
    UpdateRabbits();
    UpdateFoxes();
    ResolveDeaths();
    ResolveReproduction();
}