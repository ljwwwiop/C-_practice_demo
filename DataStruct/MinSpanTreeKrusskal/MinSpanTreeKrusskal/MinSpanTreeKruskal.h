#pragma once
// ��С������Kruskal�㷨
#include "AdjMatrixUndirNetWork.h"
#include "MinHeap.h"
#include "UFSets.h"
#include <iostream>

using namespace std;

struct KruskalEdge
{
	int weight;
	char vex1, vex2;

	KruskalEdge() {}
	KruskalEdge(int w,char v1,char v2):weight(w),vex1(v1),vex2(v2)
	{}
	bool operator>=(KruskalEdge &other)
	{
		return weight >= other.weight;
	}
	bool operator<(KruskalEdge &other)
	{
		return weight < other.weight;
	}
	bool operator<=(KruskalEdge &other)
	{
		return weight <= other.weight;
	}
	friend ostream & operator<<(ostream &out, const KruskalEdge &e)
	{
		out << e.weight;
		return out;
	}
};


void MinSpanTreeKruskal(AdjMatrixUndirNetwork &network)
{
	int arcNum = network.GetArcNum();
	int vexNum = network.GetVexNum();
	char *vexs, vex1, vex2;
	vexs = new char[vexNum];
	for (int i = 0; i < vexNum; i++)
		network.GetElem(i, vexs[i]);
	UFSets<char> uf(vexs, vexNum);   // ȡnetwork�ĵ㼯��ʼ�����鼯
		MinHeap<KruskalEdge> edges(arcNum);
	for(int i=0;i<vexNum;i++)
		for(int j=network.FirstAdjVex(i);j!=-1;j=network.NextAdjVex(i,j))
			if (i < j)
			{
				network.GetElem(i, vex1);
				network.GetElem(j, vex2);
				KruskalEdge edge(network.GetWeight(i, j), vex1, vex2);
				edges.Insert(edge);
			}

	int count = 0;
	while (count < vexNum - 1)
	{
		KruskalEdge e;
		if (edges.DeleteTop(e))
		{
			if (uf.isDifferent(e.vex1, e.vex2))
			{
				cout << "���ӱߣ�(" << e.vex1 << "," << e.vex2 << ")��Ȩ��" << e.weight << endl;
				count++;
				uf.Union(e.vex1, e.vex2);
			}

		}
		else
		{
			cout << "��ͼ����ͨ������С������!";
		}

	}
	if(count == vexNum - 1)
		cout << "��С���������ɳɹ�!" << endl;
	delete[] vexs;


}


