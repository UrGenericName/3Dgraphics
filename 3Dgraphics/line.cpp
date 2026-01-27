#pragma once
#include "line.h"
#include <iostream>

namespace graphics {
	Line::Line() {}

	Line::Line(const Line& line_input) {
		pointOnLine = line_input.pointOnLine;
		directionVector = line_input.directionVector;
	}

	Line::Line(const Point &point_input, const Vector &vector_input) {
		pointOnLine = point_input;
		directionVector = vector_input;
	}

	Line::Line(const Point& pointA_input, const Point& pointB_input) {
		pointOnLine = pointA_input;

		// Vector from two points
		directionVector.x = (pointB_input.x - pointA_input.x);
		directionVector.y = (pointB_input.y - pointA_input.y);
		directionVector.z = (pointB_input.z - pointA_input.z);
	}

	Line& Line::operator=(const Line& line_input) {
		pointOnLine = line_input.pointOnLine;
		directionVector = line_input.directionVector;

		return *this;
	}

	bool Line::operator!=(const Line& line_input) const {
		return (pointOnLine != line_input.pointOnLine) || (directionVector != line_input.directionVector);
	}

	bool Line::operator==(const Line& line_input) const {
		return (pointOnLine == line_input.pointOnLine) && (directionVector == line_input.directionVector);
	}

	bool Line::isValid() const {
		return (directionVector.isValid());
	}

	bool Line::pointFromT(double input_t, Point& point_output) const {

		if (!isValid()) { return false; }

		point_output.x = pointOnLine.x + (input_t * directionVector.x);
		point_output.y = pointOnLine.y + (input_t * directionVector.y);
		point_output.z = pointOnLine.z + (input_t * directionVector.z);

		return true;
	}

	// Returns false if intersection point does not exist or is overlapping, otherwise overrides point_output and returns true
	bool Line::intersectionPoint(const Line& line_input, Point& point_output) const {

		// Return false if vectors are null
		if (!directionVector.isValid() || !line_input.directionVector.isValid()) { return false; }

		Vector vectorA(directionVector);
		Vector vectorB(line_input.directionVector);

		vectorA.normalize();
		vectorB.normalize();

		// If lines are parallel return false
		if (vectorA == vectorB) { return false; }

		// EQUATION FOR INTERSECTION: t = ( <x1, y1, z1> - <x2, y2, z2>) / (<a2, b2, c2> - <a1, b1, c1>)
		// divison is a problem here; vectors cannot technically do division and theres a chance for an undefined component

		double tx = (pointOnLine.x - line_input.pointOnLine.x) / (line_input.directionVector.x - directionVector.x);
		double ty = (pointOnLine.y - line_input.pointOnLine.y) / (line_input.directionVector.y - directionVector.y);
		double tz = (pointOnLine.z - line_input.pointOnLine.z) / (line_input.directionVector.z - directionVector.z);

		// For simplicity, if t == 0 then just assign it to no value
		if (line_input.directionVector.x - directionVector.x == 0) { tx = std::nanf(""); }
		if (line_input.directionVector.y - directionVector.y == 0) { ty = std::nanf(""); }
		if (line_input.directionVector.z - directionVector.z == 0) { tz = std::nanf(""); }

		// Points do not intersect if t's do not match (skip undefined t's)
		if (!std::isnan(tx) && !std::isnan(ty) && tx != ty) { return false; }
		if (!std::isnan(ty) && !std::isnan(tz) && ty != tz) { return false; }
		if (!std::isnan(tz) && !std::isnan(tx) && tz != tx) { return false; }

		// For undefined t's, point intersection may still be true if x1 == x2 == 0 (same applies for y and z)
		if (std::isnan(tx) && (pointOnLine.x != 0 || line_input.pointOnLine.x != 0)) { return false; }
		if (std::isnan(ty) && (pointOnLine.y != 0 || line_input.pointOnLine.y != 0)) { return false; }
		if (std::isnan(tz) && (pointOnLine.z != 0 || line_input.pointOnLine.z != 0)) { return false; }

		// If program makes it to this point, intersection does exist
		double finalT;
		if (!std::isnan(tx)) { finalT = tx; }
		if (!std::isnan(ty)) { finalT = ty; }
		if (!std::isnan(tz)) { finalT = tz; }

		// Override intersection point
		pointFromT(finalT, point_output);
		return true;
	}
}