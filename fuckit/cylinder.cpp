#include "cylinder.h"

Cylinder::Cylinder(float a, float b, float c, int density_u, int density_v, Interval interval_u, Interval interval_v)
	: Surface(a, b, c, density_u, density_v, interval_u, interval_v)
{
	computeVertexes();
	computeIndexes();
}

Vertex Cylinder::getVertex(float u, float v)
{
	return Vertex(
		_a * v,
		_b * cos(u),
		_c * sin(u));
}