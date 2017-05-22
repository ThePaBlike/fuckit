#pragma once
#include <vector>

template <typename T>
struct Interval
{
	// ����
	T start;
	T end;

	// ������������
	Interval() {}
	Interval(T _st, T _en)
	{
		start = _st;
		end = _en;
	}

	// �������� ������������
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
	// ��������� �� ���������, ������� �������� x, y, z ���������� ������ �������
	std::vector<Vertex<T>> _vertexes;
	int _vertexes_length;
	// ��������� �� ������ ��������, ���������� ������� ��������� ������
	int *_indexes;
	int _indexes_length;
	// ��������� �����������
	T _a, _b, _c;
	// ��������� ���������
	int _density_u, _density_v;
	// ��� 
	T _step_u;
	T _step_v;
	// ��������
	Interval<T> _interval_u;
	Interval<T> _interval_v;

	virtual inline Vertex<T> getVertex(T u, T v) = 0;
private:
	// ����� ��� ��������� ��������� ������ 
	void computeVertexes();	
	void computeIndexes();

};

