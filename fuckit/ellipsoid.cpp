#include "ellipsoid.h"
#include <cmath>

template<typename T>
Ellipsoid<T>::Ellipsoid()
{
}

template<typename T>
Ellipsoid<T>::Ellipsoid(T a, T b, T c, int density_u, int density_v, Interval<T> interval_u, Interval<T> interval_v)
	: Surface<T>(a, b, c, density_u, density_v, interval_u, interval_v)
{
}

template<typename T>
Ellipsoid<T>::~Ellipsoid()
{
}

template<typename T>
Vertex<T> Ellipsoid<T>::getVertex(T u, T v) 
{
	return Vertex<T>(
		_a * sin(u) * cos(v),
		_b * sin(u) * sin(v),
		_c * cos(u));
}