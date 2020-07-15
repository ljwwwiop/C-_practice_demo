#include <iostream>
using namespace std;
#define DEFAULT_DIVISOR 11

// 主要是拉链法
// 链地址法节点定义
struct HashNode
{
	int key;
	HashNode* next;
	HashNode();
	HashNode(int _key,HashNode *_next = nullptr);
};

// 定义构造函数
HashNode::HashNode()
{
	next = nullptr;
}

HashNode::HashNode(int _key, HashNode *_next)
{
	key = _key;
	next = _next;
}

// 链地址法散列表定义
class OpenHashTable
{
public:
	OpenHashTable(int _div = DEFAULT_DIVISOR);
	~OpenHashTable();
	HashNode * Find(int key);
	void Insert(int key);
	void Display();

private:
	HashNode *t;
	// 被除的余数
	int div;
	int H(int key);
};

int OpenHashTable::H(int key)
{
	return key % div;
}

OpenHashTable::OpenHashTable(int _div )
{
	div = _div;
	t = new HashNode[_div];
}

OpenHashTable::~OpenHashTable()
{
	for (int i = 0; i < div; i++)
	{
		HashNode *p = t[i].next;
		while (p != nullptr)
		{
			t[i].next = p->next;
			delete p;
			p = t[i].next;
		}
	}
	delete[]t;
}

HashNode * OpenHashTable::Find(int key)
{
	int i = H(key);
	HashNode *p = t[i].next;
	while (p != nullptr && p->key != key)
		p = p->next;
	return p;
}

void OpenHashTable::Insert(int key)
{
	int i = H(key);
	HashNode *p = Find(key);
	if (p == nullptr)
		t[i].next = new HashNode(key, t[i].next);
	else
	{
		cout << "键值已经存在了" << endl;
	}
}

void OpenHashTable::Display()
{
	for (int i = 0; i < div; i++)
	{
		cout << i << " ";
		HashNode *p = t[i].next;
		while (p != nullptr)
		{
			cout << p->key << " ";
			p = p->next;
		}
		cout << endl;
	}
}

int main()
{
	int a[] = { 32,40,36,53,16,46,71,27,42,24,49,64 }, i;
	OpenHashTable ht(13);
	for (i = 0; i < 12; i++)
	{
		ht.Insert(a[i]);
	}
	ht.Display();
	if (ht.Find(71) != nullptr)
		cout << "查询成功" << endl;


	return 0;
}

