#pragma once
#include <vector>

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
	T x;
	T y;
	T z;
};

template <typename T>
class Surface
{
public:
	Surface();
	Surface(T a, T b, T c, int density_u, int density_v, Interval<T> interval_u, Interval<T> interval_v);
	~Surface();
	std::vector<Vertex<T>> GetVertexes();
	int* GetIndexes();
protected:
	// Указатель на указатели, которые содержат x, y, z координаты каждой вершины
	std::vector<Vertex<T>> _vertexes;
	int _vertexes_length;
	// Указатель на массив индексов, содержащий порядок рисования вершин
	int *_indexes;
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
	// Метод для получения координат вершин 
	void computeVertexes();	
	void computeIndexes();

};

