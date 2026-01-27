#pragma once
#include <iostream>
#include <vector>
#include "window.h"
#include "point.h"
#include "vector.h"
#include "line.h"
#include "plane.h"
#include "triangle.h"
#include "camera.h"
#include "angle.h"

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

	Triangle triangle(Point(2, .7, .8), Point(2, -1, .5), Point(2, -.7, -.2));

	// Draw window
	Window* pWindow = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	bool running = true;
	
	while (running) {

		camera.renderCamera(screen, SCREEN_WIDTH, SCREEN_HEIGHT, triangle);
		camera.rotation.yaw += 3.14159 / 90;

		for (int y = 0; y < SCREEN_HEIGHT; y++) {
			for (int x = 0; x < SCREEN_WIDTH; x++) {

				if (screen[(y * (SCREEN_WIDTH - 1)) + x]) {
					pWindow->m_pixels[(y * (SCREEN_WIDTH - 1)) + x] = RGB(255, 255, 255);
				}
				else {
					pWindow->m_pixels[(y * (SCREEN_WIDTH - 1)) + x] = RGB(0, 0, 0);
				}

			}
		}

		pWindow->DrawFrame();

		if (!pWindow->ProcessMessages()) {
			running = false;
		}

		Sleep(1);
	}
	

	delete pWindow;

	return 0;
}