#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <assert.h>
using namespace std;

template <class V,class W>
class GraphMatrix
{
public:
	GraphMatrix(V* vertex,size_t size,bool isdirect = false):_size(size),_isdirect(isdirect)
	{
		_vertex = new V[size];
		_matrix = new W*[size];
		for (size_t i = 0; i < size; i++)
		{
			_vertex[i] = vertex[i];
			_matrix[i] = new W[size];
			for (size_t j = 0; j < size; j++)
			{
				_matrix[i][j] = W();
			}
		}
	}

	~GraphMatrix()
	{
		delete[] _vertex;
		for (int i = 0; i < _size; i++)
		{
			delete[] _matrix[i];
		}
		delete[] _matrix;
	}

	void AddEdge(const V& src,const V& dst,const W& w)
	{
		size_t line = GetIndex(src);
		size_t row = GetIndex(dst);

		_matrix[line][row] = w;
		if (_isdirect == false)
		{
			_matrix[row][line] = w;
		}
	}

protected:
	size_t GetIndex(const V& src)
	{
		for (size_t i = 0; i < _size; i++)
		{
			if (_vertex[i] == src)
				return i;
		}
		assert(false);
		return -1;
	}

private:
	V* _vertex;
	// _matrix ¶þÎ¬Êý×é
	W** _matrix;
	size_t _size;
	bool _isdirect;

};


void TestGraphMatrix()
{
	string strs[] = { "China", "Japan", "Korea", "Russia" };
	GraphMatrix<string, int> gm(strs, sizeof(strs) / sizeof(strs[0]));

	gm.AddEdge("China", "Japan", 100);
	gm.AddEdge("China", "Korea", 200);
	gm.AddEdge("China", "Russia", 300);
	gm.AddEdge("Japan", "Korea", 150);
	gm.AddEdge("Russia", "Japan", 400);
}
