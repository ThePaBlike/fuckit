#pragma once
#include "surface.h"
class Hyper_cylinder :
	public Surface
{
public:
	Hyper_cylinder(float a, float b, float c, int density_u, int density_v, Interval interval_u, Interval interval_v);
private:
	Vertex getVertex(float u, float v);
};

