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

		friend class Camera;

		bool isValid() const;
		
		Point position;
		Angle rotation;
		float scale = 1.f;
		Material material;
		std::vector<Polygon> polygonCollection;

	private:

		void updateWorldSpacePolygonCollection();
		std::vector<Polygon> worldSpacePolygonCollection;
	};
}