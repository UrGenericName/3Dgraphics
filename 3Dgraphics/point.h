#pragma once

namespace graphics {

	typedef double value_type;

	class Point 
	{
	public:
		Point(value_type x_input = 0, value_type y_input = 0, value_type z_input = 0);	// Default constructor
		Point(const Point& point_input);	// Copy constructor

		Point operator+(const Point& point_input) const;
		Point operator-(const Point& point_input) const;
		Point& operator=(const Point& point_input);
		bool operator!=(const Point& point_input) const;
		bool operator==(const Point& point_input) const;

		value_type distance(const Point& point_input) const;
		void print() const;

		value_type x, y, z;
	};
}