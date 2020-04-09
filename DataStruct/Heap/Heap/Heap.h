#pragma once
// 实现堆 -> 基于树

#include <iostream>
#include <vector>
using namespace std;

// 定义两个比大小模板
template<typename T>
struct Less
{
	bool operator()(const T& left, const T&right)
	{
		return left < right;
	}
};

template<typename T>
struct  Great
{
	bool operator()(const T& left, const T&right)
	{
		return left > right;
	}
};

template<typename T,template<class> class Compare = Less>
class Heap
{
public:
	// 构造函数
	Heap() {}
	Heap(const T array[],size_t size)
	{
		__heap.resize(size);
		for (int index = 0; index < size; index++)
		{
			__heap[index] = array[index];
		}
		// 下表从0 开始 所以heap-2
		for (int root = (__heap.size() - 2) >> 1; root >= 0; root--)
			__AdjustDown(root);
	}

	// 插入操作函数
	void Push(const T& value)
	{	
		// 插进去后，向上调整
		__heap.push_back(value);
		if (__heap.size() > 1)
			___AdjustUp();
	}
	// 删除
	void pop()
	{
		if (__heap.size() == 0)
			return;
		__heap[0] = __heap[__heap.size() - 1];
		__heap.pop_back();
		if (__heap.size() > 1)
			_AdjustUp();
	}
	// 求大小
	size_t const size()
	{
		return __heap.size();
	}
	// 堆顶
	const T& const Top()
	{
		return __heap.front();
	}
	// 判空
	bool empty() const
	{
		return __heap.size() == 0;
	}
	// 打印堆的信息
	void PrintHeap()
	{
		cout << "Heap info :" << endl;
		for (int i = 0; i <= __heap.size() - 1; i++)
		{
			cout << __heap[i] << " ";
		}
		cout << endl;
	}

private:
	// 堆排序的本质
	// 向下调整堆
	void __AdjustDown(size_t parent)
	{
		size_t child = parent * 2 + 1;
		size_t size = __heap.size();

		while (child < size)
		{
			if ((child + 1) < size && Compare<T>()(__heap[child + 1], __heap[child]))
				child++;
			if (Compare<T>()(__heap[child], __heap[parent]))
			{
				swap(__heap[child], __heap[parent]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
			{
				return;
			}
		}
	}

	// 向上调整堆
	void _AdjustUp()
	{
		size_t child = __heap.size() - 1;
		size_t parent = child - 1 >> 1;

		while (child != 0)
		{
			if (Compare<T>()(__heap[child], __heap[parent]))
			{
				swap(__heap[child], __heap[parent]);
				child = parent;
				parent = (child - 1) >> 1;
			}
			else
			{
				return;
			}
		}

	}

private:
	vector<T> __heap;
};



