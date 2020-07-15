#pragma once
// дһ��heap��ͷ�ļ�
// ���ȶ��� -> ����heap
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

template<class T>
class Less
{
public:
	bool operator()(const T& l,const T& r)
	{
		return l < r;
	}
};

template<class T>
class Greader
{
public:
	bool operator()(const T& l, const T& r)
	{
		return l > r;
	}
};

template <class T, class Compare = Greader<int>>
class Heap 
{
public:
	Heap() {}

	Heap(const T a[], size_t n)
	{
		_heap.resize(n);
		for (size_t i = 0; i < n; i++)
		{
			_heap[i] = a[i];
		}
		for (int root = (_heap.size() - 2) >> 1; root >= 0; --root)
		{
			AdJustDown(root);
		}
	}

	void Push(const T& value)
	{
		_heap.push_back(value);
		if (_heap.size() > 1)
			AdJustUp();
	}

	void Pop()
	{
		assert(_heap.size() > 0);
		swap(_heap[0],_heap[_heap.size() - 1]);
		_heap.pop_back();
		if (_heap.size() > 0) // ��ֹ����ֻ��һ���ڵ㣬ɾ����Ϊ0
			AdJustDown(0);
	}

	// const�����ֹ�Ѷ����ƻ��ṹ
	const T& Top()
	{
		return _heap[0];
	}

	size_t Size()
	{
		return _heap.size();
	}

	bool Empty()
	{
		return _heap.empty();
	}

private:
	void AdJustDown(int root)
	{
		int parent = root;
		int child = root * 2 + 1;
		while (child < _heap.size())
		{
			if ((child + 1) < _heap.size() && Compare()(_heap[child + 1], _heap[child]))
				++child;
			if (Compare()(_heap[child], _heap[parent]))
			{
				swap(_heap[parent], _heap[child]);
				parent = child;
				child = child * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}

	void AdJustUp()
	{
		int child = _heap.size() - 1;
		int parent = (child - 1) >> 1;

		while (parent >= 0)  // child > 0
		{
			if (Compare()(_heap[child], _heap[parent]))
			{
				swap(_heap[child], _heap[parent]);
				child = parent;
				parent = (child - 1) >> 1;
			}
			else
			{
				break;
			}
		}
	}

private:
	vector<T> _heap;
};



