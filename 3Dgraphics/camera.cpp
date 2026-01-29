#pragma once
#include <cmath>
#include <iostream>
#include "camera.h"
#include "angle.h"
#include "mesh.h"
#include "pixel.h"
#include "scene.h"

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

	void Camera::renderCamera(std::vector<Pixel>& frame, int screenWidth, int screenHeight, Scene& scene_input) const {

		if (!isValid()) { return; }

		double tempI;
		Point tempPoint;
		Vector tempVector;
		Angle tempAngle;
		Line tempRay;
		tempRay.pointOnLine = position;

		value_type horizontalFOV = FOV;
		value_type verticalFOV = FOV;
		(screenWidth > screenHeight) ? (verticalFOV *= (static_cast<float>(screenHeight) / screenWidth)) : (horizontalFOV *= (static_cast<float>(screenWidth) / screenHeight));	// truncates the FOV for the shorest axis (truncates either the xFOV or yFOV)

		for (int y = 0; y < screenHeight; y++) {
			tempAngle.pitch = (verticalFOV / 2) - (verticalFOV * (static_cast<float>(y) / (screenHeight - 1))) + rotation.pitch;

			for (int x = 0; x < screenWidth; x++) {
				// Calculate ray
				tempAngle.yaw = (horizontalFOV / 2) - (horizontalFOV * (static_cast<float>(x) / (screenWidth - 1))) + rotation.yaw;
				tempAngle.vectorFromAngle(tempVector);
				tempRay.directionVector = tempVector;

				// Renders grid if enabled
				if (scene_input.renderGrid) {

					Plane groundPlane({ 0, 0, 0 }, { 1, 0, 0 }, { 0, -1, 0 });
					groundPlane.intersectionPoint(tempRay, tempPoint, &tempI);

					float gridWidth = 0.02;
					unsigned int gridColor = 0x555555;
					unsigned int gridXColor = 0x005500;
					unsigned int gridYColor = 0x550000;

					if (std::abs(std::fmod(tempPoint.x, 1.0)) < gridWidth && tempI > 0) { frame.at((screenWidth * y) + x).hex = gridColor; }	// Renders grey x axis of grid
					if (std::abs(std::fmod(tempPoint.y, 1.0)) < gridWidth && tempI > 0) { frame.at((screenWidth * y) + x).hex = gridColor; }	// Renders grey y axis of grid
					if (std::abs(tempPoint.x) < gridWidth && tempI > 0) { frame.at((screenWidth * y) + x).hex = gridXColor; }	// Renders green x axis of grid
					if (std::abs(tempPoint.y) < gridWidth && tempI > 0) { frame.at((screenWidth * y) + x).hex = gridYColor; }	// Renders red y axis of grid

				}

				// Renders scene
				for (int i = 0; i < scene_input.meshCollection.size(); i++) {	// Iterate each mesh in scene

					Mesh* currentMesh = &(scene_input.meshCollection.at(i));

					// Offsets the calculated ray to account for the mesh position
					Line tempRayOffset{ tempRay };
					tempRayOffset.pointOnLine = tempRayOffset.pointOnLine - currentMesh->position;

					if (!currentMesh->isValid()) { continue; }

					for (int j = 0; j < currentMesh->polygonCollection.size(); j++) {	// Iterate each polygon in mesh
						// For each pixel, will fill the appropriate value in the given frame vector IF there is intersection, if the intersection is infront (tempI > 0), and if the intersection is closer than the last zBuffer
						if (currentMesh->polygonCollection.at(j).intersectionPoint(tempRayOffset, tempPoint, &tempI) && tempI > 0 && tempI < frame.at((screenWidth * y) + x).zBuffer) {

							frame.at((screenWidth * y) + x).hex = currentMesh->material.shade(tempRayOffset, tempPoint, currentMesh->polygonCollection.at(j));	// call the material to shade to the pixel
							frame.at((screenWidth * y) + x).zBuffer = tempI;	// update the zBuffer
						}
					}
				}
			}
		}
	}
}