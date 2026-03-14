#pragma once
#include "3Dgraphics/mesh.h"

namespace graphics {
	Mesh::Mesh() {}

	bool Mesh::isValid() const {
		return !polygonCollection.empty();
	}

	void Mesh::updateWorldSpacePolygonCollection() {

		worldSpacePolygonCollection = polygonCollection;

		// Rotates polygons
		for (int i = 0; i < worldSpacePolygonCollection.size(); i++) {

			Point pointA { worldSpacePolygonCollection[i].getPointA() };
			Point pointB { worldSpacePolygonCollection[i].getPointB() };
			Point pointC { worldSpacePolygonCollection[i].getPointC() };

			pointA.rotate(rotation);
			pointB.rotate(rotation);
			pointC.rotate(rotation);

			worldSpacePolygonCollection[i].newPointA(pointA);
			worldSpacePolygonCollection[i].newPointB(pointB);
			worldSpacePolygonCollection[i].newPointC(pointC);

		}

		// Scales polygons
		for (int i = 0; i < worldSpacePolygonCollection.size(); i++) {

			Point pointA{ worldSpacePolygonCollection[i].getPointA() };
			Point pointB{ worldSpacePolygonCollection[i].getPointB() };
			Point pointC{ worldSpacePolygonCollection[i].getPointC() };

			pointA.scale(scale);
			pointB.scale(scale);
			pointC.scale(scale);

			worldSpacePolygonCollection[i].newPointA(pointA);
			worldSpacePolygonCollection[i].newPointB(pointB);
			worldSpacePolygonCollection[i].newPointC(pointC);

		}

		// Translates polygons
		for (int i = 0; i < worldSpacePolygonCollection.size(); i++) {

			Point pointA{ worldSpacePolygonCollection[i].getPointA() + position };
			Point pointB{ worldSpacePolygonCollection[i].getPointB() + position };
			Point pointC{ worldSpacePolygonCollection[i].getPointC() + position };

			worldSpacePolygonCollection[i].newPointA(pointA);
			worldSpacePolygonCollection[i].newPointB(pointB);
			worldSpacePolygonCollection[i].newPointC(pointC);

		}
	}
}