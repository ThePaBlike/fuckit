#include "surface.h"

template<typename T>
Surface<T>::Surface()
{
}

template<typename T>
Surface<T>::Surface(T a, T b, T c, int density_u, int density_v, Interval<T> interval_u, Interval<T> interval_v)
{
	// Присваиваем аргументы конструктора локальным переменным
	_a = a;
	_b = b;
	_c = c;
	_density_u = density_u;
	_density_v = density_v;
	_interval_u = interval_u;
	_interval_v = interval_v;

	//TODO разобраться с выделением памяти
	// Вычисляем шаг для каждой новой вершины
	_step_u = (_interval_u.end - _interval_u.start) / _density_u;
	_step_v = (_interval_v.end - _interval_v.start) / _density_v;
	// Выделяем память под координаты вершин
	_vertexes_length = (_density_u + 1) * (_density_v + 1);
	_vertexes.reserve(_vertexes_length);
	// Выделяем память под индексы
	_indexes_length = (_density_u + 2) * (_density_v + 1) * 6;
	_indexes = new int[_indexes_length];

	computeVertexes();
	computeIndexes();
}

template<typename T>
virtual Surface<T>::~Surface()
{
	delete[] _indexes;
}

template<typename T>
std::vector<Vertex<T>> Surface<T>::GetVertexes()
{
	return _vertexes;
}

template<typename T>
int * Surface<T>::GetIndexes()
{
	return _indexes;
}

template<typename T>
void Surface<T>::computeVertexes()
{
	for (T u = _interval_u.start; u <= _interval_u.end; u += _step_u)
		for (T v = _interval_v.start; v <= _interval_v.end; v += _step_v)
			_vertexes.push_back(getVertex(u, v));	
}

template<typename T>
void Surface<T>::computeIndexes()
{
	// TODO написать код для индексации
	int ind;
	int i = 0;
	for (int j = 0; j < (_density_u + 1) * (_density_v + 1); j += _density_v + 1)
	{
		for (int l = 0; l < _density_v; l++)
		{
			ind = j + l;
			_indexes[i++] = ind;
			_indexes[i++] = ind + _density_v;
			_indexes[i++] = ind + 1;
			_indexes[i++] = ind + 1;
			_indexes[i++] = ind + _density_v;
			_indexes[i++] = ind + _density_v + 1;
		}
	}
}

