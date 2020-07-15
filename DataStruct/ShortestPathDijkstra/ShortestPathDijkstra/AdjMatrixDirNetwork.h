#ifndef ADJMATRIX_DIR_NETWORK_H
#define ADJMATRIX_DIR_NETWORK_H

#include <iostream>
#define DEFAULT_INFINITY 100
#define DEFAULT_SIZE 10
using namespace std;

enum VisitStatus { VISIT, UNVISIT };

class AdjMatrixDirNetwork    //����Ϊ�ַ���
{
public:
	AdjMatrixDirNetwork(int vertexMaxNum = DEFAULT_SIZE, int infinite = DEFAULT_INFINITY);  //Ĭ�Ϲ��캯��������һ����ͼ
	AdjMatrixDirNetwork(char *vexs, int vertexNum, int vertexMaxNum = DEFAULT_SIZE, int infinite = DEFAULT_INFINITY);
	~AdjMatrixDirNetwork();
	void InsertArc(int vex1, int vex2, int weight);   //����Ϸ���vex1��vex2С��vexNum��vex1!=vex2��������ƽ�б�
	char GetElem(int vex);
	int GetVexNum();
	int GetArcNum();
	int GetWeight(int vex1, int vex2);
	int GetInfinity();
	int FirstAdjVex(int vex);   //���ض���vex�ĵ�һ���ڽӶ������ţ���û���򷵻�-1
	int NextAdjVex(int vex, int vex2);   //���ض���vex�������vex2����һ���ڽӶ������ţ���û���򷵻�-1
	void Display();
	VisitStatus GetTag(int vex);   //����Ϸ�
	int SetTag(int vex, VisitStatus _tag);  //����״̬

private:
	char *vertexes;
	VisitStatus *tag;
	int **arcs;
	int vexNum, vexMaxNum, arcNum;
	int infinity;
};

AdjMatrixDirNetwork::AdjMatrixDirNetwork(int vertexMaxNum, int infinite)
{
	vexMaxNum = vertexMaxNum;
	vexNum = 0;
	arcNum = 0;
	infinity = infinite;
	vertexes = new char[vexMaxNum];
	tag = new VisitStatus[vexMaxNum];
	arcs = new int *[vexMaxNum];
	for (int i = 0; i < vexMaxNum; i++)
		arcs[i] = new int[vexMaxNum];
}

AdjMatrixDirNetwork::AdjMatrixDirNetwork(char *vexs, int vertexNum, int vertexMaxNum, int infinite)
{
	vexMaxNum = vertexMaxNum;
	vexNum = vertexNum;
	infinity = infinite;
	arcNum = 0;
	vertexes = new char[vexMaxNum];
	tag = new VisitStatus[vexMaxNum];
	arcs = new int *[vexMaxNum];
	for (int i = 0; i < vexMaxNum; i++)
		arcs[i] = new int[vexMaxNum];
	for (int i = 0; i < vexMaxNum; i++)
	{
		vertexes[i] = vexs[i];
		tag[i] = UNVISIT;
		for (int j = 0; j < vexMaxNum; j++)
			arcs[i][j] = infinity;
	}
}

AdjMatrixDirNetwork::~AdjMatrixDirNetwork()
{
	if (vertexes != NULL)
		delete[] vertexes;
	if (tag != NULL)
		delete[] tag;
	if (arcs != NULL)
	{
		for (int i = 0; i < vexNum; i++)
			delete[] arcs[i];
		delete[] arcs;
	}
}

void AdjMatrixDirNetwork::InsertArc(int vex1, int vex2, int weight)
{
	arcs[vex1][vex2] = weight;
	arcNum++;
}

char AdjMatrixDirNetwork::GetElem(int vex)
{
	return vertexes[vex];
}

int AdjMatrixDirNetwork::GetVexNum()
{
	return vexNum;
}

int AdjMatrixDirNetwork::GetArcNum()
{
	return arcNum;
}

int AdjMatrixDirNetwork::GetWeight(int vex1, int vex2)
{
	return arcs[vex1][vex2];
}

int AdjMatrixDirNetwork::GetInfinity()
{
	return infinity;
}

int AdjMatrixDirNetwork::FirstAdjVex(int vex)
{
	for (int i = 0; i < vexNum; i++)
		if (arcs[vex][i] != infinity)
			return i;
	return -1;
}

int AdjMatrixDirNetwork::NextAdjVex(int vex, int vex2)
{
	for (int i = vex2 + 1; i < vexNum; i++)
		if (arcs[vex][i] != infinity)
			return i;
	return -1;
}

void AdjMatrixDirNetwork::Display()
{
	if (vexNum != 0)
	{
		for (int i = 0; i < vexNum; i++)
		{
			cout << "[ ";
			for (int j = 0; j < vexNum; j++)
				cout << arcs[i][j] << " ";
			cout << "]" << endl;
		}
	}
}

VisitStatus AdjMatrixDirNetwork::GetTag(int vex)
{
	return tag[vex];
}

int AdjMatrixDirNetwork::SetTag(int vex, VisitStatus _tag)
{
	if (vex >= vexNum)
		return 0;
	tag[vex] = _tag;
	return 1;
}



#endif