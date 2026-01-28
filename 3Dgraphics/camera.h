#pragma once
#include "angle.h"
#include "mesh.h"
#include <vector>

namespace graphics {

	class Camera
	{
	public:
		Camera();
		Camera(const Point& input_point, const Angle& input_rotation, value_type input_fov);
		Camera(const Camera& input_camera);

		bool isValid() const;
		void renderCamera(std::vector<bool>& screen, int screenWidth, int screenHeight, Mesh& mesh_polygon) const;

		Point position;
		Angle rotation;
		value_type FOV;
	};

}