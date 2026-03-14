#pragma once
#include <iostream>
#include <3Dgraphics/3Dgraphics.h> 

#define SCREEN_WIDTH 1920/2
#define SCREEN_HEIGHT 1080/2

using namespace graphics;

int main() {

	Scene scene;

	Point camPoint(-1.5, 2, 1.1);
	Angle camAngle(0.4, -.9, 0);
	float camFOV = 3.14159265 / 3;
	Camera camera(camPoint, camAngle, camFOV);

	Mesh cube;
	generateCylinder(cube);
	cube.material.shader = physics;
	scene.meshCollection.push_back(cube);

	camera.renderCamera(SCREEN_WIDTH, SCREEN_HEIGHT, scene);

	return 0;
}