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

	void Angle::print() const {
		std::cout << "(pitch, yaw, roll) in degrees: " << pitch * 180 / constants::PI << ", " << yaw * 180 / constants::PI << ", " << roll * 180 / constants::PI << std::endl;
		std::cout << "				  ...in radians: " << pitch << ", " << yaw << ", " << roll << std::endl;
	}
}