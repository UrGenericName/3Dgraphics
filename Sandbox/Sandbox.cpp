#pragma once
#include <iostream>
#include <3Dgraphics/3Dgraphics.h> 

#define SCREEN_WIDTH 1920/2
#define SCREEN_HEIGHT 1080/2

using namespace graphics;

int main() {

	Scene scene;

	Camera cam( Point(-1.5, 2, 1.1), Angle(0.4, -.9, 0), 3.14159/3 );

	Mesh cube;
	generateCube(cube);
	cube.material.shader = physics;
	scene.meshCollection.push_back(cube);	

	cam.renderCamera(SCREEN_WIDTH, SCREEN_HEIGHT, scene);

	return 0;
}