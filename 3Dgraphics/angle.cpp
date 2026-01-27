#include "angle.h"
#include <cmath>
#include <iostream>
#include "constants.h"

namespace graphics {
	Angle::Angle(value_type input_pitch, value_type input_yaw, value_type input_roll) {
		pitch = input_pitch;
		yaw = input_yaw;
		roll = input_roll;
	}

	Angle::Angle(const Angle& input_angle) {
		pitch = input_angle.pitch;
		yaw = input_angle.yaw;
		roll = input_angle.roll;
	}

	Angle::Angle(const Vector& directionVector) {
		angleFromVector(directionVector);
	}

	Angle Angle::operator+(const Angle& angle_input) const {
		Angle result;
		result.pitch = pitch + angle_input.pitch;
		result.yaw = yaw + angle_input.yaw;
		result.roll = roll + angle_input.roll;

		return result;
	}

	Angle Angle::operator-(const Angle& angle_input) const {
		Angle result;
		result.pitch = pitch - angle_input.pitch;
		result.yaw = yaw - angle_input.yaw;
		result.roll = roll - angle_input.roll;

		return result;
	}

	Angle& Angle::operator=(const Angle& angle_input) {
		pitch = angle_input.pitch;
		yaw = angle_input.yaw;
		roll = angle_input.roll;

		return *this;
	}

	bool Angle::operator==(const Angle& angle_input) const {
		return (pitch == angle_input.pitch && yaw == angle_input.yaw && roll == angle_input.roll);
	}

	bool Angle::isValid() const {
		return !(std::isnan(pitch) || std::isnan(yaw) || std::isnan(roll));
	}

	void Angle::angleFromVector(const Vector& directionVector) {

		if (!directionVector.isValid()) { return; }

		Vector tempVector(directionVector);

		// Rotating a point on a 2D plane can be represented with this forumula:
		// < x*cos(theta) - y*sin(theta), x*sin(theta) + y*cos(theta)>
		// We basically just reverse engineer vectorFromAngle() by solving for theta

		// ROLL (We don't need roll)
		roll = 0;

		// YAW
		yaw = atan2(tempVector.y, tempVector.x);
		tempVector.x = sqrt(pow(tempVector.x, 2) + pow(tempVector.y, 2));	// Undos yaw on x so pitch can be correctly calculated

		// PITCH
		pitch = atan2(tempVector.z, tempVector.x);
	}

	// Overrides the given vector; performs better than return a pointer to a new Vector
	void Angle::vectorFromAngle(Vector& output_vector) const {

		if (!isValid()) { return; }

		// Rotating a point on a 2D plane can be represented with this forumula:
		// < x*cos(theta) - y*sin(theta), x*sin(theta) + y*cos(theta)>

		// PITCH (formula simplified; x input = 1, z input = 0)
		output_vector.x = cos(pitch);
		output_vector.z = sin(pitch);

		// YAW (formula simplified; y input = 0, x input is variable)
		value_type tempX = output_vector.x;
		output_vector.x = tempX * cos(yaw);
		output_vector.y = tempX * sin(yaw);

		// ROLL	(no formula simplifications; y & z inputs are variable)
		value_type tempY = output_vector.y;
		value_type tempZ = output_vector.z;
		output_vector.y = tempY * cos(roll) - tempZ * sin(roll);
		output_vector.z = tempY * sin(roll) + tempZ * cos(roll);

		output_vector.normalize();
	}

	void Angle::print() const {
		std::cout << "(pitch, yaw, roll) in degrees: " << pitch * 180 / constants::PI << ", " << yaw * 180 / constants::PI << ", " << roll * 180 / constants::PI << std::endl;
	}
}