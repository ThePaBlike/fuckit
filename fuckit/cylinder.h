#pragma once
#include "surface.h"

class Cylinder :
	public Surface
{
public:
	Cylinder(float a, float b, float c, int density_u, int density_v, Interval interval_u, Interval interval_v);
private:
	Vertex getVertex(float u, float v);
};
