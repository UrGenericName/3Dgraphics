#pragma once
#include "point.h"
#include <iostream>

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

	void Point::print() const {
		std::cout << "(x, y, z): " << x << ", " << y << ", " << z << std::endl;
	}
}