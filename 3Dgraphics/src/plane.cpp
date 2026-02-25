#pragma once
#include "3Dgraphics/plane.h"
#include <iostream>

namespace graphics {
	Plane::Plane() {}

	Plane::Plane(const Plane& plane_input) {
		normalVector = plane_input.normalVector;
		pointOnPlane = plane_input.pointOnPlane;
	}

	Plane::Plane(const Point& point_input, const Vector& normalVector_input) {
		pointOnPlane = point_input;
		normalVector = normalVector_input;
	}

	Plane::Plane(const Point& pointA_input, const Point& pointB_input, const Point& pointC_input) {
		Vector vectorA(pointA_input - pointB_input);
		Vector vectorB(pointA_input - pointC_input);

		pointOnPlane = pointA_input;
		normalVector.crossProduct(vectorA, vectorB);
	}

	Plane& Plane::operator=(const Plane& plane_input) {
		normalVector = plane_input.normalVector;
		pointOnPlane = plane_input.pointOnPlane;

		return *this;
	}

	bool Plane::operator!=(const Plane& plane_input) const {
		return (normalVector != plane_input.normalVector) || (pointOnPlane != plane_input.pointOnPlane);
	}

	bool Plane::operator==(const Plane& plane_input) const {
		return (normalVector == plane_input.normalVector) && (pointOnPlane == plane_input.pointOnPlane);
	}

	bool Plane::isValid() const {
		return !(normalVector.x == 0 && normalVector.y == 0 && normalVector.z == 0);
	}

	// Determines where input point is relative to plane; returns true if plane normal is facing point, false if not.  Points intersecting plane should return false, but might be unpredictable
	bool Plane::planeInequality(const Point& point_input) const {
		return 0 < (normalVector.x * (point_input.x - pointOnPlane.x)) + (normalVector.y * (point_input.y - pointOnPlane.y)) + (normalVector.z * (point_input.z - pointOnPlane.z));
	}

	// Overrides point_output, returns false if no valid intersection
	bool Plane::intersectionPoint(const Line& line_input, Point& point_output, double* t_output) const {

		// Return false if plane normal is not valid
		if (!normalVector.isValid()) { return false; }

		// Return false if line vector is not valid
		if (!line_input.isValid()) { return false; }

		// If normal and line are orthongal, then there is no intersection
		if (normalVector.dotProduct(line_input.directionVector) == 0) { return false; }

		// Complex arithmetic equation to solve for t
		double tNumerator = (normalVector.x * (pointOnPlane.x - line_input.pointOnLine.x)) + (normalVector.y * (pointOnPlane.y - line_input.pointOnLine.y)) + (normalVector.z * (pointOnPlane.z - line_input.pointOnLine.z));
		double tDenominator = (normalVector.x * line_input.directionVector.x) + (normalVector.y * line_input.directionVector.y) + (normalVector.z * line_input.directionVector.z);
		double t = tNumerator / tDenominator;

		// If t_output is a given argument, then assign it with t
		if (t_output != nullptr) { *t_output = t; }

		line_input.pointFromT(t, point_output);
		return true;
	}

	void Plane::print() const {

		std::cout << "PLANE:" << std::endl;
		pointOnPlane.print();
		normalVector.print();
	}
}