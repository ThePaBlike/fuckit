#include "thor.h"

Thor::Thor(float a, float b, float c, int density_u, int density_v, Interval interval_u, Interval interval_v)
	: Surface(a, b, c, density_u, density_v, interval_u, interval_v)
{
	computeVertexes();
	computeIndexes();
}

Vertex Thor::getVertex(float u, float v)
{
	return Vertex(
		_a * cos(u) * cos(v),
		_b * cos(u) * sin(v),
		_c * sin(u));
}