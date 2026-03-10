#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <vector>
#include <cstdint>
#include <optional>
#include "component.hpp"
#include "config.hpp"

using namespace Config;

// ─────────────────────────────────────────
// GRID SETUP
// ─────────────────────────────────────────

// What can live in a cell
enum class CellType { Empty, Grass, Rabbit, Fox };

struct Cell {
    CellType type = CellType::Empty;
    int      entityIndex = -1; // index into whichever array owns this agent
};

// The grid itself — flat array, indexed as [y * COLS + x]
std::vector<Cell> grid(COLS* ROWS);

// Helper accessors so you never do index math by hand
Cell& GetCell(int x, int y) { return grid[y * COLS + x]; }
bool  InBounds(int x, int y) { return x >= 0 && x < COLS && y >= 0 && y < ROWS; }
void  ClearCell(int x, int y) { grid[y * COLS + x] = { CellType::Empty, -1 }; }
void  SetCell(int x, int y, CellType t, int idx) { grid[y * COLS + x] = { t, idx }; }

// ─────────────────────────────────────────
// COMPONENTS (same as before, but position
// is now a grid coordinate, not pixels)
// ─────────────────────────────────────────

struct Rabbit {
    Position pos;
    int energy = 10;
};

struct Fox {
    Position pos;
    int energy = 15;
};

std::vector<Rabbit> rabbits;
std::vector<Fox>    foxes;

// ─────────────────────────────────────────
// SPAWNING
// ─────────────────────────────────────────
void SpawnRabbit(int x, int y) {
    if (!InBounds(x, y)) return;
    if (GetCell(x, y).type != CellType::Empty) return;

    int idx = rabbits.size();
    rabbits.push_back({ {x, y}, 10 });
    SetCell(x, y, CellType::Rabbit, idx);
}

void SpawnFox(int x, int y) {
    if (!InBounds(x, y)) return;
    if (GetCell(x, y).type != CellType::Empty) return;

    int idx = foxes.size();
    foxes.push_back({ {x, y}, 15 });
    SetCell(x, y, CellType::Fox, idx);
}

// ─────────────────────────────────────────
// SYSTEMS
// ─────────────────────────────────────────

// Tries to move a rabbit one step in a random direction
void UpdateRabbits() {
    int dirs[4][2] = { {0,-1},{0,1},{-1,0},{1,0} };

    for (auto& rabbit : rabbits) {
        auto [dx, dy] = dirs[GetRandomValue(0, 3)];
        int nx = rabbit.pos.x + dx;
        int ny = rabbit.pos.y + dy;

        if (!InBounds(nx, ny)) continue;
        if (GetCell(nx, ny).type != CellType::Empty) continue;

        // vacate old cell, occupy new one
        ClearCell(rabbit.pos.x, rabbit.pos.y);
        rabbit.pos = { nx, ny };
        SetCell(nx, ny, CellType::Rabbit, -1); // -1 is fine for now
    }
}

// Renders the grid — purely visual, reads grid state only
void RenderGrid() {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            Color color = BLACK;
            switch (GetCell(x, y).type) {
            case CellType::Grass:  color = DARKGREEN; break;
            case CellType::Rabbit: color = PINK;     break;
            case CellType::Fox:    color = ORANGE;    break;
            default: break;
            }
            DrawRectangle(x * CELL_SIZE, y * CELL_SIZE,
                CELL_SIZE - 1, CELL_SIZE - 1, // -1 gives a grid gap
                color);
        }
    }
}

// ─────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────
int main() {
    InitWindow(COLS * CELL_SIZE, ROWS * CELL_SIZE, "Grid ECS");
    SetTargetFPS(10); // slow enough to watch

    // Seed a few agents
    SpawnRabbit(5, 5);
    SpawnRabbit(10, 8);
    SpawnFox(20, 15);

    // Sprinkle some grass
    for (int i = 0; i < 100; i++) {
        int x = GetRandomValue(0, COLS - 1);
        int y = GetRandomValue(0, ROWS - 1);
        if (GetCell(x, y).type == CellType::Empty)
            SetCell(x, y, CellType::Grass, -1);
    }

    while (!WindowShouldClose()) {
        UpdateRabbits();

        BeginDrawing();
        ClearBackground(BLACK);
        RenderGrid();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}