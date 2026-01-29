#pragma once
#include "polygon.h"
#include <iostream>

namespace graphics {
	Polygon::Polygon() {}

	Polygon::Polygon(const Polygon& polygon_input) {

		pointA = polygon_input.pointA;
		pointB = polygon_input.pointB;
		pointC = polygon_input.pointC;

		mainPlane = polygon_input.mainPlane;
		planeAB = polygon_input.planeAB;
		planeBC = polygon_input.planeBC;
		planeCA = polygon_input.planeCA;
	}

	Polygon::Polygon(const Point& pointA_input, const Point& pointB_input, const Point& pointC_input) {

		pointA = pointA_input;
		pointB = pointB_input;
		pointC = pointC_input;

		updateCachedData();
	}

	Polygon& Polygon::operator=(const Polygon& polygon_input) {
		pointA = polygon_input.pointA;
		pointB = polygon_input.pointB;
		pointC = polygon_input.pointC;

		mainPlane = polygon_input.mainPlane;
		planeAB = polygon_input.planeAB;
		planeBC = polygon_input.planeBC;
		planeCA = polygon_input.planeCA;

		return (*this);
	}

	bool Polygon::operator!=(const Polygon& polygon_input) const {
		return (pointA != polygon_input.pointA || pointB != polygon_input.pointB || pointC != polygon_input.pointC);
	}

	bool Polygon::operator==(const Polygon& polygon_input) const {
		return (pointA == polygon_input.pointA && pointB == polygon_input.pointB && pointC == polygon_input.pointC);
	}

	bool Polygon::isValid() const {
		return (mainPlane.isValid() && planeAB.isValid() && planeBC.isValid() && planeCA.isValid());
	}

	Point Polygon::getPointA() { return pointA; }
	Point Polygon::getPointB() { return pointB; }
	Point Polygon::getPointC() { return pointC; }

	void Polygon::newPointA(Point& input_point) { pointA = input_point; updateCachedData(); }
	void Polygon::newPointB(Point& input_point) { pointB = input_point; updateCachedData(); }
	void Polygon::newPointC(Point& input_point) { pointC = input_point; updateCachedData(); }

	// Overrides point_output with intersection point and returns true, returns false if not valid intersection
	bool Polygon::intersectionPoint(const Line& line_input, Point& point_output, double* t_output) const {

		if (!mainPlane.intersectionPoint(line_input, point_output, t_output)) { return false; }

		// If point is not within "cookie-cutter" then return false
		if (!planeAB.planeInequality(point_output)) { return false; }
		if (!planeBC.planeInequality(point_output)) { return false; }
		if (!planeCA.planeInequality(point_output)) { return false; }

		return true;
	}

	Vector* Polygon::normalVector() const {
		return (new Vector(mainPlane.normalVector));
	}

	// Updates the internal plane member variables based on the point A, B and C
	void Polygon::updateCachedData() {

		// return if points don't make up valid polygon
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