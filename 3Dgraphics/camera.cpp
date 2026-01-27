#include "camera.h"
#include <iostream>
#include "angle.h"
#include "triangle.h"

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

	void Camera::renderCamera(std::vector<bool>& screen, int screenWidth, int screenHeight, Triangle& input_triangle) const {

		if (!isValid()) { return; }

		Point tempPoint;
		Vector tempVector;
		Angle tempAngle;
		Line tempRay;
		tempRay.pointOnLine = position;

		value_type horizontalFOV = FOV;
		value_type verticalFOV = FOV;
		(screenWidth > screenHeight) ? (verticalFOV *= (static_cast<float>(screenHeight) / screenWidth)) : (horizontalFOV *= (static_cast<float>(screenWidth) / screenHeight));

		for (int y = 0; y < screenHeight; y++) {
			tempAngle.pitch = (verticalFOV / 2) - (verticalFOV * (static_cast<float>(y) / (screenHeight - 1))) + rotation.pitch;

			for (int x = 0; x < screenWidth; x++) {
				// Calculate ray
				tempAngle.yaw = (horizontalFOV / 2) - (horizontalFOV * (static_cast<float>(x) / (screenWidth - 1))) + rotation.yaw;
				tempAngle.vectorFromAngle(tempVector);
				tempRay.directionVector = tempVector;

				// Calculate intersection
				(input_triangle.intersectionPoint(tempRay, tempPoint)) ? (screen[((screenWidth - 1) * y) + x] = true) : (screen[((screenWidth - 1) * y) + x] = false);
			}
		}
	}
}