#include "shape_presets.h"
#include "mesh.h"
#include "polygon.h"

namespace graphics {

	void generatePyramid(Mesh& mesh_input) {
		mesh_input.polygonCollection.insert(
			mesh_input.polygonCollection.end(),
			{
				// Side faces (apex at +Z)
				Polygon{ Point(0, 0, 1), Point(-0.5f, -0.5f, 0), Point(0.5f, -0.5f, 0) },
				Polygon{ Point(0, 0, 1), Point(0.5f, -0.5f, 0), Point(0.5f,  0.5f, 0) },
				Polygon{ Point(0, 0, 1), Point(0.5f,  0.5f, 0), Point(-0.5f,  0.5f, 0) },
				Polygon{ Point(0, 0, 1), Point(-0.5f,  0.5f, 0), Point(-0.5f, -0.5f, 0) },

				// Base (1x1 square, split into two triangles)
				Polygon{ Point(-0.5f, -0.5f, 0), Point(0.5f, -0.5f, 0), Point(0.5f,  0.5f, 0) },
				Polygon{ Point(-0.5f, -0.5f, 0), Point(0.5f,  0.5f, 0), Point(-0.5f,  0.5f, 0) }
			}
		);
	}

	void generateCube(Mesh& mesh_input) {
        mesh_input.polygonCollection.insert(
            mesh_input.polygonCollection.end(),
            {
                // Front face (Z = +0.5)
                Polygon{ Point(-0.5f, -0.5f, 0.5f), Point(0.5f, -0.5f, 0.5f), Point(0.5f,  0.5f, 0.5f) },
                Polygon{ Point(-0.5f, -0.5f, 0.5f), Point(0.5f,  0.5f, 0.5f), Point(-0.5f,  0.5f, 0.5f) },

                // Back face (Z = -0.5)
                Polygon{ Point(-0.5f, -0.5f, -0.5f), Point(0.5f,  0.5f, -0.5f), Point(0.5f, -0.5f, -0.5f) },
                Polygon{ Point(-0.5f, -0.5f, -0.5f), Point(-0.5f,  0.5f, -0.5f), Point(0.5f,  0.5f, -0.5f) },

                // Left face (X = -0.5)
                Polygon{ Point(-0.5f, -0.5f, -0.5f), Point(-0.5f, -0.5f,  0.5f), Point(-0.5f,  0.5f,  0.5f) },
                Polygon{ Point(-0.5f, -0.5f, -0.5f), Point(-0.5f,  0.5f,  0.5f), Point(-0.5f,  0.5f, -0.5f) },

                // Right face (X = +0.5)
                Polygon{ Point(0.5f, -0.5f, -0.5f), Point(0.5f,  0.5f,  0.5f), Point(0.5f, -0.5f,  0.5f) },
                Polygon{ Point(0.5f, -0.5f, -0.5f), Point(0.5f,  0.5f, -0.5f), Point(0.5f,  0.5f,  0.5f) },

                // Top face (Y = +0.5)
                Polygon{ Point(-0.5f, 0.5f, -0.5f), Point(-0.5f, 0.5f,  0.5f), Point(0.5f, 0.5f,  0.5f) },
                Polygon{ Point(-0.5f, 0.5f, -0.5f), Point(0.5f, 0.5f,  0.5f), Point(0.5f, 0.5f, -0.5f) },

                // Bottom face (Y = -0.5)
                Polygon{ Point(-0.5f, -0.5f, -0.5f), Point(0.5f, -0.5f,  0.5f), Point(-0.5f, -0.5f,  0.5f) },
                Polygon{ Point(-0.5f, -0.5f, -0.5f), Point(0.5f, -0.5f, -0.5f), Point(0.5f, -0.5f,  0.5f) }
            }
        );
	}

    void generateCylinder(Mesh& mesh_input) {
        mesh_input.polygonCollection.insert(
            mesh_input.polygonCollection.end(),
            {
                // ---------- Top cap (Z = +0.5) ----------
                Polygon{ Point(0,0,0.5f), Point(0.5f,0,0.5f), Point(0.3535f,0.3535f,0.5f) },
                Polygon{ Point(0,0,0.5f), Point(0.3535f,0.3535f,0.5f), Point(0,0.5f,0.5f) },
                Polygon{ Point(0,0,0.5f), Point(0,0.5f,0.5f), Point(-0.3535f,0.3535f,0.5f) },
                Polygon{ Point(0,0,0.5f), Point(-0.3535f,0.3535f,0.5f), Point(-0.5f,0,0.5f) },
                Polygon{ Point(0,0,0.5f), Point(-0.5f,0,0.5f), Point(-0.3535f,-0.3535f,0.5f) },
                Polygon{ Point(0,0,0.5f), Point(-0.3535f,-0.3535f,0.5f), Point(0,-0.5f,0.5f) },
                Polygon{ Point(0,0,0.5f), Point(0,-0.5f,0.5f), Point(0.3535f,-0.3535f,0.5f) },
                Polygon{ Point(0,0,0.5f), Point(0.3535f,-0.3535f,0.5f), Point(0.5f,0,0.5f) },

                // ---------- Bottom cap (Z = -0.5) ----------
                Polygon{ Point(0,0,-0.5f), Point(0.3535f,0.3535f,-0.5f), Point(0.5f,0,-0.5f) },
                Polygon{ Point(0,0,-0.5f), Point(0,0.5f,-0.5f), Point(0.3535f,0.3535f,-0.5f) },
                Polygon{ Point(0,0,-0.5f), Point(-0.3535f,0.3535f,-0.5f), Point(0,0.5f,-0.5f) },
                Polygon{ Point(0,0,-0.5f), Point(-0.5f,0,-0.5f), Point(-0.3535f,0.3535f,-0.5f) },
                Polygon{ Point(0,0,-0.5f), Point(-0.3535f,-0.3535f,-0.5f), Point(-0.5f,0,-0.5f) },
                Polygon{ Point(0,0,-0.5f), Point(0,-0.5f,-0.5f), Point(-0.3535f,-0.3535f,-0.5f) },
                Polygon{ Point(0,0,-0.5f), Point(0.3535f,-0.3535f,-0.5f), Point(0,-0.5f,-0.5f) },
                Polygon{ Point(0,0,-0.5f), Point(0.5f,0,-0.5f), Point(0.3535f,-0.3535f,-0.5f) },

                // ---------- Side faces ----------
                Polygon{ Point(0.5f,0,0.5f), Point(0.3535f,0.3535f,0.5f), Point(0.3535f,0.3535f,-0.5f) },
                Polygon{ Point(0.5f,0,0.5f), Point(0.3535f,0.3535f,-0.5f), Point(0.5f,0,-0.5f) },

                Polygon{ Point(0.3535f,0.3535f,0.5f), Point(0,0.5f,0.5f), Point(0,0.5f,-0.5f) },
                Polygon{ Point(0.3535f,0.3535f,0.5f), Point(0,0.5f,-0.5f), Point(0.3535f,0.3535f,-0.5f) },

                Polygon{ Point(0,0.5f,0.5f), Point(-0.3535f,0.3535f,0.5f), Point(-0.3535f,0.3535f,-0.5f) },
                Polygon{ Point(0,0.5f,0.5f), Point(-0.3535f,0.3535f,-0.5f), Point(0,0.5f,-0.5f) },

                Polygon{ Point(-0.3535f,0.3535f,0.5f), Point(-0.5f,0,0.5f), Point(-0.5f,0,-0.5f) },
                Polygon{ Point(-0.3535f,0.3535f,0.5f), Point(-0.5f,0,-0.5f), Point(-0.3535f,0.3535f,-0.5f) },

                Polygon{ Point(-0.5f,0,0.5f), Point(-0.3535f,-0.3535f,0.5f), Point(-0.3535f,-0.3535f,-0.5f) },
                Polygon{ Point(-0.5f,0,0.5f), Point(-0.3535f,-0.3535f,-0.5f), Point(-0.5f,0,-0.5f) },

                Polygon{ Point(-0.3535f,-0.3535f,0.5f), Point(0,-0.5f,0.5f), Point(0,-0.5f,-0.5f) },
                Polygon{ Point(-0.3535f,-0.3535f,0.5f), Point(0,-0.5f,-0.5f), Point(-0.3535f,-0.3535f,-0.5f) },

                Polygon{ Point(0,-0.5f,0.5f), Point(0.3535f,-0.3535f,0.5f), Point(0.3535f,-0.3535f,-0.5f) },
                Polygon{ Point(0,-0.5f,0.5f), Point(0.3535f,-0.3535f,-0.5f), Point(0,-0.5f,-0.5f) },

                Polygon{ Point(0.3535f,-0.3535f,0.5f), Point(0.5f,0,0.5f), Point(0.5f,0,-0.5f) },
                Polygon{ Point(0.3535f,-0.3535f,0.5f), Point(0.5f,0,-0.5f), Point(0.3535f,-0.3535f,-0.5f) }
            }
        );
    }

}