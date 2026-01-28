#pragma once
#include <iostream>
#include <vector>
#include "point.h"
#include "vector.h"
#include "line.h"
#include "plane.h"
#include "polygon.h"
#include "mesh.h"
#include "camera.h"
#include "angle.h"

namespace raylib {	// defined within namespace so names don't clash with graphics
	#include <raylib.h>
}

using namespace graphics;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define FILL '#'
#define EMPTY '-'


int main() {

	// Define screen vector
	std::vector<bool> screen(SCREEN_WIDTH * SCREEN_HEIGHT, false);

	Point camPoint(0, -2, 0.3);
	Angle camAngle(0, 3.14159 / 5, 0);
	Camera camera(camPoint, camAngle, 3.14159265 / 2);

	Polygon polygonA(Point(2, .7, .8), Point(2, -1, .5), Point(2, -.7, -.2));
	Polygon polygonB(Point(4, .7, .8), Point(4, -1, .5), Point(4, -.7, -.2));

	Mesh test;
	test.polygonCollection.push_back(polygonA);
	test.polygonCollection.push_back(polygonB);
	std::cout << test.isValid() << std::endl;

	raylib::InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Graphics");
	raylib::SetTargetFPS(15);

	// Main loop
	while (!raylib::WindowShouldClose()) 
	{
		camera.renderCamera(screen, SCREEN_WIDTH, SCREEN_HEIGHT, test);
		raylib::BeginDrawing();
		raylib::ClearBackground(raylib::BLACK);

		// Draws frame onto screen
		for (int y = 0; y < SCREEN_HEIGHT; y++) {
			for (int x = 0; x < SCREEN_WIDTH; x++) {
				screen[y * SCREEN_WIDTH + x] ? raylib::DrawPixel(x, y, raylib::WHITE) : raylib::DrawPixel(x, y, raylib::BLACK);
			}
			std::cout << std::endl;

		}

		raylib::EndDrawing();
	}

	return 0;
}