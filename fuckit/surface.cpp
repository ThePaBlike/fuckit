#include "surface.h"


//template<typename T>
//std::vector<Vertex<T>> Surface<T>::GetVertexes()
//{
//	return _vertexes;
//}
//
//template<typename T>
//int * Surface<T>::GetIndexes()
//{
//	return _indexes;
//}
//
//template<typename T>
//void Surface<T>::computeVertexes()
//{
//	for (T u = _interval_u.start; u <= _interval_u.end; u += _step_u)
//		for (T v = _interval_v.start; v <= _interval_v.end; v += _step_v)
//			_vertexes.push_back(getVertex(u, v));	
//}
//
//template<typename T>
//void Surface<T>::computeIndexes()
//{
//	// TODO написать код для индексации
//	int ind;
//	int i = 0;
//	for (int j = 0; j < (_density_u + 1) * (_density_v + 1); j += _density_v + 1)
//	{
//		for (int l = 0; l < _density_v; l++)
//		{
//			ind = j + l;
//			_indexes[i++] = ind;
//			_indexes[i++] = ind + _density_v;
//			_indexes[i++] = ind + 1;
//			_indexes[i++] = ind + 1;
//			_indexes[i++] = ind + _density_v;
//			_indexes[i++] = ind + _density_v + 1;
//		}
//	}
//}
//
