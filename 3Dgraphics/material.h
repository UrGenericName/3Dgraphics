#pragma once
#include "shaders.h"
#include "polygon.h"
#include "line.h"
#include "point.h"

namespace graphics {

	class Material
	{
	public:
		Material();

		unsigned int shade(Line& ray_input, Point& intersection_point, Polygon& polygon_input) const;

		unsigned int shader = shaders::flat;
		unsigned int color = 0xffffff;
	private:

		unsigned int shadeFlat(Line& ray_input, Point& intersection_point, Polygon& polygon_input) const;
		unsigned int shadePhysics(Line& ray_input, Point& intersection_point, Polygon& polygon_input) const;
	};
}