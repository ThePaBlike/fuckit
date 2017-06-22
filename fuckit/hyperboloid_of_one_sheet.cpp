#include "hyperboloid_of_one_sheet.h"

Hyperboloid_of_one_sheet::Hyperboloid_of_one_sheet(float a, float b, float c, int density_u, int density_v, Interval interval_u, Interval interval_v)
	: Surface(a, b, c, density_u, density_v, interval_u, interval_v)
{
	computeVertexes();
	computeIndexes();
}

Vertex Hyperboloid_of_one_sheet::getVertex(float u, float v)
{
	return Vertex(
		_a * cosh(u) * cos(v),
		_b * sinh(u) * sin(v),
		_c * sinh(u));
}