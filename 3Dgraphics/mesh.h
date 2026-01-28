#pragma once
#include <vector>
#include "polygon.h"

namespace graphics {

	class Mesh
	{
	public:

		Mesh();
		Mesh(const Mesh& mesh_input); // Copy constructor

		bool isValid() const;

		std::vector<Polygon> polygonCollection;
	};
}