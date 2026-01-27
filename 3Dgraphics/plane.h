#pragma once
#include "point.h"
#include "vector.h"
#include "line.h"

namespace graphics {

	class Plane
	{
	public:
		Plane();
		Plane(const Plane& plane_input);	// Copy constructor
		Plane(const Point& point_input, const Vector& normalVector_input);
		Plane(const Point& pointA_input, const Point& pointB_input, const Point& pointC_input);

		Plane& operator=(const Plane& plane_input);
		bool operator!=(const Plane& plane_input) const;
		bool operator==(const Plane& plane_input) const;

		bool isValid() const;
		bool planeInequality(const Point& point_input) const;
		bool intersectionPoint(const Line& line_input, Point& point_output) const;
		void print() const;

		// EQUATION: A(x - x0) + B(y - y0) + C(z - z0) = 0
		Vector normalVector;	// <a, b, c>
		Point pointOnPlane;		// <x0, y0, z0>
	};
}