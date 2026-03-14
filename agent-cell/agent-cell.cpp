#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <vector>
#include <cstdint>
#include <optional>
#include "config.h"
#include "grid.h"
#include "agents.h"
#include "simulation.h"
#include "systems.h"

using namespace Config;

int main() {
    InitWindow(COLS * CELL_SIZE, ROWS * CELL_SIZE, "Predator-Prey");
    SetTargetFPS(10);

    InitSimulation();

    while (!WindowShouldClose()) {
        StepSimulation();

        BeginDrawing();
        ClearBackground(BLACK);
        RenderGrid();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
