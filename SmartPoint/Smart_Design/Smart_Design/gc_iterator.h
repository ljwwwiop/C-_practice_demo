#pragma once
/*
	处理可能发生的异常，使用一些超级处对象的迭代器iter
	
*/
#include <iostream>

using namespace std;

class OutOfRangeExc
{
	// 处理异常类
	// 添加函数如果需要被你申请
	OutOfRangeExc()
	{
		cout << "Attempted Access is Out of Range" << endl;
	}
};

// 主要进行处理一个迭代器iter
template<class T>
class Iter
{
private:
	T *ptr;
	// current pointer value
	T *end;
	// points to element one past end
	T *begin;
	// points to start of allocated array
	unsigned length; // 连续的长度

public:
	Iter()
	{
		ptr = end = begin = NULL;
		length = 0;
	}
	Iter(T *p,T *first,T *last)
	{
		ptr = p;
		begin = first;
		end = last;
		length = last - first;
	}
	// Return length of sequence to which this
	// Iter points.
	unsigned size() { return length; }
	// Return value pointed to by ptr.
	// Do not allow out-of-bounds access. 不能越界
	T &operator*() {
		if ((ptr >= end) || (ptr < begin)) {
			throw OutOfRangeExc();
		}
		return *ptr;
	}

	// Return address contained in ptr.
	// Do not allow out-of-bounds access.
	T *operator->()
	{
		if ((ptr >= end) || (ptr < begin))
		{
			throw OutOfRangeExc();
		}
		return ptr;
	}

	// 重载 前置++
	Iter operator++()
	{
		ptr++;
		return *this;
	}
	// 前置 - -
	Iter operator--()
	{
		ptr--;
		return *this;
	}
	// 后置++
	Iter operator++(int)
	{
		T *tmp = ptr;
		ptr++;
		return Iter<T>(tmp,begin,end);
	}
	// 后置--
	Iter operator--(int)
	{
		T *tmp = ptr;
		ptr--;
		return Iter<T>(tmp, begin, end);
	}
	// Return a reference to the object at the specified index
	T &operator[](int i)
	{
		if (i < 0 || i >= (end - begin)) {
			throw OutOfRangeExc();
		}
	}
	// 相关关系符重载
	bool operator==(const Iter &op2)
	{
		return ptr == op2.ptr;
	}
	bool operator!=(const Iter &op2)
	{
		return ptr != op2.ptr;
	}
	bool operator<(const Iter &op2)
	{
		return ptr < op2.ptr;
	}
	bool operator<=(const Iter &op2)
	{
		return ptr <= op2.ptr;
	}
	bool operator>(const Iter &op2)
	{
		return ptr > op2.ptr;
	}
	bool operator>=(const Iter &op2)
	{
		return ptr >= op2.ptr;
	}
	
	// 重载+ - 整数 操作
	Iter operator-(int n)
	{
		ptr -= n;
		return *this;
	}
	Iter operator+(int n)
	{
		ptr += n;
		return *this;
	}
	// 返回两个iter迭代器之间的元素个数
	int operator-(const Iter<T> &itr2)
	{
		return ptr - itr2.ptr;
	}
};






