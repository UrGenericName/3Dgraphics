#pragma once
#include <vector>
#include "angle.h"
#include "mesh.h"
#include "pixel.h"
#include "scene.h"

namespace graphics {

	class Camera
	{
	public:
		Camera();
		Camera(const Point& input_point, const Angle& input_rotation, value_type input_fov);
		Camera(const Camera& input_camera);

		bool isValid() const;
		void renderCamera(std::vector<Pixel>& screen, int screenWidth, int screenHeight, Scene& scene_polygon) const;

		Point position;
		Angle rotation;
		value_type FOV;
	};

}