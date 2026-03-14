#pragma once

#define FAR_CLIPPING_DISTANCE 9999

namespace graphics {

	struct Pixel {
		Pixel(unsigned int input_hex = 0) {
			hex = input_hex;
		}

		unsigned int hex;
		float zBuffer = FAR_CLIPPING_DISTANCE;
	};
}