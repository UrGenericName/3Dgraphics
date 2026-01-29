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

#define SCREEN_WIDTH 1920/4
#define SCREEN_HEIGHT 1080/4



int main() {

	Scene scene;

	Point camPoint(-5.1, 3.9, 4.1);
	Angle camAngle(0, 0, 0);
	Camera camera(camPoint, camAngle, 3.14159265 / 2);

	Mesh pyramid;
	generatePyramid(pyramid);
	pyramid.position = { 2, 1, 3 };
	pyramid.material.shader = shaders::physics;

	Mesh cube;
	generateCube(cube);
	cube.position = { 2, 1, 2 };
	cube.material.shader = shaders::physics;

	Mesh cylinder;
	generateCylinder(cylinder);
	cylinder.position = { 2, 1, 0 };
	cylinder.material.shader = shaders::physics;

	scene.meshCollection.push_back(pyramid);
	scene.meshCollection.push_back(cube);
	scene.meshCollection.push_back(cylinder);

	pyramid.position.y = -1;
	cube.position.y = -1;
	cylinder.position.y = -1;
	pyramid.material.shader = shaders::flat;
	pyramid.material.color = 0xff0000;
	cube.material.shader = shaders::flat;
	cube.material.color = 0x00ff00;
	cylinder.material.shader = shaders::flat;
	cylinder.material.color = 0x0000ff;

	scene.meshCollection.push_back(pyramid);
	scene.meshCollection.push_back(cube);
	scene.meshCollection.push_back(cylinder);

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
		if (raylib::IsKeyDown(raylib::KEY_UP)) { camera.rotation.pitch += .1; }
		if (raylib::IsKeyDown(raylib::KEY_LEFT)) { camera.rotation.yaw += .1; }
		if (raylib::IsKeyDown(raylib::KEY_DOWN)) { camera.rotation.pitch -= .1; }
		if (raylib::IsKeyDown(raylib::KEY_RIGHT)) { camera.rotation.yaw -= .1; }

		// CAMERA MOVEMENT 
		if (raylib::IsKeyDown(raylib::KEY_W)) { camera.position.x += .1; }
		if (raylib::IsKeyDown(raylib::KEY_A)) { camera.position.y += .1; }
		if (raylib::IsKeyDown(raylib::KEY_S)) { camera.position.x -= .1; }
		if (raylib::IsKeyDown(raylib::KEY_D)) { camera.position.y -= .1; }
		if (raylib::IsKeyDown(raylib::KEY_SPACE)) { camera.position.z += .1; }
		if (raylib::IsKeyDown(raylib::KEY_LEFT_CONTROL)) { camera.position.z -= .1; }

		// DEBUG
		if (raylib::IsKeyDown(raylib::KEY_E)) { camera.position.print(); camera.rotation.print(); }

		raylib::EndDrawing();
	}
	

	return 0;
}