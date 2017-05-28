#include "surface.h"

Surface::Surface() {}

Surface::Surface(float a, float b, float c, int density_u, int density_v, Interval interval_u, Interval interval_v)
{
	// ����������� ��������� ������������ ��������� ����������
	_a = a;
	_b = b;
	_c = c;
	_density_u = density_u;
	_density_v = density_v;
	_interval_u = interval_u;
	_interval_v = interval_v;

	//TODO ����������� � ���������� ������
	// ��������� ��� ��� ������ ����� �������
	_step_u = (_interval_u.end - _interval_u.start) / _density_u;
	_step_v = (_interval_v.end - _interval_v.start) / _density_v;
	// �������� ������ ��� ���������� ������
	_vertexes_length = (_density_u + 1) * (_density_v + 1);
	_vertexes.reserve(_vertexes_length);
	// �������� ������ ��� �������
	_indexes_length = (_density_u) * (_density_v) * 4;
	_indexes.reserve(_indexes_length);
}

Surface::~Surface() {}

std::vector<Vertex> Surface::GetVertexes()
{
	return _vertexes;
}

std::vector<int> Surface::GetIndexes()
{
	return _indexes;
}


void Surface::computeVertexes()
{
	// TODO �������� ��� ��� ���������� ������� ������
	float u, v;
	int i, j;
	for (i = 0, u = _interval_u.start; i <= _density_u; u += _step_u, i++)
	{
		for (j = 0, v = _interval_v.start; j <= _density_v; v += _step_v, j++)
		{
			_vertexes.push_back(getVertex(u, v));
		}
	}
}

void Surface::computeIndexes()
{
	// TODO �������� ��� ��� ����������
	int index;
	int heigth = _density_v + 1;
	for (int i = 0; i < _density_u; i++)
	{
		for (int j = 0; j < _density_v; j++)
		{
			index = i * heigth + j;
			_indexes.push_back(index);
			_indexes.push_back(index + heigth);
			_indexes.push_back(index + heigth + 1);
			_indexes.push_back(index + 1);
		}
	}
}

int Surface::GetVertexLength()
{
	return _vertexes_length;
}


int Surface::GetIndexLength()
{
	return _indexes_length;
}

