// systems.cpp
#include "systems.h"
#include "agents.h"
#include "grid.h"
#include "raylib.h"

void UpdateGrass() {
    for (auto& grass : grasses) {
        if (!grass.grown) {
            grass.regrowTimer--;
            if (grass.regrowTimer <= 0) {
                grass.grown = true;
                SetCell(grass.x, grass.y, CellType::Grass, -1);
            }
        }
    }
}

void UpdateRabbits() {
    int dirs[4][2] = { {0,-1},{0,1},{-1,0},{1,0} };
    for (auto& rabbit : rabbits) {
        if (!rabbit.alive) continue;

        rabbit.energy--;

        auto [dx, dy] = dirs[GetRandomValue(0, 3)];
        int nx = rabbit.x + dx;
        int ny = rabbit.y + dy;

        if (!InBounds(nx, ny)) continue;

        Cell& target = GetCell(nx, ny);
        if (target.type == CellType::Grass) {
            rabbit.energy += 5; // eat grass
            // grass regrow logic would go here
        }
        if (target.type == CellType::Empty || target.type == CellType::Grass) {
            ClearCell(rabbit.x, rabbit.y);
            rabbit.x = nx;
            rabbit.y = ny;
            SetCell(nx, ny, CellType::Rabbit, -1);
        }
    }
}

void UpdateFoxes() {
    int dirs[4][2] = { {0,-1},{0,1},{-1,0},{1,0} };
    for (auto& fox : foxes) {
        if (!fox.alive) continue;

        fox.energy--;

        auto [dx, dy] = dirs[GetRandomValue(0, 3)];
        int nx = fox.x + dx;
        int ny = fox.y + dy;

        if (!InBounds(nx, ny)) continue;

        Cell& target = GetCell(nx, ny);
        if (target.type == CellType::Rabbit) {
            fox.energy += 10; // eat rabbit
            rabbits[target.entityIndex].alive = false;
        }
        if (target.type == CellType::Empty || target.type == CellType::Rabbit) {
            ClearCell(fox.x, fox.y);
            fox.x = nx;
            fox.y = ny;
            SetCell(nx, ny, CellType::Fox, -1);
        }
    }
}

void ResolveDeaths() {
    for (auto& rabbit : rabbits)
        if (rabbit.energy <= 0) rabbit.alive = false;
    for (auto& fox : foxes)
        if (fox.energy <= 0) fox.alive = false;
    // Note: actual removal from vectors handled in simulation.cpp
}

void ResolveReproduction() {
    // Placeholder — add when core loop is stable
}

void RenderGrid() {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            Color color = BLACK;
            switch (GetCell(x, y).type) {
            case CellType::Grass:  color = DARKGREEN; break;
            case CellType::Rabbit: color = WHITE;     break;
            case CellType::Fox:    color = ORANGE;    break;
            default: break;
            }
            DrawRectangle(x * CELL_SIZE, y * CELL_SIZE,
                CELL_SIZE - 1, CELL_SIZE - 1, color);
        }
    }
}