#pragma once
#include "AdjListDirNetwork.h"
#include <queue>
#include <stack>

/*
	最早发生时间和最晚发生时间相等，那么该活动或者该节点就是关键路径，或关键节点。
*/

void CriticalPath(AdjListDirNetwork &network)
{
	int vexNum = network.GetVexNum();
	// 度
	int *indegree = new int[vexNum];
	// 边
	int *ve = new int[vexNum];
	int *v1 = new int[vexNum];

	int i, j;
	queue<int> q;
	stack<int> s;
	network.GetVexsIndgree(indegree);
	for (i = 0; i < vexNum; i++)
		ve[i] = 0;
	for (i = 0; i < vexNum; i++)
		if (indegree[i] == 0)
			q.push(i);

	while (!q.empty())
	{
		i = q.front();
		s.push(i);
		q.pop();
		for (j = network.GetFirstAdjVex(i); j != -1; j = network.GetNextAdjVex(i, j))
		{
			if (--indegree[j] == 0)
				q.push(j);
			if (ve[i] + network.GetWeight(i, j) > ve[j])
				ve[j] = ve[i] + network.GetWeight(i, j);
		}
	}

	i = s.top();
	s.pop();
	for (j = 0; j < vexNum; j++)
		v1[j] = ve[i];
	while (!s.empty())
	{
		i = s.top();
		s.pop();
		for (j = network.GetFirstAdjVex(i); j != -1; j = network.GetNextAdjVex(i, j))
			if (v1[j] - network.GetWeight(i, j) < v1[i])
				v1[i] = v1[j] - network.GetWeight(i, j);
	}

	for (i = 0; i < vexNum; i++)
		cout << ve[i] << " ";
	cout << endl;

	for (i = 0; i < vexNum; i++)
		cout << v1[i] << " ";
	cout << endl << "关键活动有：";

	for (i = 0; i < vexNum; i++)
	{
		int ee, el;
		ee = ve[i];
		for (j = network.GetFirstAdjVex(i); j != -1; j = network.GetNextAdjVex(i, j))
		{
			el = v1[j] - network.GetWeight(i, j);
			if (ee == el)
			{
				char v1 = network.GetElem(i), v2 = network.GetElem(j);
				cout << "(" << v1 << "," << v2 << ") ";        //输出关键活动
			}
		}
	}
	cout << endl;
	delete[] indegree;
	delete[] ve;
	delete[] v1;

}
