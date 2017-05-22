#pragma once
#include <vector>
#define PI 3.141592

template <typename T>
struct Interval
{
	// Поля
	T start;
	T end;

	// Конструкторы
	Interval() {}
	Interval(T _st, T _en)
	{
		start = _st;
		end = _en;
	}

	// Оператор присваивания
	Interval& Interval::operator=(Interval i)
	{
		start = i.start;
		end = i.end;
		return *this;
	}
};

template <typename T>
struct Vertex
{
	Vertex() {}
	Vertex(T _x, T _y, T _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	T x;
	T y;
	T z;

	// Оператор присваивания
	Vertex& Vertex::operator=(Vertex i)
	{
		start = i.start;
		end = i.end;
		return *this;
	}
};

template <typename T>
class Surface
{
public:
	template<typename T>
	Surface()
	{
	}

	template<typename T>
	Surface(T a, T b, T c, int density_u, int density_v, Interval<T> interval_u, Interval<T> interval_v)
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
		_indexes.reserve(_indexes_length);

		computeVertexes();
		computeIndexes();
	}

	virtual ~Surface()
	{
	}
	std::vector<Vertex<T>> GetVertexes();
	std::vector<int> GetIndexes();
	
	int GetVertexLength();

	int GetIndexLength();
protected:
	// Указатель на указатели, которые содержат x, y, z координаты каждой вершины
	std::vector<Vertex<T>> _vertexes;
	int _vertexes_length;
	// Указатель на массив индексов, содержащий порядок рисования вершин
	std::vector<int> _indexes;
	int _indexes_length;
	// Параметры поверхности
	T _a, _b, _c;
	// Плотность сегментов
	int _density_u, _density_v;
	// Шаг 
	T _step_u;
	T _step_v;
	// Интервал
	Interval<T> _interval_u;
	Interval<T> _interval_v;

	virtual inline Vertex<T> getVertex(T u, T v) = 0;
private:
	// Метод для рассчёта всех вершин 
	void computeVertexes();	
	// Метод для рассчёта всех индексов
	void computeIndexes();

	

};



template<typename T>
std::vector<Vertex<T>> Surface<T>::GetVertexes()
{
	return _vertexes;
}

template<typename T>
std::vector<int> Surface<T>::GetIndexes()
{
	return _indexes;
}

template<typename T>
void Surface<T>::computeVertexes()
{
	for (T u = _interval_u.start; u <= _interval_u.end; u += _step_u)
		for (T v = _interval_v.start; v <= _interval_v.end; v += _step_v)
			_vertexes.push_back(getVertexe(u, v));
}
template<typename T>
Vertex<double> getVertexe(T u, T v)
{
	return Vertex<T>(
		v,
		cos(u),
		sin(u));
}
template<typename T>
void Surface<T>::computeIndexes()
{
	// TODO написать код для индексации
	int ind;
	for (int j = 0; j < (_density_u + 1) * (_density_v + 1); j += _density_v + 1)
	{
		for (int l = 0; l < _density_v; l++)
		{
			ind = j + l;
			_indexes.push_back(ind);
			_indexes.push_back(ind + _density_v);
			_indexes.push_back(ind + 1);
			_indexes.push_back(ind + 1);
			_indexes.push_back(ind + _density_v);
			_indexes.push_back(ind + _density_v + 1);
		}
	}
}

template<typename T>
int Surface<T>::GetVertexLength()
{
	return _vertexes_length;
}

template<typename T>
int Surface<T>::GetIndexLength()
{
	return _indexes_length;
}

