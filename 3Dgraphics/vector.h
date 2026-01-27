#pragma once
#include "point.h"

namespace graphics {

	class Vector
	{
	public:
		Vector(const Vector& vector_input);	// Copy constructor
		Vector(value_type x_input = 0, value_type y_input = 0, value_type z_input = 0);
		Vector(const Point& point_input);

		Vector operator+(const Vector& vector_input) const;
		Vector operator-(const Vector& vector_input) const;
		Vector& operator=(const Vector& vector_input);
		Vector& operator=(const Point& point_input);
		bool operator!=(const Vector& vector_input) const;
		bool operator==(const Vector& vector_input) const;

		bool isValid() const;
		void crossProduct(const Vector vectorA_input, const Vector vectorB_input);
		value_type dotProduct(const Vector& vector_input) const;
		value_type getMagnitude() const;
		bool normalize();
		void print() const;

		value_type x, y, z;
	};
}