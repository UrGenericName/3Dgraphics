#pragma once
#include <iostream>
#include <chrono>

#include <thread>
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

		std::vector<raylib::Color> frameBuffer(screenHeight * screenWidth);
		raylib::Image img = raylib::GenImageColor(screenWidth, screenHeight, raylib::GetColor(scene_input.backgroundColor));
		raylib::Texture2D tex = raylib::LoadTextureFromImage(img);
		raylib::UnloadImage(img);

		// Main loop
		while (!raylib::WindowShouldClose())
		{
			renderFrame(frameBuffer, screenWidth, screenHeight, scene_input);

			userMoveCamera(CAM_MOVE_SPEED);
			userRotateCamera(CAM_ROTATION_SPEED);
			userSceneControl(scene_input);

			raylib::UpdateTexture(tex, frameBuffer.data());
			raylib::BeginDrawing();
			raylib::ClearBackground(raylib::GetColor(scene_input.backgroundColor));
			raylib::DrawTexture(tex, 0, 0, raylib::WHITE);
			raylib::EndDrawing();
		}
	}

	void Camera::renderFrame(std::vector<raylib::Color>& frameBuffer, int screenWidth, int screenHeight, Scene& scene_input) {

		if (!isValid()) { return; }

		value_type horizontalFOV = FOV;
		value_type verticalFOV = FOV;
		(screenWidth > screenHeight) ? (verticalFOV *= (static_cast<float>(screenHeight) / screenWidth)) : (horizontalFOV *= (static_cast<float>(screenWidth) / screenHeight));	// truncates the FOV for the shorest axis (truncates either the xFOV or yFOV)

		Vector camVector{ 1, 0, 0 };	// calculates camera vector, used for calculating roll
		camVector.rotateAroundAxis(Vector{ 0, 1, 0 }, rotation.pitch);
		camVector.rotateAroundAxis(Vector{ 0, 0, 1 }, rotation.yaw);

		// Caches world space polygons before use
		for (int i = 0; i < scene_input.meshCollection.size(); i++) {

			scene_input.meshCollection[i].updateWorldSpacePolygonCollection();

		}

		// MULTI-THREADING
		std::vector<std::thread> threads;
		unsigned int threadCount = std::thread::hardware_concurrency();
		int pixelsPerThread = (screenWidth * screenHeight) / threadCount;

		// Calculate a group of pixel for each thread
		for (int i = 0; i < threadCount; i++) {

			// for thread i, render a specific group of pixels
			threads.push_back(std::thread([&, i]() {

				renderPixelGroup(frameBuffer, pixelsPerThread, i, screenWidth, screenHeight, scene_input, camVector, horizontalFOV, verticalFOV);

			}));

		}

		// Wait for all them to join back
		for (auto& t : threads) {
			t.join();
		}
	}

	// Used for multithreading
	void Camera::renderPixelGroup(std::vector<raylib::Color>& frameBuffer, int pixelsPerThread, int threadIndex, int screenWidth, int screenHeight, Scene& scene_input, Vector &camVector, value_type horizontalFOV, value_type verticalFOV) {
		
		int startPixel = threadIndex * pixelsPerThread;
		for (int i = 0; i < pixelsPerThread; i++) {

			int x = (i + startPixel) % screenWidth;
			int y = (i + startPixel) / screenWidth;
			renderPixel(frameBuffer, x, y, screenWidth, screenHeight, scene_input, camVector, horizontalFOV, verticalFOV);
		}

	}

	void Camera::renderPixel(std::vector<raylib::Color>& frameBuffer, int x, int y, int screenWidth, int screenHeight, Scene& scene_input, Vector& camVector, value_type horizontalFOV, value_type verticalFOV) {

		value_type tempI;
		Point tempPoint;
		Line ray;
		Pixel currentPixel;

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
			calculateGrid(screenWidth, horizontalFOV, verticalFOV, currentPixel, ray, tempPoint, tempI);
		}

		Mesh* meshToBeShaded = nullptr;
		Polygon* polygonToBeShaded = nullptr;
		Point pointToBeShaded;
		value_type tempIToBeShaded;

		// Renders scene
		for (int i = 0; i < scene_input.meshCollection.size(); i++) {	// Iterate each mesh in scene

			Mesh* currentMesh = &(scene_input.meshCollection[i]);

			if (!currentMesh->isValid()) { continue; }

			for (int j = 0; j < currentMesh->worldSpacePolygonCollection.size(); j++) {	// Iterate each polygon in mesh
				// For each pixel, will fill the appropriate value in the given frame vector IF there is intersection, if the intersection is infront (tempI > 0), and if the intersection is closer than the last zBuffer
				if (currentMesh->worldSpacePolygonCollection[j].intersectionPoint(ray, tempPoint, &tempI) && tempI > 0 && tempI < currentPixel.zBuffer) {

					// Store the mesh so the material shading can be done outside the loop
					meshToBeShaded = currentMesh;
					polygonToBeShaded = &currentMesh->worldSpacePolygonCollection[j];
					pointToBeShaded = tempPoint;
					tempIToBeShaded = tempI;

					currentPixel.zBuffer = tempI;	// update the zBuffer
				}
			}
		}

		if (meshToBeShaded != nullptr) {
			currentPixel.hex = meshToBeShaded->material.shade(ray, tempPoint, *polygonToBeShaded);	// call the material to shade to the pixel
		}

		// Store hex value to frameBuffer vector
		frameBuffer[y * (screenWidth) + x] = raylib::GetColor((currentPixel.hex << 8) | 0xff);	// raylib color is formatted as 0xRRGGBBAA; need to bitshift to add the alpha channel
	}

	void Camera::calculateGrid(int& screenWidth, value_type& horizontalFOV, value_type& verticalFOV, Pixel& pixel, Line& ray, Point& intersectionPoint, value_type& tempI) const {

		Plane groundPlane({ 0, 0, 0 }, { 1, 0, 0 }, { 0, -1, 0 });
		groundPlane.intersectionPoint(ray, intersectionPoint, &tempI);

		float gridWidth = 1 / ((screenWidth / 2) + tan(horizontalFOV / 2)) * intersectionPoint.distance(position);	// idealy the grid should be 1px thick, but in practice this is difficult and expensive to implement.  This solution is not perfect, but very cheap

		unsigned int gridColor = 0x555555;
		unsigned int gridXColor = 0x005500;
		unsigned int gridYColor = 0x550000;

		// weird way to avoid using fmod because fmod is expensive
		value_type intersectionPointXModOne = intersectionPoint.x - (long)intersectionPoint.x;
		value_type intersectionPointYModOne = intersectionPoint.y - (long)intersectionPoint.y;

		if (std::abs(intersectionPointXModOne) < gridWidth && tempI > 0) { pixel.hex = gridColor; pixel.zBuffer = tempI; }	// Renders grey x axis of grid
		if (std::abs(intersectionPointYModOne) < gridWidth && tempI > 0) { pixel.hex = gridColor; pixel.zBuffer = tempI; }	// Renders grey y axis of grid
		if (std::abs(intersectionPoint.x) < gridWidth && tempI > 0) { pixel.hex = gridXColor; pixel.zBuffer = tempI; }	// Renders green x axis of grid
		if (std::abs(intersectionPoint.y) < gridWidth && tempI > 0) { pixel.hex = gridYColor; pixel.zBuffer = tempI; }	// Renders red y axis of grid
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