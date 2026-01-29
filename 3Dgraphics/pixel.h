#pragma once

#define FAR_CLIPPING_DISTANCE 9999

namespace graphics {

	struct Pixel {
		unsigned int hex;
		float zBuffer = FAR_CLIPPING_DISTANCE;
	};
}