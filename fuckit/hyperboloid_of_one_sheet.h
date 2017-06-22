#pragma once
#include "surface.h"
class Hyperboloid_of_one_sheet :
	public Surface
{
public:
	Hyperboloid_of_one_sheet(float a, float b, float c, int density_u, int density_v, Interval interval_u, Interval interval_v);
private:
	Vertex getVertex(float u, float v);
};

