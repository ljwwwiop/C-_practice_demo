#pragma once
#include "Heap.h"

template<class T,class Compare=Greader<T>>
class Priority_Queue
{
public:
	Priority_Queue() {}

	~Priority_Queue(){}

	const T& Top() const 
	{
		return hp.Top();
	}

	bool Empty()
	{
		return hp.Empty();
	}

	size_t Size()
	{
		return hp.Size();
	}

	void Pop()
	{
		hp.Pop();
	}

	void Push(const T& data)
	{
		hp.Push(data);
	}

	void Print_Queue()
	{
		while (!hp.Empty())
		{
			cout << hp.Top() << " ";
			hp.Pop();
		}
		cout << endl;
	}


private:
	Heap<T, Compare> hp;
};




