#define DELETE -1  // ɾ�����
#define EMPTY 0		// �ձ��
#define USE 1	// ʹ�ñ��
#include<iostream>
using namespace std;

// hash��ײ���ֽ������
// 1 close hash ����ַ��,����̽�ⷨ������̽��δ��Ź����ݵĿռ䣬��Ž�ȥ
// 2 open hash ���������ڵ�Ԫ��������������ͻ

template<class ElemType,class KeyType>
class ClosedHashTable
{
public:
	// �����������Լ����ء�
	ClosedHashTable(int size, int divisor);		// ���캯��
	~ClosedHashTable();
	void Traverse() const; // ��������
	int Search(const KeyType &key) const; // ����
	int Insert(const ElemType &e);
	bool Delete(const KeyType &Key);
	
	// ��������
	ClosedHashTable(const ClosedHashTable<ElemType, KeyType> &t);
		// ��ֵ����
	ClosedHashTable<ElemType, KeyType> &operator=
	(const ClosedHashTable<ElemType, KeyType> &t) ;

protected:
	// ���ݳ�Ա
	ElemType *ht;	// ɢ�б�
	int *tag;	// �������
	int maxSize;	//ɢ�б�����
	int p;	//�������鷨�ĳ���(p = 13,p����)

	// ��������
	int H(KeyType key) const;		// ɢ�к���
	int Collision(KeyType key, int i) const;	//��ͻ���

};

// ɢ�б����ʵ�ֲ���
template<class ElemType, class KeyType>
int ClosedHashTable< ElemType, KeyType>::H(KeyType key) const
{
	return key % p;
}

// ���ص�i�γ�ͻ��̽���ַ
template<class ElemType, class KeyType>
int ClosedHashTable< ElemType, KeyType>::Collision(KeyType key, int i) const
{
	return (H(key) + i) % maxSize;
}

// ����һ���յĹ�ϣ��,sizeΪɢ������,divisorΪ�����������ĳ���
template<class ElemType, class KeyType>
ClosedHashTable< ElemType, KeyType>::ClosedHashTable(int size, int divisor)
{
	maxSize = size;
	p = divisor;
	ht = new ElemType[maxSize];
	tag = new int[maxSize];

	// ������Ԫ���ÿ�
	for (int i = 0; i < maxSize; i++)
		tag[i] = 0;
}

// ����hash��
template<class ElemType, class KeyType>
ClosedHashTable< ElemType, KeyType>::~ClosedHashTable()
{
	delete[]ht;
	delete[]tag;
}

template<class ElemType, class KeyType>
void ClosedHashTable< ElemType, KeyType>::Traverse() const
{
	// visitÿ����
	for (int i = 0; i < maxSize; i++)
		if (tag[i] == DELETE)
			cout << "*";	// �Լ����
		else if (tag[i] == EMPTY)
			cout << "#";	// Ϊ��
		else
			cout << ht[i] << " " << endl;	// ��ӡֵ
}

// ��ѯ����
template <class ElemType, class KeyType>
int ClosedHashTable< ElemType, KeyType>::Search(const KeyType &key) const
{
	int c = 0;
	int i = H(key);

	while (c < maxSize && ((tag[i] == USE && ht[i] != key) || tag[i] == DELETE))
		// ��ͻ����С��maxSize����Ԫ��ht[pos] �ǿգ��ҹؼ��ֲ����
		i = Collision(key, ++c);	// �����һ��̽���ַ

	if (c >= maxSize || tag[i] == EMPTY)	//����ʧ��
		return -1;
	else
		return i;
}

// ����e ,����ɹ�return true�����򷵻�false
template <class ElemType, class KeyType>
int ClosedHashTable<ElemType, KeyType>::Insert(const ElemType &e)
{
	int c = 0;
	int i = H(e);
	int k = -1;

	while (c< maxSize && ((tag[i] == USE && ht[i] != e) || tag[i] == DELETE))
	{
		// ��ͻ����ӦС��maxSize��Ԫ��ht[i]�ǿ��ҹؼ���ֵ����
		if (k == -1 && tag[i] == DELETE)
			k = i;
		
		// ̽����һ����ַ
		i = Collision(e, ++c);
	}
	if (c >= maxSize && k == -1)	// ��ͻ�������ڵ���maxSize��˵����ϣ������
		return 0;
	else if (tag[i] == USE && ht[i] == e)
		return 0;
	else
	{
		// ����ʧ�ܣ������Ԫ��
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
	// ɾ���ؼ��֣��ɹ�true ,ʧ��false
	int i = Search(key);
	if (i == -1)
		return false;
	else
	{
		tag[i] = DELETE;
		return true;
	}

}


// ��������
template <class ElemType, class KeyType>
ClosedHashTable<ElemType, KeyType>::ClosedHashTable(const ClosedHashTable<ElemType, KeyType> &t)
{
	maxSize = t.maxSize;
	p = t.p;
	ht = new ElemType[maxSize];
	tag = new int[maxSize];

	for (int i = 0; i < maxSize; i++)
	{
		// ���ƽ�Ԫ�أ�
		ht[i] = t.ht[i];
		tag[i] = t.tag[i];
	}
}

// ���غ��� =
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
		cout << "�ɹ���" << ht.Search(27) << endl;
	if (ht.Delete(40))
	{
		cout << "�ɹ�ɾ��40" << endl;
	}
	else
	{
		cout << "ɾ��ʧ��" << endl;
	}
	ht.Traverse();

	return 0;
}








