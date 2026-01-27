#pragma once
#include "triangle.h"
#include <iostream>

namespace graphics {
	Triangle::Triangle() {}

	Triangle::Triangle(const Triangle& triangle_input) {

		pointA = triangle_input.pointA;
		pointB = triangle_input.pointB;
		pointC = triangle_input.pointC;

		mainPlane = triangle_input.mainPlane;
		planeAB = triangle_input.planeAB;
		planeBC = triangle_input.planeBC;
		planeCA = triangle_input.planeCA;
	}

	Triangle::Triangle(const Point& pointA_input, const Point& pointB_input, const Point& pointC_input) {

		pointA = pointA_input;
		pointB = pointB_input;
		pointC = pointC_input;

		updateCachedData();
	}

	Triangle& Triangle::operator=(const Triangle& triangle_input) {
		pointA = triangle_input.pointA;
		pointB = triangle_input.pointB;
		pointC = triangle_input.pointC;

		mainPlane = triangle_input.mainPlane;
		planeAB = triangle_input.planeAB;
		planeBC = triangle_input.planeBC;
		planeCA = triangle_input.planeCA;

		return (*this);
	}

	bool Triangle::operator!=(const Triangle& triangle_input) const {
		return (pointA != triangle_input.pointA || pointB != triangle_input.pointB || pointC != triangle_input.pointC);
	}

	bool Triangle::operator==(const Triangle& triangle_input) const {
		return (pointA == triangle_input.pointA && pointB == triangle_input.pointB && pointC == triangle_input.pointC);
	}

	bool Triangle::isValid() const {
		return (mainPlane.isValid() && planeAB.isValid() && planeBC.isValid() && planeCA.isValid());
	}

	Point Triangle::getPointA() { return pointA; }
	Point Triangle::getPointB() { return pointB; }
	Point Triangle::getPointC() { return pointC; }

	void Triangle::newPointA(Point& input_point) { pointA = input_point; updateCachedData(); }
	void Triangle::newPointB(Point& input_point) { pointB = input_point; updateCachedData(); }
	void Triangle::newPointC(Point& input_point) { pointC = input_point; updateCachedData(); }

	// Overrides point_output with intersection point and returns true, returns false if not valid intersection
	bool Triangle::intersectionPoint(const Line& line_input, Point& point_output) const {

		if (!mainPlane.intersectionPoint(line_input, point_output)) { return false; }

		// If point is not within "cookie-cutter" then return false
		if (!planeAB.planeInequality(point_output)) { return false; }
		if (!planeBC.planeInequality(point_output)) { return false; }
		if (!planeCA.planeInequality(point_output)) { return false; }

		return true;
	}

	// Updates the internal plane member variables based on the point A, B and C
	void Triangle::updateCachedData() {

		// return if points don't make up valid triangle
		if (pointA == pointB || pointB == pointC || pointC == pointA) { return; }

		Vector tempVector;
		Vector vectorAB(pointA - pointB);
		Vector vectorBC(pointB - pointC);
		Vector vectorCA(pointC - pointA);

		// Caches main plain
		tempVector.crossProduct(vectorAB, vectorBC);
		mainPlane.normalVector = tempVector;
		mainPlane.pointOnPlane = pointA;

		// Cachces planeAB
		tempVector.crossProduct(vectorAB, vectorBC);
		tempVector.crossProduct(vectorAB, tempVector);
		planeAB.normalVector = tempVector;
		planeAB.pointOnPlane = pointA;

		// Caches planeBC
		tempVector.crossProduct(vectorBC, vectorCA);
		tempVector.crossProduct(vectorBC, tempVector);
		planeBC.normalVector = tempVector;
		planeBC.pointOnPlane = pointB;

		// Caches planeCA
		tempVector.crossProduct(vectorCA, vectorAB);
		tempVector.crossProduct(vectorCA, tempVector);
		planeCA.normalVector = tempVector;
		planeCA.pointOnPlane = pointC;
	}
}