#pragma once
#include "point.h"
#include "vector.h"
#include "line.h"
#include "plane.h"

namespace graphics {

	class Triangle
	{
	public:
		Triangle();
		Triangle(const Triangle& triangle_input);	// Copy constructor
		Triangle(const Point& pointA_input, const Point& pointB_input, const Point& pointC_input);

		Triangle& operator=(const Triangle& triangle_input);
		bool operator!=(const Triangle& triangle_input) const;
		bool operator==(const Triangle& triangle_input) const;

		bool isValid() const;
		Point getPointA();
		Point getPointB();
		Point getPointC();
		void newPointA(Point& point_input);
		void newPointB(Point& point_input);
		void newPointC(Point& point_input);
		bool intersectionPoint(const Line& line_input, Point& point_output) const;

	private: // Do not want outside functions messing with these directly, they should use the provided public member functions

		void updateCachedData();

		Point pointA, pointB, pointC;

		//	Cached data
		Plane mainPlane;					// Plane which overlaps the triangle
		Plane planeAB, planeBC, planeCA;	// These planes are perpendicular to the main plane and define the borders of the triangle (like a cookie cutter); normals point inside
	};
}