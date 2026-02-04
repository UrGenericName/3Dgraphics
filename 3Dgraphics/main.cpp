#pragma once
#include "graphics.h"

#define SCREEN_WIDTH 1920/8
#define SCREEN_HEIGHT 1080/8

using namespace graphics;

int main() {

	Scene scene;

	Point camPoint(-1.5, 2, 1.1);
	Angle camAngle(0.4, -.9, 0);
	float camFOV = 3.14159265 / 2;
	Camera camera(camPoint, camAngle, camFOV);

	Mesh cube;
	generateCube(cube);
	cube.material.shader = physics;
	scene.meshCollection.push_back(cube);

	camera.renderCamera(SCREEN_WIDTH, SCREEN_HEIGHT, scene);

	return 0;
}