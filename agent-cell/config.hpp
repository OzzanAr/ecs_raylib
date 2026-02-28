#pragma once

namespace Config {
    // World
    constexpr int GRID_WIDTH = 100;
    constexpr int GRID_HEIGHT = 100;
    constexpr int CELL_SIZE = 8; // pixels

    // ECS Values
    constexpr int MAX_COMPONETS = 10;
    constexpr int MAX_ENTITIES = 50;

    // Initial populations
    constexpr int INITIAL_GRASS = 2000;
    constexpr int INITIAL_RABBITS = 50;
    constexpr int INITIAL_FOXES = 10;

    // Grass
    constexpr float GRASS_GROWTH_RATE = 0.02f;
    constexpr int GRASS_ENERGY_VALUE = 20;

    // Rabbits
    constexpr int RABBIT_INITIAL_ENERGY = 50;
    constexpr int RABBIT_MOVE_COST = 1;
    constexpr int RABBIT_REPRODUCE_THRESHOLD = 80;
    constexpr int RABBIT_REPRODUCE_COST = 40;
    constexpr int RABBIT_MAX_AGE = 200;

    // Foxes
    constexpr int FOX_INITIAL_ENERGY = 100;
    constexpr int FOX_MOVE_COST = 2;
    constexpr int FOX_REPRODUCE_THRESHOLD = 150;
    constexpr int FOX_REPRODUCE_COST = 80;
    constexpr int FOX_MAX_AGE = 300;
    constexpr int FOX_HUNT_ENERGY_GAIN = 60;

    // Simulation
    constexpr int TARGET_FPS = 60;
    constexpr int STEPS_PER_FRAME = 1; // Speed control
    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 600;
}

