#pragma once
#include "point.h"
#include "vector.h"

namespace graphics {

	class Line
	{
	public:
		Line();
		Line(const Line& line_input);	// Copy constructor
		Line(const Point &point_input, const Vector &vector_input);
		Line(const Point &pointA_input, const Point &pointB_input);

		bool isValid() const;
		Line& operator=(const Line& line_input);
		bool operator!=(const Line& line_input) const;
		bool operator==(const Line& line_input) const;

		bool pointFromT(double input_t, Point& point_output) const;
		bool intersectionPoint(const Line& line_input, Point& point_output) const;

		// EQUATION: <x, y, z> = <x0, y0, z0} + t*<a, b, c>
		Point pointOnLine;
		Vector directionVector;
	};
}