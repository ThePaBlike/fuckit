#pragma once
#include <vector>
#include <cmath>
#define PI 3.141592653589793f

struct Interval
{
	// ����
	float start;
	float end;

	// ������������
	Interval() {}
	Interval(float _st, float _en)
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

	// �������� ������������
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
	// ��������� �����������
	float _a, _b, _c;
	// ����� ��� �������� ���� ������ 
	void computeVertexes();
	// ����� ��� �������� ���� ��������
	void computeIndexes();
	// ����� ��� ���������� ������ ������� �� �������� �������
	virtual inline Vertex getVertex(float u, float v) = 0;
private:
	std::vector<Vertex> _vertexes;
	int _vertexes_length;
	std::vector<int> _indexes;
	int _indexes_length;

	// ��������� ���������
	int _density_u, _density_v;
	// ��� 
	float _step_u;
	float _step_v;
	// ��������
	Interval _interval_u;
	Interval _interval_v;
};




