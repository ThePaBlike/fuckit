#pragma once
#include <vector>
#include <cmath>
#define PI 3.141592653589793f

struct Interval
{
	// Поля
	float start;
	float end;

	// Конструкторы
	Interval() {}
	Interval(float _st, float _en)
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

struct Vertex
{
	Vertex() {}
	Vertex(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	float x;
	float y;
	float z;

	// Оператор присваивания
	Vertex& Vertex::operator=(Vertex i)
	{
		x = i.x;
		y = i.y;
		z = i.z;
		return *this;
	}
};


class Surface
{
public:
	Surface();
	Surface(float a, float b, float c, int density_u, int density_v, Interval interval_u, Interval interval_v);
	virtual ~Surface();

	std::vector<Vertex> GetVertexes();
	std::vector<int> GetIndexes();
	
	int GetVertexLength();
	int GetIndexLength();

protected:
	// Параметры поверхности
	float _a, _b, _c;
	// Метод для рассчёта всех вершин 
	void computeVertexes();
	// Метод для рассчёта всех индексов
	void computeIndexes();
	// Метод для вычисления каждой вершины по заданной формуле
	virtual inline Vertex getVertex(float u, float v) = 0;
private:
	std::vector<Vertex> _vertexes;
	int _vertexes_length;
	std::vector<int> _indexes;
	int _indexes_length;

	// Плотность сегментов
	int _density_u, _density_v;
	// Шаг 
	float _step_u;
	float _step_v;
	// Интервал
	Interval _interval_u;
	Interval _interval_v;
};




