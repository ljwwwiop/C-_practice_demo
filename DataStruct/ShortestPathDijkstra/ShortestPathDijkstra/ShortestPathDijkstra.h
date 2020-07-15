#pragma once
// Dijkstra���·���㷨
#include "AdjMatrixDirNetwork.h"

using namespace std;

void ShortestPathDijkstra(AdjMatrixDirNetwork &network, int startVex)
{
	int vexNum = network.GetVexNum(), *dist, *path;
	int	i, j, infinity = network.GetInfinity(), min, minOrder;
	dist = new int[vexNum];
	path = new int[vexNum];
	network.SetTag(startVex, VISIT);
	for (i = 0; i < vexNum; i++)    //��ʼ��
	{
		if (i != startVex)
		{
			dist[i] = network.GetWeight(startVex, i);
			if (dist[i] == infinity)
				path[i] = -1;
			else
				path[i] = startVex;
		}
		else
		{
			dist[i] = 0;
			path[i] = -1;
		}
	}
	for (i = 1; i < vexNum; i++)   //ѭ��n-1�Σ��ҳ���startvexΪ��㣬����n-1������Ϊ�յ�����·��
	{
		min = infinity;
		for (j = 0; j < vexNum; j++)
		{
			if (network.GetTag(j) == UNVISIT && dist[j] < min)
			{
				min = dist[j];
				minOrder = j;
			}
		}
		network.SetTag(minOrder, VISIT);
		for (j = 0; j < vexNum; j++)
		{
			if (network.GetTag(j) == UNVISIT && (min + network.GetWeight(minOrder, j) < dist[j]))
			{
				dist[j] = min + network.GetWeight(minOrder, j);
				path[j] = minOrder;
			}
		}
	}
	for (i = 0; i < vexNum; i++)
		cout << dist[i] << " ";
	cout << endl;
	for (i = 0; i < vexNum; i++)
		cout << path[i] << " ";
	cout << endl;
	for (i = 0; i < vexNum; i++)
	{
		if (i != startVex)
		{
			cout << "�����" << network.GetElem(startVex) << "���յ�" << network.GetElem(i) << "�����·������Ϊ:" << dist[i];
			cout << "  ���·��Ϊ:" << network.GetElem(i);
			j = i;
			while (path[j] != -1)
			{
				j = path[j];
				cout << "<-" << network.GetElem(j);
			}
			cout << endl;
		}
	}
	delete[] dist;
	delete[] path;
}





