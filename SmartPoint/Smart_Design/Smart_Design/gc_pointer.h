#pragma once
/*
	Pointer implements a pointer type that uses
	garbage collection to release unused memory.
	A Pointer must only be used to point to memory
	that was dynamically allocated using new.
	When used to refer to an allocated array,
	specify the array size.
*/
#include <iostream>
#include <list>
#include <typeinfo>
#include <cstdlib>
#include "gc_details.h"
#include "gc_iterator.h"

using namespace std;

template<class T,int size=0>
class Pointer
{
private:
	// refContainer维护垃圾收集列表
	static list<PtrDetails<T>> refContainer;
	// 添加一个指针指向当前分配了的内存
	T *addr;
	// 判断是否是一个array
	bool isArray;
	// 长度
	unsigned arraySize;
	// 是否第一个指针已经被创建
	static bool first;
	// 在refContainer中返回指向指针详细信息的迭代器
	typename list<PtrDetails<T>>::iterator findPtrInfo(T *ptr);

public:
	// 定义一个指针迭代器类型
	typedef Iter<T> GCiterator;
	// Empty constructor
	// NOTE: templates aren't able to have prototypes with default arguments
	// this is why constructor is designed like this
	Pointer()
	{
		Pointer(NULL);
	}
	Pointer(T*);
	// 拷贝构造函数
	Pointer(const Pointer &ob);
	// 析构函数
	~Pointer();
	// 回收垃圾，并且返回是否最后一个，这个对象是否释放
	static bool collect();
	// 指针到指针的重载赋值
	T *operator=(T *t);
	Pointer &operator=(Pointer &rv);
	// 返回指针对象相关的指针
	T &operator*()
	{
		return *addr;
	}
	// 返回地址
	T *operator->()
	{
		return addr;
	}
	// 返回具体索引对应的地址
	T &operator[](int i)
	{
		return addr[i];
	}
	// 将Iter返回到已分配内存的开头
	Iter<T> begin()
	{
		int _size;
		if (isArray) {
			_size = arraySize;
		}
		else {
			_size = 1;
		}
		return Iter<T>(addr, addr, addr + _size);
	}
	// 将Iter返回到已分配数组末尾之后的值
	Iter<T> end()
	{
		int _size = 0;
		if (isArray) {
			_size = arraySize;
		}
		else {
			_size = 1;
		}
		return  Iter<T>(addr+_size,addr,addr+_size);
	}
	//返回此类型指针的refContainer大小(list)
	static int refContainerSize()
	{
		return refContainer.size();
	}
	// 显示refContainer包含的内容
	static void showlist();
	// 清空refContainer当程序退出时
	static void shutdown();
};

// 实现函数
// 静态函数初始化，创造一个内存给静态变量
template<class T,int size>
list<PtrDetails<T>> Pointer<T, size>::refContainer;

template<class T,int size>
bool Pointer<T, size>::first = true;

//初始化对象和未初始化对象的构造函数
template<class T, int size>
Pointer<T, size>::Pointer(T *t)
{
	// 把shutdown()函数注册成为一个exit()函数,使得在main函数后被调用
	if (first)
	{
		atexit(shutdown);
	}
	first = false;
	typename list<PtrDetails<T>>::iterator  p;
	p = findPtrInfo(t);

	if (p != refContainer.end())
	{
		p->refcount++;
	}
	else {
		PtrDetails<T> obj(t, size);
		refContainer.push_front(obj);
	}

	addr = t;
	arraySize = size;
	if (size > 0) {
		isArray = true;
	}
	else {
		isArray = false;
	}
}

// 拷贝构造函数，当切换对象时，需要使用到
template<class T,int size>
Pointer<T, size>::Pointer(const Pointer &ob)
{
	typename list<PtrDetails<T>>::iterator p;
	p = findPtrInfo(ob.addr);
	// 计数器增加
	p->refcount++;
	addr = ob.addr;
	arraySize = ob.arraySize;
	if (arraySize > 0)
	{
		isArray = true;
	}
	else {
		isArray = false;
	}
}

// 析构函数
template <class T, int size>
Pointer<T, size>::~Pointer()
{
	typename list<PtrDetails<T>>::iterator p;
	p = findPtrInfo(addr);
	if (p->refcount) {
		p->refcount--;
	}
	collect();
}

// 回收垃圾，看是否是最后一个指针，对象记得释放掉
template <class T, int size>
bool Pointer<T, size>::collect()
{
	// collect() will be called in the destructor,在析构函数中被调用
	bool memfreed = false;
	typename list<PtrDetails<T>>::iterator p;
	do {
		for (p = refContainer.begin(); p != refContainer.end(); p++)
		{
			if (p->refcount > 0) continue;
			memfreed = true;
			refContainer.remove(*p);

			if (p->memPtr) {
				if (p->isArray) {
					delete[] p->memPtr;
				}
				else
				{
					delete p->memPtr;
				}
			}
			break;
		}
	} while (p != refContainer.end());
	return memfreed;
}

// 完成重载
template <class T, int size>
T *Pointer<T, size>::operator=(T *t)
{
	typename list<PtrDetails<T>>::iterator p;
	p = findPtrInfo(addr);
	p->refcount--;
	p = findPtrInfo(t);
	if (p != refContainer.end()) {
		p->refcount++;
	}
	else {
		PtrDetails<T> obj(t, size);
		refContainer.push_front(obj);
	}
	addr = t;
	return t;
}

template <class T, int size>
Pointer<T, size> &Pointer<T, size>::operator=(Pointer &rv)
{
	typename list<PtrDetails<T>>::iterator p;
	p = findPtrInfo(addr);
	p->refcount--;
	p = findPtrInfo(rv.addr);
	p->refcount++;
	addr = rv.addr;
	return rv;
}

// show function()
template <class T, int size>
void Pointer<T, size>::showlist()
{
	typename list<PtrDetails<T>>::iterator p;
	cout << "refContainer :" << typeid(T).name << endl;
	cout<< "memPtr refcount value\n ";
	if (refContainer.begin() == refContainer.end())
	{
		cout << "refContainer is empty" << endl;
	}

	for (p = refContainer.begin(); p != refContainer.end(); p++)
	{
		cout << "[" << (void *)p->memPtr << "]" << " " << p->refcount << endl;
		if (p->memPtr) 
		{ cout << " " << *p->memPtr; }
		else
		{
			cout << "- - -";
			cout << endl;
		}
	}
	cout << endl;
}

template <class T, int size>
void Pointer<T, size>::shutdown()
{
	if (refContainerSize() == 0)
	{
		return; // 此时是空链表
	}
	typename list<PtrDetails<T>>::iterator p;
	for (p = refContainer.begin(); p != refContainer.end(); p++)
	{
		// 将所有相关的引用计数器清0
		p->refcount = 0;
	}
	// 清空内存
	collect();
}

template <class T, int size>
typename list<PtrDetails<T>>::iterator  Pointer<T, size>::findPtrInfo(T *ptr)
{
	typename list<PtrDetails<T>>::iterator p;
	// 如果指针ptr 在 refContainer链表中
	for (p = refContainer.begin(); p != refContainer.end(); p++)
	{
		if (p->memPtr == ptr) {
			return p;
		}
	}
	return p;
}






