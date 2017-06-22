#pragma once
#include "surface.h"
class Parabolic_cylinder :
	public Surface
{
public:
	Parabolic_cylinder(float a, float b, float c, int density_u, int density_v, Interval interval_u, Interval interval_v);
private:
	Vertex getVertex(float u, float v);
};

