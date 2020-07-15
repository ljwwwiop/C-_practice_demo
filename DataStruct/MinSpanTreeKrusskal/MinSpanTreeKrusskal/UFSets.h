#pragma once
// ���鼯
#include <iostream>
using namespace std;

template<typename ElemType>
struct ElemNode
{
	ElemType data;
	int parent;
};

template<typename ElemType>
class UFSets
{
public:
	UFSets(ElemType *es, int n);
	~UFSets();
	void Union(ElemType e1, ElemType e2); // ��Ȩ�ϲ�
	bool isDifferent(ElemType e1, ElemType e2); // �ж�e1,e2�Ƿ�ͬ��һ���ȼ���
	template<typename ElemType>
	friend ostream& operator<<(ostream &out, const UFSets<ElemType> &ufsets);

protected:
	// ����Ԫ��e���ڵȼ���ĸ��������±�
	int FindRootOrder(ElemType e);

private:
	ElemNode<ElemType> *sets;
	int size;

};

template<typename ElemType>
UFSets<typename ElemType>::UFSets(ElemType *es, int n)
{
	size = n;
	sets = new ElemNode<ElemType>[size];
	for (int i = 0; i < size; i++)
	{
		sets[i].data = es[i];
		sets[i].parent = -1;
	}
}

template<typename ElemType>
UFSets<typename ElemType>::~UFSets()
{
	if (sets != NULL)
		delete[] sets;
}

template<typename ElemType>
ostream& operator<<(ostream &out, const UFSets<ElemType> &ufsets)
{
	out << '[';
	for (int i = 0; i < ufsets.size; i++)
	{
		out << '(' << ufsets.sets[i].parent << ',' << ufsets.sets[i].data << ')';
		if (i != ufsets.size - 1)
			cout << ',';
	}
	out << ']';
	return out;
}

template<typename ElemType>
void UFSets<ElemType>::Union(ElemType e1, ElemType e2)
{
	int r1, r2;
	r1 = FindRootOrder(e1);
	r2 = FindRootOrder(e2);
	if (r1 != r2 && r1 != -1 && r2 != -1)
		if (sets[r1].parent > sets[r2].parent)
		{
			sets[r2].parent = sets[r1].parent + sets[r2].parent;
			sets[r1].parent = r2;
		}
		else
		{
			sets[r1].parent = sets[r1].parent + sets[r2].parent;
			sets[r2].parent = r1;
		}
}

template<typename ElemType>
bool UFSets<ElemType>::isDifferent(ElemType e1, ElemType e2)
{
	int r1, r2;
	r1 = FindRootOrder(e1);
	r2 = FindRootOrder(e2);
	return r1 != r2;
}

template<typename ElemType>
int UFSets<ElemType>::FindRootOrder(ElemType e)
{
	int i = 0;
	while (i < size&&sets[i].data != e)
		i++;
	if (i == size)
		return -1;
	else
		while (sets[i].parent > -1)
			i = sets[i].parent;
	return i;
}
