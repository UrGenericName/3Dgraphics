#pragma once
#include "scene.h"

namespace graphics {
	Scene::Scene() {}

	Scene::Scene(const Scene& scene_input) {
		meshCollection = scene_input.meshCollection;
	}

	bool Scene::isValid() const {
		return !meshCollection.empty();
	}

}