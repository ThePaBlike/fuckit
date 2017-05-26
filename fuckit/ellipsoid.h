#pragma once
#include "surface.h"
#include <cmath>

class Ellipsoid :
	public Surface
{
public:	
	Ellipsoid(float a, float b, float c, int density_u, int density_v, Interval interval_u, Interval interval_v);
private:
	Vertex getVertex(float u, float v);
};

