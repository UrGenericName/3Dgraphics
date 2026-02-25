#pragma once
#include <cmath>
#include <iostream>
#include "3Dgraphics/camera.h"
#include "3Dgraphics/angle.h"
#include "3Dgraphics/mesh.h"
#include "3Dgraphics/pixel.h"
#include "3Dgraphics/scene.h"

namespace raylib {	// defined within namespace so names don't clash with graphics
#include <raylib.h>
}

#define TARGET_FPS 30
#define CAM_MOVE_SPEED .2f
#define CAM_ROTATION_SPEED .4f
#define WINDOW_NAME "Graphics"

namespace graphics {

	Camera::Camera() {
		FOV = 0;
	}

	Camera::Camera(const Point& input_point, const Angle& input_rotation, value_type input_fov) {
		position = input_point;
		rotation = input_rotation;
		FOV = input_fov;
	}

	Camera::Camera(const Camera& input_camera) {
		position = input_camera.position;
		rotation = input_camera.rotation;
		FOV = input_camera.FOV;
	}

	bool Camera::isValid() const {
		return rotation.isValid();
	}

	void Camera::renderCamera(int screenWidth, int screenHeight, Scene& scene_input) {

		// Window initialization
		raylib::InitWindow(screenWidth, screenHeight, WINDOW_NAME);
		raylib::SetTargetFPS(TARGET_FPS);

		// Main loop
		while (!raylib::WindowShouldClose())
		{

			std::vector<Pixel> frame(screenWidth * screenHeight, Pixel{ scene_input.backgroundColor });	// initalize frame vector; set the default pixel to the background color defined in scene object
			renderFrame(frame, screenWidth, screenHeight, scene_input);	// render camera to frame vector
			raylib::ClearBackground(raylib::BLACK);
			raylib::BeginDrawing();

			// Draws frame onto screen
			for (int y = 0; y < screenHeight; y++) {
				for (int x = 0; x < screenWidth; x++) {
					raylib::DrawPixel(x, y, raylib::GetColor((frame.at(y * screenWidth + x).hex << 8) | 0xff));	// raylib color is formatted as 0xRRGGBBAA; need to bitshift to add the alpha channel
				}
				std::cout << std::endl;
			}

			userMoveCamera(CAM_MOVE_SPEED);
			userRotateCamera(CAM_ROTATION_SPEED);
			userSceneControl(scene_input);

			raylib::EndDrawing();
		}
	}

	void Camera::renderFrame(std::vector<Pixel>& frame, int screenWidth, int screenHeight, Scene& scene_input) const {

		if (!isValid()) { return; }

		value_type horizontalFOV = FOV;
		value_type verticalFOV = FOV;
		(screenWidth > screenHeight) ? (verticalFOV *= (static_cast<float>(screenHeight) / screenWidth)) : (horizontalFOV *= (static_cast<float>(screenWidth) / screenHeight));	// truncates the FOV for the shorest axis (truncates either the xFOV or yFOV)

		value_type tempI;
		Point tempPoint;
		Line ray;

		Vector camVector{ 1, 0, 0 };	// calculates camera vector, used for calculating roll
		camVector.rotateAroundAxis(Vector{ 0, 1, 0 }, rotation.pitch);
		camVector.rotateAroundAxis(Vector{ 0, 0, 1 }, rotation.yaw);

		// Caches world space polygons before use
		for (int i = 0; i < scene_input.meshCollection.size(); i++) {

			scene_input.meshCollection.at(i).updateWorldSpacePolygonCollection();

		}

		for (int y = 0; y < screenHeight; y++) {
			for (int x = 0; x < screenWidth; x++) {

				// Calculate ray (with no rotation)
				ray.directionVector.x = (screenWidth / 2) + tan(horizontalFOV / 2);
				ray.directionVector.y = (screenWidth / 2) - x;
				ray.directionVector.z = (screenHeight / 2) - y;
				ray.pointOnLine = position;

				// Rotate ray vector (rotation for camera works different than standard vector rotation)
				ray.directionVector.rotateAroundAxis(Vector{ 0, 1, 0 }, rotation.pitch);
				ray.directionVector.rotateAroundAxis(Vector{ 0, 0, 1 }, rotation.yaw);
				ray.directionVector.rotateAroundAxis(camVector, rotation.roll);

				// Renders grid if enabled
				if (scene_input.renderGrid) {

					Plane groundPlane({ 0, 0, 0 }, { 1, 0, 0 }, { 0, -1, 0 });
					groundPlane.intersectionPoint(ray, tempPoint, &tempI);

					float gridWidth = 1 / ((screenWidth / 2) + tan(horizontalFOV / 2)) * tempPoint.distance(position);	// idealy the grid should be 1px thick, but in practice this is difficult and expensive to implement.  This solution is not perfect, but very cheap

					unsigned int gridColor = 0x555555;
					unsigned int gridXColor = 0x005500;
					unsigned int gridYColor = 0x550000;

					if (std::abs(std::fmod(tempPoint.x, 1.0)) < gridWidth && tempI > 0) { frame.at((screenWidth * y) + x).hex = gridColor; frame.at((screenWidth * y) + x).zBuffer = tempI; }	// Renders grey x axis of grid
					if (std::abs(std::fmod(tempPoint.y, 1.0)) < gridWidth && tempI > 0) { frame.at((screenWidth * y) + x).hex = gridColor; frame.at((screenWidth * y) + x).zBuffer = tempI; }	// Renders grey y axis of grid
					if (std::abs(tempPoint.x) < gridWidth && tempI > 0) { frame.at((screenWidth * y) + x).hex = gridXColor; frame.at((screenWidth * y) + x).zBuffer = tempI; }	// Renders green x axis of grid
					if (std::abs(tempPoint.y) < gridWidth && tempI > 0) { frame.at((screenWidth * y) + x).hex = gridYColor; frame.at((screenWidth * y) + x).zBuffer = tempI; }	// Renders red y axis of grid

				}

				// Renders scene
				for (int i = 0; i < scene_input.meshCollection.size(); i++) {	// Iterate each mesh in scene

					Mesh* currentMesh = &(scene_input.meshCollection.at(i));

					if (!currentMesh->isValid()) { continue; }

					for (int j = 0; j < currentMesh->worldSpacePolygonCollection.size(); j++) {	// Iterate each polygon in mesh
						// For each pixel, will fill the appropriate value in the given frame vector IF there is intersection, if the intersection is infront (tempI > 0), and if the intersection is closer than the last zBuffer
						if (currentMesh->worldSpacePolygonCollection.at(j).intersectionPoint(ray, tempPoint, &tempI) && tempI > 0 && tempI < frame.at((screenWidth * y) + x).zBuffer) {

							frame.at((screenWidth * y) + x).hex = currentMesh->material.shade(ray, tempPoint, currentMesh->worldSpacePolygonCollection.at(j));	// call the material to shade to the pixel
							frame.at((screenWidth * y) + x).zBuffer = tempI;	// update the zBuffer
						}
					}
				}
			}
		}
	}

	void Camera::userMoveCamera(float speed_input) {

		if (raylib::IsKeyDown(raylib::KEY_LEFT_SHIFT)) { speed_input *= 3; }

		if (raylib::IsKeyDown(raylib::KEY_W)) {
			Vector direction { speed_input, 0 ,0 };

			direction.rotateAroundAxis(Vector{ 0, 1, 0 }, rotation.pitch);
			direction.rotateAroundAxis(Vector{ 0, 0, 1 }, rotation.yaw);

			position.x += direction.x;
			position.y += direction.y;
			position.z += direction.z;
		}

		if (raylib::IsKeyDown(raylib::KEY_A)) {
			Vector direction{ 0, speed_input ,0 };

			direction.rotateAroundAxis(Vector{ 0, 1, 0 }, rotation.pitch);
			direction.rotateAroundAxis(Vector{ 0, 0, 1 }, rotation.yaw);

			position.x += direction.x;
			position.y += direction.y;
			position.z += direction.z;
		}

		if (raylib::IsKeyDown(raylib::KEY_S)) {
			Vector direction{ -speed_input, 0 ,0 };

			direction.rotateAroundAxis(Vector{ 0, 1, 0 }, rotation.pitch);
			direction.rotateAroundAxis(Vector{ 0, 0, 1 }, rotation.yaw);

			position.x += direction.x;
			position.y += direction.y;
			position.z += direction.z;
		}

		if (raylib::IsKeyDown(raylib::KEY_D)) {
			Vector direction{ 0, -speed_input ,0 };

			direction.rotateAroundAxis(Vector{ 0, 1, 0 }, rotation.pitch);
			direction.rotateAroundAxis(Vector{ 0, 0, 1 }, rotation.yaw);

			position.x += direction.x;
			position.y += direction.y;
			position.z += direction.z;
		}

		if (raylib::IsKeyDown(raylib::KEY_SPACE)) { position.z += speed_input; }
		if (raylib::IsKeyDown(raylib::KEY_LEFT_CONTROL)) { position.z -= speed_input; }

	}

	void Camera::userRotateCamera(float speed_input) {

		if (raylib::IsKeyDown(raylib::KEY_UP)) { rotation.pitch -= .1; }
		if (raylib::IsKeyDown(raylib::KEY_DOWN)) { rotation.pitch += .1; }
		if (raylib::IsKeyDown(raylib::KEY_RIGHT)) { rotation.yaw -= .1; }
		if (raylib::IsKeyDown(raylib::KEY_LEFT)) { rotation.yaw += .1; }
		if (raylib::IsKeyDown(raylib::KEY_E)) { rotation.roll += .1; }
		if (raylib::IsKeyDown(raylib::KEY_Q)) { rotation.roll -= .1; }

	}

	void Camera::userSceneControl(Scene& scene_input) {

		if (raylib::IsKeyPressed(raylib::KEY_F)) { scene_input.renderGrid = !scene_input.renderGrid; }

	}
}