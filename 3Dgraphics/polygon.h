#pragma once
#include "point.h"
#include "vector.h"
#include "line.h"
#include "plane.h"

namespace graphics {

	class Polygon
	{
	public:
		Polygon();
		Polygon(const Polygon& polygon_input);	// Copy constructor
		Polygon(const Point& pointA_input, const Point& pointB_input, const Point& pointC_input);

		Polygon& operator=(const Polygon& polygon_input);
		bool operator!=(const Polygon& polygon_input) const;
		bool operator==(const Polygon& polygon_input) const;

		bool isValid() const;
		Point getPointA();
		Point getPointB();
		Point getPointC();
		void newPointA(Point& point_input);
		void newPointB(Point& point_input);
		void newPointC(Point& point_input);
		bool intersectionPoint(const Line& line_input, Point& point_output, double* t_output = nullptr) const;
		Vector* normalVector() const;

	private: // Do not want outside functions messing with these directly, they should use the provided public member functions

		void updateCachedData();

		Point pointA, pointB, pointC;

		//	Cached data
		Plane mainPlane;					// Plane which overlaps the polygon
		Plane planeAB, planeBC, planeCA;	// These planes are perpendicular to the main plane and define the borders of the polygon (like a cookie cutter); normals point inside
	};
}