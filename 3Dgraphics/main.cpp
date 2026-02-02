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
#include "scene.h"
#include "angle.h"
#include "pixel.h"
#include "shaders.h"
#include "shape_presets.h"

namespace raylib {	// defined within namespace so names don't clash with graphics
	#include <raylib.h>
}

using namespace graphics;

#define SCREEN_WIDTH 1920/2
#define SCREEN_HEIGHT 1080/2



int main() {

	Scene scene;

	Point camPoint(-1.5, 2, 1.1);
	Angle camAngle(0.4, -.9, 0);
	Camera camera(camPoint, camAngle, 3.14159265 / 2);

	Mesh monkey;
	generateMonkey(monkey);
	monkey.material.shader = physics;
	monkey.material.color = 0xffffff;
	scene.meshCollection.push_back(monkey);



	raylib::InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Graphics");
	raylib::SetTargetFPS(30);

	// Main loop
	while (!raylib::WindowShouldClose()) 
	{

		std::vector<Pixel> frame(SCREEN_WIDTH * SCREEN_HEIGHT, Pixel{ scene.backgroundColor });	// initalize frame vector; set the default pixel to the background color defined in scene object
		camera.renderCamera(frame, SCREEN_WIDTH, SCREEN_HEIGHT, scene);	// render camera to frame vector
		raylib::ClearBackground(raylib::BLACK);
		raylib::BeginDrawing();

		// Draws frame onto screen
		for (int y = 0; y < SCREEN_HEIGHT; y++) {
			for (int x = 0; x < SCREEN_WIDTH; x++) {
				raylib::DrawPixel(x, y, raylib::GetColor((frame.at(y * SCREEN_WIDTH + x).hex << 8) | 0xff));	// raylib color is formatted as 0xRRGGBBAA; need to bitshift to add the alpha channel
			}
			std::cout << std::endl;
		}

		// CAMERA ROTATION 
		if (raylib::IsKeyDown(raylib::KEY_UP)) { camera.rotation.pitch -= .1; }
		if (raylib::IsKeyDown(raylib::KEY_DOWN)) { camera.rotation.pitch += .1; }
		if (raylib::IsKeyDown(raylib::KEY_RIGHT)) { camera.rotation.yaw -= .1; }
		if (raylib::IsKeyDown(raylib::KEY_LEFT)) { camera.rotation.yaw += .1; }
		if (raylib::IsKeyDown(raylib::KEY_E)) { camera.rotation.roll -= .1; }
		if (raylib::IsKeyDown(raylib::KEY_Q)) { camera.rotation.roll += .1; }

		// CAMERA MOVEMENT 
		if (raylib::IsKeyDown(raylib::KEY_W)) { camera.position.x += .1; }
		if (raylib::IsKeyDown(raylib::KEY_A)) { camera.position.y += .1; }
		if (raylib::IsKeyDown(raylib::KEY_S)) { camera.position.x -= .1; }
		if (raylib::IsKeyDown(raylib::KEY_D)) { camera.position.y -= .1; }
		if (raylib::IsKeyDown(raylib::KEY_SPACE)) { camera.position.z += .1; }
		if (raylib::IsKeyDown(raylib::KEY_LEFT_CONTROL)) { camera.position.z -= .1; }

		// DEBUG
		if (raylib::IsKeyDown(raylib::KEY_F)) { camera.position.print(); camera.rotation.print(); }

		raylib::EndDrawing();
	}
	

	return 0;
}