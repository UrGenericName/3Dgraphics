#pragma once
#include <vector>
#include "angle.h"
#include "mesh.h"
#include "pixel.h"
#include "scene.h"

namespace raylib {	// defined within namespace so names don't clash with graphics
	#include <raylib.h>
}

namespace graphics {

	class Camera
	{
	public:
		Camera();
		Camera(const Point& input_point, const Angle& input_rotation, value_type input_fov);
		Camera(const Camera& input_camera);

		bool isValid() const;
		void renderCamera(int screenWidth, int screenHeight, Scene& scene_polygon);

		Point position;
		Angle rotation;
		value_type FOV;

	private:
		void renderFrame(std::vector<raylib::Color>& frameBuffer, int screenWidth, int screenHeight, Scene& scene_polygon);
		void renderPixelGroup(std::vector<raylib::Color>& frameBuffer, int pixelsPerThread, int threadIndex, int screenWidth, int screenHeight, Scene& scene_input, Vector& camVector, value_type horizontalFOV, value_type verticalFOV);
		void renderPixel(std::vector<raylib::Color>& frameBuffer, int x, int y, int screenWidth, int screenHeight, Scene& scene_input, Vector& camVector, value_type horizontalFOV, value_type verticalFOV);
		void calculateGrid(int& screenWidth, value_type& horizontalFOV, value_type& verticalFOV, Pixel& pixel, Line& ray, Point& intersectionPoint, value_type& tempI) const;
		void userMoveCamera(float speed_input);
		void userRotateCamera(float speed_input);
		void userSceneControl(Scene& scene_input);
	};

}