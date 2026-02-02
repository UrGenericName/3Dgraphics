#pragma once
#include "vector.h"
#include "angle.h"
#include <cmath>
#include <iostream>

namespace graphics {
	Vector::Vector(const Vector& vector_input) {
		x = vector_input.x;
		y = vector_input.y;
		z = vector_input.z;
	}

	Vector::Vector(value_type x_input, value_type y_input, value_type z_input) {
		x = x_input;
		y = y_input;
		z = z_input;
	}

	Vector::Vector(const Point &point_input) {
		x = point_input.x;
		y = point_input.y;
		z = point_input.z;
	}

	Vector Vector::operator+(const Vector& vector_input) const {
		Vector result;
		result.x = x + vector_input.x;
		result.y = y + vector_input.y;
		result.z = z + vector_input.z;

		return result;
	}

	Vector Vector::operator-(const Vector& vector_input) const {
		Vector result;
		result.x = x - vector_input.x;
		result.y = y - vector_input.y;
		result.z = z - vector_input.z;

		return result;
	}

	Vector Vector::operator*(const Vector& vector_input) const {
		Vector result;
		result.x = x * vector_input.x;
		result.y = y * vector_input.y;
		result.z = z * vector_input.z;

		return result;
	}

	Vector Vector::operator/(const Vector& vector_input) const {
		Vector result;
		result.x = x / vector_input.x;
		result.y = y / vector_input.y;
		result.z = z / vector_input.z;

		return result;
	}

	Vector& Vector::operator=(const Vector& vector_input) {
		x = vector_input.x;
		y = vector_input.y;
		z = vector_input.z;

		return *this;
	}

	Vector& Vector::operator=(const Point& point_input) {
		x = point_input.x;
		y = point_input.y;
		z = point_input.z;

		return *this;
	}

	bool Vector::operator!=(const Vector& vector_input) const {
		return (x != vector_input.x) || (y != vector_input.y) || (z != vector_input.z);
	}

	bool Vector::operator==(const Vector& vector_input) const {
		return (x == vector_input.x) && (y == vector_input.y) && (z == vector_input.z);
	}

	bool Vector::isValid() const {
		return !(x == 0 && y == 0 && z == 0);
	}

	void Vector::rotate(const Angle& rotation_input) {

		// --- Rotate around global Z (yaw) ---
		value_type tempX = x;
		value_type tempY = y;
		x = tempX * cos(rotation_input.yaw) - tempY * sin(rotation_input.yaw);
		y = tempX * sin(rotation_input.yaw) + tempY * cos(rotation_input.yaw);

		// --- Rotate around global Y (pitch) ---
		tempX = x;
		value_type tempZ = z;
		x = tempX * cos(rotation_input.pitch) + tempZ * sin(rotation_input.pitch);
		z = -tempX * sin(rotation_input.pitch) + tempZ * cos(rotation_input.pitch);

		// --- Rotate around global X (roll) ---
		tempY = y;
		tempZ = z;
		y = tempY * cos(rotation_input.roll) - tempZ * sin(rotation_input.roll);
		z = tempY * sin(rotation_input.roll) + tempZ * cos(rotation_input.roll);


	}

	void Vector::rotateAroundAxis(const Vector& axis_input, value_type angle_input) {
		Vector k = axis_input;
		k.normalize();

		Vector v = *this; // save original vector

		Vector kCrossV;
		kCrossV.crossProduct(k, v);
		value_type kDotV = k.dotProduct(v);

		value_type tempCos = cos(angle_input);
		value_type tempSin = sin(angle_input);

		// Rodrigues formula
		x = v.x * tempCos + kCrossV.x * tempSin + k.x * kDotV * (1 - tempCos);
		y = v.y * tempCos + kCrossV.y * tempSin + k.y * kDotV * (1 - tempCos);
		z = v.z * tempCos + kCrossV.z * tempSin + k.z * kDotV * (1 - tempCos);
	}


	void Vector::crossProduct(const Vector vectorA_input, const Vector vectorB_input) {
		x = (vectorA_input.y * vectorB_input.z) - (vectorA_input.z * vectorB_input.y);
		y = (vectorA_input.z * vectorB_input.x) - (vectorA_input.x * vectorB_input.z);
		z = (vectorA_input.x * vectorB_input.y) - (vectorA_input.y * vectorB_input.x);
	}

	value_type Vector::dotProduct(const Vector& vector_input) const {
		return (x * vector_input.x) + (y * vector_input.y) + (z * vector_input.z);
	}

	value_type Vector::getMagnitude() const {
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}

	// returns false if not valid vector
	bool Vector::normalize() {

		if (!isValid()) { return false; }

		float magnitude = getMagnitude();

		x /= magnitude;
		y /= magnitude;
		z /= magnitude;

		return true;
	}

	void Vector::print() const {
		std::cout << "<x, y, z>: " << x << ", " << y << ", " << z << std::endl;
	}
}