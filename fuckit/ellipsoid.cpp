#include "ellipsoid.h"

Ellipsoid::Ellipsoid(float a, float b, float c, int density_u, int density_v, Interval interval_u, Interval interval_v)
	: Surface(a, b, c, density_u, density_v, interval_u, interval_v)
{
	computeVertexes();
	computeIndexes();
}

Vertex Ellipsoid::getVertex(float u, float v)
{
	return Vertex(
		_a * sin(u) * cos(v),
		_b * sin(u) * sin(v),
		_c * cos(u));
}