#pragma once
#include "mesh.h"

namespace graphics {
	Mesh::Mesh() {}

	bool Mesh::isValid() const {
		return !polygonCollection.empty();
	}
}