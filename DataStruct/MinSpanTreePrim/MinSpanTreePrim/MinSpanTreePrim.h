#pragma once
#include "AdjMatrixUndirNetWork.h"

using namespace std;

struct  PrimNode
{
	int lowweight;
	int nearvertex;
};

void MinSpanTreePrim(AdjMatrixUndirNetwork &network, int startVex = 0)
{
	int vexNum = network.GetVexNum(), i, j, k;
	PrimNode *vexs;
	vexs = new PrimNode[vexNum];
	vexs[startVex].lowweight = 0;
	vexs[startVex].nearvertex = -1;

	for (i = 0; i < vexNum; i++)
	{
		if (startVex != i)
		{
			vexs[i].lowweight = network.GetWeight(startVex, i);
			vexs[i].nearvertex = startVex;
		}
	}

	for (i = 1; i < vexNum; i++)
	{
		int minWeight = network.GetInfinity(), minOrder;
		for (j = 0; j < vexNum; j++)
			if (vexs[j].lowweight != 0 && vexs[j].lowweight < minWeight)
			{
				minWeight = vexs[j].lowweight;
				minOrder = j;
			}
		if (minWeight == network.GetInfinity())
		{
			cout << "��ͼ����ͨ���޷�������С������!" << endl;
			break;
		}
		else
		{
			vexs[minOrder].lowweight = 0;
			char v1, v2;
			network.GetElem(vexs[minOrder].nearvertex, v1);
			network.GetElem(minOrder, v2);
			cout << "���ӱߣ�(" << v1 << "," << v2 << "),Ȩ:" << minWeight << endl;
			for(k = network.FirstAdjVex(minOrder);k!=-1;k=network.NextAdjVex(minOrder,k))
				if (vexs[k].lowweight != 0 && network.GetWeight(minOrder, k) < vexs[k].lowweight)
				{
					vexs[k].lowweight = network.GetWeight(minOrder, k);
					vexs[k].nearvertex = minOrder;
				}
		}
	}
	if(i == vexNum)
		cout << "��С���������ɳɹ�!" << endl;
	delete[] vexs;
}




