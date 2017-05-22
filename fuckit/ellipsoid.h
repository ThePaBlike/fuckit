#pragma once
#include "surface.h"
#include <cmath>
template <typename T>
class Ellipsoid :
	public Surface<T>
{
public:
	
	template<typename T>
	Ellipsoid(T a, T b, T c, int density_u, int density_v, Interval<T> interval_u, Interval<T> interval_v)
		: Surface<T>(a, b, c, density_u, density_v, interval_u, interval_v)
	{
	}

	~Ellipsoid()
	{
	}
private:
	Vertex<T> getVertex(T u, T v) override;
};


template<typename T>
Vertex<T> Ellipsoid<T>::getVertex(T u, T v)
{
	return Vertex<T>(
		_a * sin(u) * cos(v),
		_b * sin(u) * sin(v),
		_c * cos(u));
}