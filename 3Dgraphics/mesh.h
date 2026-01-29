#pragma once
#include <vector>
#include "point.h"
#include "angle.h"
#include "polygon.h"
#include "material.h"
#include "shaders.h"

namespace graphics {

	class Mesh
	{
	public:

		Mesh();

		bool isValid() const;
		
		Point position;
		Angle rotation;
		Material material;
		std::vector<Polygon> polygonCollection;
	};
}