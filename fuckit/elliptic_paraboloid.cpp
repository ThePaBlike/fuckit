#include "elliptic_paraboloid.h"

Elliptic_paraboloid::Elliptic_paraboloid(float a, float b, float c, int density_u, int density_v, Interval interval_u, Interval interval_v)
	: Surface(a, b, c, density_u, density_v, interval_u, interval_v)
{
	computeVertexes();
	computeIndexes();
}

Vertex Elliptic_paraboloid::getVertex(float u, float v)
{
	return Vertex(
		_a * u * cos(v),
		_b * u * sin(v),
		u * u);
}

