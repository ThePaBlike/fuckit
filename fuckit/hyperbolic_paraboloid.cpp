#include "hyperbolic_paraboloid.h"

Hyperbolic_paraboloid::Hyperbolic_paraboloid(float a, float b, float c, int density_u, int density_v, Interval interval_u, Interval interval_v)
	: Surface(a, b, c, density_u, density_v, interval_u, interval_v)
{
	computeVertexes();
	computeIndexes();
}

Vertex Hyperbolic_paraboloid::getVertex(float u, float v)
{
	return Vertex(
		_a * (u + v),
		_b * (v - u),
		4 * u * v);
}
