#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <raymath.h>
#include <algorithm>
#include <string>
#include <iostream>
#include "config.hpp"
#include <unordered_map>

// Entity 
using EntityId = uint32_t;
EntityId nextId = 0;
EntityId CreateEntity() { return nextId++; }

// Components 
struct Position { float x, y; };
struct Velocity { float dx, dy; };
struct Renderable { Color color; float size; };

// Components Stores
std::unordered_map<EntityId, Position> positions;
std::unordered_map<EntityId, Velocity> velocities;
std::unordered_map<EntityId, Renderable> renderables;

// SYSTEMS

// Moves entities that have a postions and a velocity
void MoveSystem(float dt) {
	for (auto& [id, velo] : velocities) {
		if (positions.count(id)) {
			positions[id].x += velo.dx * dt;
			positions[id].y += velo.dy * dt;
		}
	}
}

// Bounces entities off the wall 
void BounceSystem() {
	for (auto& [id, velo] : velocities) {
		if (!positions.count(id)) continue;
		auto& pos = positions[id];

		if (pos.x < 0 or pos.x > GetScreenWidth()) velo.dx *= -1;
		if (pos.y < 0 or pos.y > GetScreenHeight()) velo.dy *= -1;
	}
}


// Renders entities based on the specified color
void RenderSystem() {
	for (auto& [id, rend] : renderables) {
		if (!positions.count(id)) continue;
		auto& pos = positions[id];
		DrawRectangle((int)pos.x, (int)pos.y,
			(int)rend.size, (int)rend.size,
			rend.color);
	}
}

// MISC FUNCTIONS
void InitlizeEntities() {
}


int main() {
	InitWindow(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT, "Agent Cell");
	SetTargetFPS(Config::TARGET_FPS);

	InitlizeEntities();

	EntityId rabbit = CreateEntity();
	positions[rabbit] = { 100, 100};
	velocities[rabbit] = { 120, 80};
	renderables[rabbit] = { WHITE, 12};


	EntityId fox = CreateEntity();
	positions[fox] = { 400, 300};
	velocities[fox] = { -90, 110};
	renderables[fox] = { ORANGE, 16};

	EntityId grass = CreateEntity();
	positions[grass] = { 200, 400};
	renderables[grass] = { GREEN, 10};

	while (!WindowShouldClose()) {
		float deltaTime = GetFrameTime();

		// Update
		MoveSystem(deltaTime);
		BounceSystem();

		// Rendering
		BeginDrawing();

		ClearBackground(BLACK);
		RenderSystem();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
