#pragma once

namespace graphics {

	class Angle
	{
	public:
		Angle(float input_pitch = 0, float input_yaw = 0, float input_roll = 0);
		Angle(const Angle& input_angle);

		Angle operator+(const Angle& angle_input) const;
		Angle operator-(const Angle& angle_input) const;
		Angle& operator=(const Angle& angle_input);
		bool operator==(const Angle& angle_input) const;

		bool isValid() const;
		void print() const;

		float pitch, yaw, roll;	// Everything done in radians
	};

}