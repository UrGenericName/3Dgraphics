#pragma once
#include "mesh.h"

namespace graphics {
	Mesh::Mesh() {}

	Mesh::Mesh(const Mesh& mesh_input) {
		polygonCollection = mesh_input.polygonCollection;
	}

	bool Mesh::isValid() const {
		return !polygonCollection.empty();
	}
}