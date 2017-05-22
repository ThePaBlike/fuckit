#pragma once
#include "surface.h"

template <typename T>
class Ellipsoid :
	public Surface<T>
{
public:
	Ellipsoid();
	Ellipsoid(T a, T b, T c, int density_u, int density_v, Interval<T> interval_u, Interval<T> interval_v);
	~Ellipsoid();
private:
	Vertex<T> getVertex(T u, T v) override;
};

