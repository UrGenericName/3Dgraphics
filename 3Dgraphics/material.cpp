#pragma once
#include <vector>
#include "material.h"
#include "mesh.h"
#include "vector.h"

namespace graphics {
	Material::Material() {}

	// Chooses which private shade function to call based on the shader variable
	unsigned int Material::shade(Line& ray_input, Point& intersection_point, Polygon& polygon_input) const {

		switch (shader) {

			case shaders::flat:
				return shadeFlat(ray_input, intersection_point, polygon_input);

			case shaders::physics:
				return shadePhysics(ray_input, intersection_point, polygon_input);
		}
	}

	// Simple flat shader, just returns the color specified in the object (this is the default shader)
	unsigned int Material::shadeFlat(Line& ray_input, Point& intersection_point, Polygon& polygon_input) const {
		return color;
	}

	// Greyscale shader which shades the polygon based on the angle
	unsigned int Material::shadePhysics(Line& ray_input, Point& intersection_point, Polygon& polygon_input) const {

		float tempDot = ray_input.directionVector.dotProduct(*polygon_input.normalVector());	// determines the dot product of the polygon normal and ray vector
		unsigned int illumination = std::abs(tempDot) * 255;

		return (illumination << 16) | (illumination << 8) | (illumination);	// takes the illumination and converts it to 0xRRGGBB
	}
}