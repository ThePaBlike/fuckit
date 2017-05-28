#pragma once
#include "surface.h"

class Thor :
	public Surface
{
public:
	Thor(float a, float b, float c, int density_u, int density_v, Interval interval_u, Interval interval_v);
private:
	Vertex getVertex(float u, float v);
};
