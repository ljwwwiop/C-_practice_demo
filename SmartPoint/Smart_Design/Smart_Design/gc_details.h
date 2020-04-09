#pragma once
// 主要是为了实现一个自己的智能智能，垃圾回收机制,强化一下template的使用
// This class defines an element that is stored,定义了被存储的元素
// in the garbage collection information list.
#include <iostream>

using namespace std;

template<class T>
class PtrDetails 
{
public:
	// 当前引用计数
	unsigned refcount;
	// 指向已经分配内存的指针
	T *memPtr;
	// 指针指向的是否是一个连续的数组
	bool isArray;
	// 数组长度
	unsigned arraysize;
	// 进行细节处理，如果指向数组了，size就是数组大小
	PtrDetails(T *mPtr,unsigned size = 0)
	{
		refcount = 1;
		memPtr = mPtr;
		arraysize = size;
		
		if (size != 0)
		{
			isArray = true;
		}
		else 
		{
			isArray = false;
		}
	}
};

// Overloading operator== allows two class objects to be compared.
// This is needed by the STL list class.
template<class T>
bool operator==(const PtrDetails<T> & obj1, const PtrDetails<T> & obj2)
{
	return obj1.memPtr == obj2.memPtr;
}





