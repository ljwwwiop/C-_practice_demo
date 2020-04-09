#pragma once

// 构建双链表
// 同时定义链表上的操作

struct NODE
{
	char m_szName[20];
	int m_Age;
	char m_szSex[4];
	char m_szAddr[100];
	char m_szTel[20];

	// 定义next 和 prior
	NODE *m_next;
	NODE *m_prior;
};

// 声明函数
// 输入一个刚创建好的空白节点
void MyInputNode(NODE& pt);

// 输出节点
void MyOutputNode(NODE& pt);

// 创建链表
void MyCreateList();

// 创建一个节点
NODE& MyAdd_Node();
// 链表尾部添加一个节点
NODE* MyAddNode();
void MyShowList();
// FINDNODE + SHOWNODE
void MyShowNode();
NODE& MyFindNode(char *FindName);
// 前插，插在查询节点之前
void MyInsertFront(char* ptName, NODE* pResFindNode, NODE* pNew);
// 后插，插在查询节点之后
void MyInsertNext(char* pName, NODE* pResFindNode, NODE* pNew);
void MyInsertNode();
void MyModifyNode();
void MyDeleteNode();
void MyClearnList();
void MyHelp();


