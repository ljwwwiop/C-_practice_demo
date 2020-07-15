#pragma once
#include "AdjListDirGraph.h"

void TopSort(AdjListDirGraph &graph)  //���Ϊ0�Ľ����ջ����ţ�ʹ�þ�̬��ջ�ķ������Բ����ٿ��ٿռ�
{
	int vexNum = graph.GetVexNum(), top = -1, i, count = 0;   //topΪջ��ָ�룬count��¼����Ķ������
	int *indgree = new int[vexNum];
	graph.GetVexsIndgree(indgree);
	for (i = 0; i < vexNum; i++)
		if (indgree[i] == 0)    //���Ϊ0�Ķ�����ջ
		{
			indgree[i] = top;
			top = i;
		}
	cout << "��������Ϊ:";
	while (top != -1)   //��ջ�ǿ�
	{
		cout << graph.GetElem(top);
		count++;
		int v = top;
		top = indgree[top];    //��ջ
		for (i = graph.GetFirstAdjVex(v); i != -1; i = graph.GetNextAdjVex(v, i))
			if (--indgree[i] == 0)
			{
				indgree[i] = top;
				top = i;
			}
	}
	cout << endl;
	if (count < vexNum)
		cout << "��������ʧ�ܣ���ͼ�����򻷣�";
	else
		cout << "��������ɹ���";
	cout << endl;
	delete[] indgree;
}



