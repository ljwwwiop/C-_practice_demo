// 实现Linker.h 中声明的函数功能
#include "stdafx.h"
#include "Linker.h"

// 定义两个功能节点 head,end
NODE *g_head = NULL;
NODE *g_end = NULL;

void MyInputNode(NODE& pt)
{
	pt.m_next = NULL;
	pt.m_next = NULL;
	cout << "姓名:";      cin >> pt.m_szName;
	cout << "年龄:";      cin >> pt.m_Age;
	cout << "性别:";      cin >> pt.m_szSex;
	cout << "联系方式:";   cin >> pt.m_szTel;
	cout << "住址:";      cin >> pt.m_szAddr;

}

void MyOutputNode(NODE& pt)
{
	cout << "姓名：" << pt.m_szName << endl;
	cout << "年龄：" << pt.m_Age << endl;
	cout << "性别: " << pt.m_szSex << endl;
	cout << "电话: " << pt.m_szTel << endl;
	cout << "住址: " << pt.m_szAddr << endl<<endl;
}

void MyCreateList()
{
	NODE *Temp = new NODE;
	if (Temp == NULL)
	{
		cout << "创建失败！" << endl;
	}
	else
	{
		MyInputNode(*Temp);
		cout << "创建链表成功！" << endl << endl;
	}
	g_head = Temp;
	g_end = Temp;
}

// 单独创建一个节点
NODE& MyAdd_Node()
{
	NODE* pTemp = new NODE;

	if (NULL != pTemp)
	{
		MyInputNode(*pTemp);
	}

	return *pTemp;
}

NODE* MyAddNode()
{
	if (g_head == NULL || g_end == NULL)
	{
		cout << "该链表不存在，请重新创建后再操作！" << endl;
	}
	NODE *pNew = &MyAdd_Node(); // 引用使用
	g_end->m_next = pNew;
	pNew->m_prior = g_end;
	g_end = pNew;
	return NULL;
}

void MyShowList()
{
	int nCount = 1;
	if (g_head != NULL && g_end != NULL)
	{
		NODE* pt = g_head;
		cout << "<--------------打印链表-------------->" << endl;
		while (pt != NULL)
		{
			cout<<"第"<<nCount<<"个节点"<<endl;
			MyOutputNode(*pt);
			pt = pt->m_next;
			nCount++;
		}
		cout << "<--------------打印结束-------------->" << endl << endl;
	}
}

NODE& MyFindNode(char *FindName)
{
	// 根据姓名查找
	NODE * pt = g_head;
	while (true)
	{
		if (pt != NULL)
		{
			if (strcmp(pt->m_szName,FindName)==0)
			{
				return *pt;
			}
			else
			{
				pt = pt->m_next;
			}

		}
		else
		{
			cout << "查询节点不存在!" <<endl <<endl;
			return *pt;
		}
	}
}

void MyShowNode()
{
	char szNameBuf[20] = "";
	cout << "请输入查找姓名:";
	cin >> szNameBuf;
	MyOutputNode(MyFindNode(szNameBuf));
}

void MyInsertFront(char* ptName, NODE* pResFindNode, NODE* pNew)
{	
	// 前插
	if (pResFindNode == g_head)
	{
		pNew->m_next = g_head;
		g_head->m_prior = pNew;
		g_head = pNew;
	}
	else  
	{
		pNew->m_prior = pResFindNode->m_prior;
		pNew->m_next = pResFindNode;
		pResFindNode->m_prior->m_next = pNew;
		pResFindNode->m_prior = pNew;
	}
}

void MyInsertNext(char* pName, NODE* pResFindNode, NODE* pNew)
{
	// 后插
	if (pResFindNode == g_end)
	{
		pResFindNode->m_next = pNew;
		pNew->m_prior = pResFindNode;
		g_end = pNew;
	}
	else
	{
		pNew->m_next = pResFindNode->m_next;
		pResFindNode->m_next->m_prior = pNew;
		pNew->m_prior = pResFindNode;
		pResFindNode->m_next = pNew;
	}
}

void MyInsertNode()
{
	// 这个地方逻辑存在BUG 应该先判断输入的姓名是否在链表中..然后再执行操作
	char szNameBuf[20] = "";
	cout << "请输入姓名 :";
	cin >> szNameBuf;
	NODE *pNew = &MyAdd_Node();
	NODE *pResFindNode = &MyFindNode(szNameBuf);

	cout << "-------------插入操作开始-------------" << endl;
	int Chose = 1;
	cout << "1 - - - 插入节点前， 2 - - - 插入节点后(默认是节点前) ";
	cin >> Chose;
	if (Chose == 1)
	{
		MyInsertFront(szNameBuf,pResFindNode,pNew);
	}
	else if(Chose == 2)
	{
		MyInsertNext(szNameBuf, pResFindNode, pNew);
	}
	else
	{
		cout << "请输入1或者2，请从新再次尝试输入！" << endl;
	}
	cout << "-------------插入操作完成-------------" << endl << endl;
}

void MyModifyNode()
{
	char szNameBuf[20] = "";
	cout << "请输入将要修改的用户姓名：";
	cin >> szNameBuf;
	cout << "-------------修改操作开始-------------" << endl;
	NODE *pResFindNode = &MyFindNode(szNameBuf);
	MyInputNode(*pResFindNode);
	cout << "-------------修改操作结束-------------" << endl << endl;
}

void MyDeleteNode()
{
	char szNameBuf[20] = "";
	cout << "请输入要删除的用户姓名:";
	cin >> szNameBuf;

	cout << "-------------删除操作进行中-------------" << endl;
	NODE *pResFindNode = &MyFindNode(szNameBuf);
	if (pResFindNode == g_head)
	{
		g_head = pResFindNode->m_next;
		pResFindNode->m_next->m_prior = NULL;
	}
	else if (pResFindNode == g_end)
	{
		g_end = pResFindNode->m_prior;
		g_end->m_next = NULL;
	}
	else
	{
		pResFindNode->m_prior->m_next = pResFindNode->m_next;

	}
	// 释放内存
	delete []pResFindNode;
	cout << "-------------删除操作结束-------------" << endl << endl;

}

void MyClearnList()
{
	NODE *pt = g_head;
	cout << "-------------清除链表进行中-------------" << endl;
	while (pt != NULL)
	{
		delete []pt;
		pt = pt->m_next;
	}
	g_head = NULL;
	g_end = NULL;
	cout << "-------------清除链表结束-------------" << endl << endl;
}

void MyHelp()
{
	for (size_t i = 0; i < 80; i++)
		putchar('=');
	cout << endl;

	void Create();
	void Add();
	void Insert();
	void Delete();
	void Clearn();
	void Modify();
	void Find();
	void Show();
	void Help();
	void Exit();
	cout << "命令           语句         操作含义    " << endl;
	cout << "Create         创建         创建一个链表" << endl;
	cout << "Add            添加         在该链表结尾处添加一个新的节点" << endl;
	cout << "Insert         插入         在链表任意地方随意插入一个新节点" << endl;
	cout << "Delete         删除         在链表任意地方随意删除一个已有节点" << endl;
	cout << "Clearn         清空         清空整个链表" << endl;
	cout << "Modify         修改         在链表任意地方随意是修改一个已有节点" << endl;
	cout << "Show           显示         完整的显示该链表的所有节点的详细信息" << endl;
	cout << "Help           帮助         查看帮助说明文档" << endl;
	cout << "Exit           退出         退出，结束本程序" << endl;


	for (size_t i = 0; i < 80; i++)
		putchar('=');

	cout << endl << endl;
}


