#include "hyper_cylinder.h"
Hyper_cylinder::Hyper_cylinder(float a, float b, float c, int density_u, int density_v, Interval interval_u, Interval interval_v)
	: Surface(a, b, c, density_u, density_v, interval_u, interval_v)
{
	computeVertexes();
	computeIndexes();
}

Vertex Hyper_cylinder::getVertex(float u, float v)
{
	return Vertex(
		_b * sinh(u),
		v,
		_a * cosh(u));
}
