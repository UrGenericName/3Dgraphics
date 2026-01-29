#pragma once
#include <vector>
#include "mesh.h"

namespace graphics {

	class Scene
	{
	public:

		Scene();
		Scene(const Scene& scene_input); // Copy constructor

		bool isValid() const;

		bool renderGrid = true;
		unsigned int backgroundColor = 0x000000;
		std::vector<Mesh> meshCollection;
	};
}