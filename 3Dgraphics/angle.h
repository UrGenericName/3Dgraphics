#pragma once
#include "point.h"
#include "vector.h"

namespace graphics {

	class Angle
	{
	public:
		Angle(value_type input_pitch = 0, value_type input_yaw = 0, value_type input_roll = 0);
		Angle(const Angle& input_angle);
		Angle(const Vector& directionVector);

		Angle operator+(const Angle& angle_input) const;
		Angle operator-(const Angle& angle_input) const;
		Angle& operator=(const Angle& angle_input);
		bool operator==(const Angle& angle_input) const;

		bool isValid() const;
		void angleFromVector(const Vector& directionVector);
		void vectorFromAngle(Vector& output_vector) const;
		void print() const;

		value_type pitch, yaw, roll;	// Everything done in radians
	};

}