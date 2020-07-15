#pragma once
// �ڽӱ�ʵ������ͼ

#include <iostream>
#define DEFAULT_SIZE 10
using namespace std;

struct AdjListArcNode    //�߽�㶨��
{
	int adjVex;
	AdjListArcNode *nextArc;

	AdjListArcNode() :nextArc(NULL) {}

	AdjListArcNode(int _adjVex, AdjListArcNode *_nextArc = NULL)
	{
		adjVex = _adjVex;
		nextArc = _nextArc;
	}
};

struct AdjListVexNode   //�����㶨��
{
	char data;
	AdjListArcNode *firstArc;

	AdjListVexNode() :firstArc(NULL) {}

	AdjListVexNode(char VexValue, AdjListArcNode *_firstArc = NULL)
	{
		data = VexValue;
		firstArc = _firstArc;
	}
};



enum VisitStatus { VISIT, UNVISIT };

class AdjListDirGraph     //�ڽӱ�ʵ������ͼ����
{
public:
	AdjListDirGraph(int _vexMaxNum = DEFAULT_SIZE);
	AdjListDirGraph(char *Vexs, int _vexNum, int _vexMaxNum = DEFAULT_SIZE);
	~AdjListDirGraph();
	void Clear();
	void InsertArc(int vex1, int vex2);   //������Ϸ���������ƽ�бߣ���vex1������vex2
	void Show();
	int GetVexNum();
	void GetVexsIndgree(int *indegree);
	char GetElem(int vex);
	int GetFirstAdjVex(int vex);
	int GetNextAdjVex(int vex1, int vex2);

private:
	VisitStatus *tag;
	AdjListVexNode *vexTable;
	int vexNum;
	int vexMaxNum;
	int arcNum;
	int *Indegree;
};

AdjListDirGraph::AdjListDirGraph(int _vexMaxNum)
{
	vexMaxNum = _vexMaxNum;
	vexNum = 0;
	arcNum = 0;
	tag = new VisitStatus[vexMaxNum];
	vexTable = new AdjListVexNode[vexMaxNum];
	Indegree = new int[vexMaxNum];
}

AdjListDirGraph::AdjListDirGraph(char *Vexs, int _vexNum, int _vexMaxNum)
{
	vexMaxNum = _vexMaxNum;
	vexNum = _vexNum;
	arcNum = 0;
	tag = new VisitStatus[vexMaxNum];
	vexTable = new AdjListVexNode[vexMaxNum];
	Indegree = new int[vexMaxNum];
	for (int i = 0; i < vexNum; i++)
	{
		tag[i] = UNVISIT;
		vexTable[i].data = Vexs[i];
		Indegree[i] = 0;
	}
}

AdjListDirGraph::~AdjListDirGraph()
{
	if (tag != NULL)
		delete[] tag;
	Clear();
	if (vexTable != NULL)
		delete[] vexTable;
	if (Indegree != NULL)
		delete[] Indegree;
}

void AdjListDirGraph::InsertArc(int vex1, int vex2)
{
	vexTable[vex1].firstArc = new AdjListArcNode(vex2, vexTable[vex1].firstArc);
	arcNum++;
	Indegree[vex2]++;
}

void AdjListDirGraph::Show()
{
	for (int i = 0; i < vexNum; i++)
	{
		cout << vexTable[i].data << ": ";
		AdjListArcNode *p = vexTable[i].firstArc;
		while (p != NULL)
		{
			cout << p->adjVex << " ";
			p = p->nextArc;
		}
		cout << endl;
	}
	for (int i = 0; i < vexNum; i++)
		cout << Indegree[i] << " ";
	cout << endl;
}

void AdjListDirGraph::Clear()
{
	for (int i = 0; i < vexNum; i++)
	{
		while (vexTable[i].firstArc != NULL)
		{
			AdjListArcNode *p = vexTable[i].firstArc;
			vexTable[i].firstArc = p->nextArc;
			delete p;
			arcNum--;
		}
	}
}

int AdjListDirGraph::GetVexNum()
{
	return vexNum;
}

void AdjListDirGraph::GetVexsIndgree(int *indegree)
{
	for (int i = 0; i < vexNum; i++)
		indegree[i] = Indegree[i];
}

char AdjListDirGraph::GetElem(int vex)
{
	return vexTable[vex].data;
}

int AdjListDirGraph::GetFirstAdjVex(int vex)
{
	if (vexTable[vex].firstArc == NULL)
		return -1;
	return vexTable[vex].firstArc->adjVex;
}

int AdjListDirGraph::GetNextAdjVex(int vex1, int vex2)
{
	AdjListArcNode *p = vexTable[vex1].firstArc;
	while (p != NULL && p->adjVex != vex2)
		p = p->nextArc;
	if (p == NULL || p->nextArc == NULL)
		return -1;
	else
		return p->nextArc->adjVex;
}