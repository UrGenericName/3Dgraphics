#pragma once
#include <iostream>
#include "3Dgraphics/point.h"
#include "3Dgraphics/angle.h"

namespace graphics {
	Point::Point(value_type x_input, value_type y_input, value_type z_input) {
		x = x_input;
		y = y_input;
		z = z_input;
	}

	Point::Point(const Point& point_input) {
		x = point_input.x;
		y = point_input.y;
		z = point_input.z;
	}

	Point Point::operator+(const Point& point_input) const {
		Point result;
		result.x = x + point_input.x;
		result.y = y + point_input.y;
		result.z = z + point_input.z;

		return result;
	}

	Point Point::operator-(const Point& point_input) const {
		Point result;
		result.x = x - point_input.x;
		result.y = y - point_input.y;
		result.z = z - point_input.z;

		return result;
	}

	Point& Point::operator=(const Point& point_input) {
		x = point_input.x;
		y = point_input.y;
		z = point_input.z;

		return *this;
	}

	bool Point::operator!=(const Point& point_input) const {
		return (x != point_input.x) || (y != point_input.y) || (z != point_input.z);
	}

	bool Point::operator==(const Point& point_input) const {
		return (x == point_input.x) && (y == point_input.y) && (z == point_input.z);
	}

	value_type Point::distance(const Point& point_input) const {
		return sqrt(pow(x - point_input.x, 2) + pow(y - point_input.y, 2) + pow(z - point_input.z, 2));
	}

	void Point::rotate(const Angle& rotation_input) {

		// --- Rotate around global Z (yaw) ---
		value_type tempX = x;
		value_type tempY = y;
		x = tempX * cos(rotation_input.yaw) - tempY * sin(rotation_input.yaw);
		y = tempX * sin(rotation_input.yaw) + tempY * cos(rotation_input.yaw);

		// --- Rotate around global Y (pitch) ---
		tempX = x;
		value_type tempZ = z;
		x = tempX * cos(rotation_input.pitch) + tempZ * sin(rotation_input.pitch);
		z = -tempX * sin(rotation_input.pitch) + tempZ * cos(rotation_input.pitch);

		// --- Rotate around global X (roll) ---
		tempY = y;
		tempZ = z;
		y = tempY * cos(rotation_input.roll) - tempZ * sin(rotation_input.roll);
		z = tempY * sin(rotation_input.roll) + tempZ * cos(rotation_input.roll);


	}

	void Point::scale(value_type scale_input) {
		x *= scale_input;
		y *= scale_input;
		z *= scale_input;
	}

	void Point::print() const {
		std::cout << "(x, y, z): " << x << ", " << y << ", " << z << std::endl;
	}
}