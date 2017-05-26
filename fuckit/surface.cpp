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
	_indexes_length = (_density_u + 1) * (_density_v + 1) * 4;
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
	for (float u = _interval_u.start; u <= _interval_u.end; u += _step_u)
		for (float v = _interval_v.start; v <= _interval_v.end; v += _step_v)
			_vertexes.push_back(getVertex(u, v));
}

void Surface::computeIndexes()
{
	// TODO �������� ��� ��� ����������
	int ind;
	for (int j = 0; j < (_density_u + 1) * (_density_v + 1); j += _density_v + 1)
	{
		for (int l = 0; l < _density_v; l++)
		{
			ind = j + l;
			_indexes.push_back(ind);
			_indexes.push_back(ind + _density_v);
			_indexes.push_back(ind + _density_v + 1);
			_indexes.push_back(ind + 1);
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

