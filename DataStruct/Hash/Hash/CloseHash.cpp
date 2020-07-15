#define DELETE -1  // 删除标记
#define EMPTY 0		// 空标记
#define USE 1	// 使用标记
#include<iostream>
using namespace std;

// hash碰撞两种解决方法
// 1 close hash 开地址法,线性探测法，继续探索未存放过内容的空间，存放进去
// 2 open hash 拉链发，在单元格内用链表解决冲突

template<class ElemType,class KeyType>
class ClosedHashTable
{
public:
	// 方法声明，以及重载。
	ClosedHashTable(int size, int divisor);		// 构造函数
	~ClosedHashTable();
	void Traverse() const; // 遍历函数
	int Search(const KeyType &key) const; // 搜索
	int Insert(const ElemType &e);
	bool Delete(const KeyType &Key);
	
	// 拷贝函数
	ClosedHashTable(const ClosedHashTable<ElemType, KeyType> &t);
		// 赋值重载
	ClosedHashTable<ElemType, KeyType> &operator=
	(const ClosedHashTable<ElemType, KeyType> &t) ;

protected:
	// 数据成员
	ElemType *ht;	// 散列表
	int *tag;	// 标记数组
	int maxSize;	//散列表容量
	int p;	//除留与书法的除数(p = 13,p素数)

	// 辅助函数
	int H(KeyType key) const;		// 散列函数
	int Collision(KeyType key, int i) const;	//冲突检测

};

// 散列表类的实现部分
template<class ElemType, class KeyType>
int ClosedHashTable< ElemType, KeyType>::H(KeyType key) const
{
	return key % p;
}

// 返回第i次冲突的探查地址
template<class ElemType, class KeyType>
int ClosedHashTable< ElemType, KeyType>::Collision(KeyType key, int i) const
{
	return (H(key) + i) % maxSize;
}

// 创建一个空的哈希表,size为散列容量,divisor为除留余数法的除数
template<class ElemType, class KeyType>
ClosedHashTable< ElemType, KeyType>::ClosedHashTable(int size, int divisor)
{
	maxSize = size;
	p = divisor;
	ht = new ElemType[maxSize];
	tag = new int[maxSize];

	// 将所有元素置空
	for (int i = 0; i < maxSize; i++)
		tag[i] = 0;
}

// 销毁hash表
template<class ElemType, class KeyType>
ClosedHashTable< ElemType, KeyType>::~ClosedHashTable()
{
	delete[]ht;
	delete[]tag;
}

template<class ElemType, class KeyType>
void ClosedHashTable< ElemType, KeyType>::Traverse() const
{
	// visit每个点
	for (int i = 0; i < maxSize; i++)
		if (tag[i] == DELETE)
			cout << "*";	// 以及清空
		else if (tag[i] == EMPTY)
			cout << "#";	// 为空
		else
			cout << ht[i] << " " << endl;	// 打印值
}

// 查询操作
template <class ElemType, class KeyType>
int ClosedHashTable< ElemType, KeyType>::Search(const KeyType &key) const
{
	int c = 0;
	int i = H(key);

	while (c < maxSize && ((tag[i] == USE && ht[i] != key) || tag[i] == DELETE))
		// 冲突次数小于maxSize并且元素ht[pos] 非空，且关键字不相等
		i = Collision(key, ++c);	// 求得下一个探测地址

	if (c >= maxSize || tag[i] == EMPTY)	//查找失败
		return -1;
	else
		return i;
}

// 插入e ,插入成功return true，否则返回false
template <class ElemType, class KeyType>
int ClosedHashTable<ElemType, KeyType>::Insert(const ElemType &e)
{
	int c = 0;
	int i = H(e);
	int k = -1;

	while (c< maxSize && ((tag[i] == USE && ht[i] != e) || tag[i] == DELETE))
	{
		// 冲突次数应小于maxSize且元素ht[i]非空且关键字值不等
		if (k == -1 && tag[i] == DELETE)
			k = i;
		
		// 探测下一个地址
		i = Collision(e, ++c);
	}
	if (c >= maxSize && k == -1)	// 冲突次数大于等于maxSize，说明哈希表满了
		return 0;
	else if (tag[i] == USE && ht[i] == e)
		return 0;
	else
	{
		// 查找失败，则插入元素
		if (k == -1)
			k = i;
		ht[k] = e;
		tag[k] = USE;
		return 1;
	}
}

template <class ElemType, class KeyType>
bool ClosedHashTable<ElemType, KeyType>::Delete(const KeyType &key)
{
	// 删除关键字，成功true ,失败false
	int i = Search(key);
	if (i == -1)
		return false;
	else
	{
		tag[i] = DELETE;
		return true;
	}

}


// 拷贝函数
template <class ElemType, class KeyType>
ClosedHashTable<ElemType, KeyType>::ClosedHashTable(const ClosedHashTable<ElemType, KeyType> &t)
{
	maxSize = t.maxSize;
	p = t.p;
	ht = new ElemType[maxSize];
	tag = new int[maxSize];

	for (int i = 0; i < maxSize; i++)
	{
		// 复制进元素，
		ht[i] = t.ht[i];
		tag[i] = t.tag[i];
	}
}

// 重载函数 =
template <class ElemType, class KeyType>
ClosedHashTable<ElemType, KeyType> &ClosedHashTable<ElemType, KeyType>::operator=(const ClosedHashTable<ElemType, KeyType> &t) 
{
	if (&t != this)
	{
		delete[]ht;
		delete[]tag;
		maxSize = t.maxSize;
		p = t.p;
		ht = new ElemType[maxSize];
		tag = new int[maxSize];

		for (int i = 0; i < maxSize; i++)
		{
			ht[i] = t.ht[i];
			tag[i] = t.tag[i];
		}

	}
	return *this;
}

int main()
{
	ClosedHashTable<int, int> ht(13, 13);
	int elem[] = { 32,40,36,53,16,46,71,27,42,24,49,64 };
	for (int i = 0; i < 12; i++)
		ht.Insert(elem[i]);
	ht.Traverse();
	cout << endl;
	if (ht.Search(27) != -1)
		cout << "成功：" << ht.Search(27) << endl;
	if (ht.Delete(40))
	{
		cout << "成功删除40" << endl;
	}
	else
	{
		cout << "删除失败" << endl;
	}
	ht.Traverse();

	return 0;
}








