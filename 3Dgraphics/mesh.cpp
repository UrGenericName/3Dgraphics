#pragma once
#include "mesh.h"

namespace graphics {
	Mesh::Mesh() {}

	bool Mesh::isValid() const {
		return !polygonCollection.empty();
	}

	void Mesh::updateWorldSpacePolygonCollection() {

		worldSpacePolygonCollection = polygonCollection;

		// Rotates polygons
		for (int i = 0; i < worldSpacePolygonCollection.size(); i++) {

			Point pointA { worldSpacePolygonCollection.at(i).getPointA() };
			Point pointB { worldSpacePolygonCollection.at(i).getPointB() };
			Point pointC { worldSpacePolygonCollection.at(i).getPointC() };

			pointA.rotate(rotation);
			pointB.rotate(rotation);
			pointC.rotate(rotation);

			worldSpacePolygonCollection.at(i).newPointA(pointA);
			worldSpacePolygonCollection.at(i).newPointB(pointB);
			worldSpacePolygonCollection.at(i).newPointC(pointC);

		}

		// Scales polygons
		for (int i = 0; i < worldSpacePolygonCollection.size(); i++) {

			Point pointA{ worldSpacePolygonCollection.at(i).getPointA() };
			Point pointB{ worldSpacePolygonCollection.at(i).getPointB() };
			Point pointC{ worldSpacePolygonCollection.at(i).getPointC() };

			pointA.scale(scale);
			pointB.scale(scale);
			pointC.scale(scale);

			worldSpacePolygonCollection.at(i).newPointA(pointA);
			worldSpacePolygonCollection.at(i).newPointB(pointB);
			worldSpacePolygonCollection.at(i).newPointC(pointC);

		}

		// Translates polygons
		for (int i = 0; i < worldSpacePolygonCollection.size(); i++) {

			Point pointA{ worldSpacePolygonCollection.at(i).getPointA() + position };
			Point pointB{ worldSpacePolygonCollection.at(i).getPointB() + position };
			Point pointC{ worldSpacePolygonCollection.at(i).getPointC() + position };

			worldSpacePolygonCollection.at(i).newPointA(pointA);
			worldSpacePolygonCollection.at(i).newPointB(pointB);
			worldSpacePolygonCollection.at(i).newPointC(pointC);

		}
	}
}