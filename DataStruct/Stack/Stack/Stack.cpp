#include <iostream>
using namespace std;

template<typename T>
class Stack
{
private:
	// 指针 栈大小 栈个数  一次分配元素最大个数
	T *m_Data;
	int m_buffSize;
	int m_nCount;
	const int m_onceAlloc;
public:
	Stack() {}
	Stack(int buffsize = 0) :m_buffSize(buffsize), m_Data(nullptr), m_nCount(0), m_onceAlloc(10)
	{
		if (m_buffSize < 0)
		{
			cout << "Application is invalid:buffsize" << m_buffSize << endl;
			m_buffSize = 0;
		}
		else 
		{
			m_Data = new T[buffsize];
		}
	}
	~Stack()
	{
		if (m_Data != nullptr)
		{
			delete m_Data;
			m_Data = nullptr;
		}
	}
	// 栈是否被销毁
	bool DestroyStack()
	{
		delete this;
		return true;
	}
	// 清空栈
	void clear()
	{
		if (m_Data != nullptr)
		{
			delete[] m_Data;
			m_Data = nullptr;
			m_buffSize = 0;
			m_nCount = 0;
		}
		cout << " stack is already empty!" << endl;
	}
	bool isEmpty()
	{
		return m_nCount == 0;
	}
	int Getlength()
	{
		return m_nCount;
	}
	// 获取栈顶
	const T Top()
	{
		return m_Data[m_nCount-1];
	}
	void push(const T& elem)
	{
		if (m_nCount < m_buffSize)
		{
			m_Data[m_nCount++] = elem;
		}
		else
		{
			// 重新分配内存,类似vector
			T *m_TempData = new T[m_buffSize + m_onceAlloc];
			// 内存拷贝
			memcpy(m_TempData,m_Data,m_nCount*(sizeof(T)));
			m_buffSize = m_nCount + m_onceAlloc;
			m_TempData[m_nCount++] = elem;
			// 释放之前的空间
			delete[] m_Data;
			m_Data = m_TempData;
		}
	}
	void pop()
	{
		if (m_nCount == 0)
			return -1;
		else if(--m_nCount == m_buffSize -m_onceAlloc){
			m_buffSize -= m_onceAlloc;
			T *TempDate = new T[m_buffSize];
			// 拷贝过去
			memcpy(TempDate, m_Data, m_buffSize * sizeof(T));
			delete[] m_Data;
			m_Data = TempDate;
		}
		else
		{
			m_Data[m_nCount++] = 0;
		}
	}
	void Print()
	{
		if (m_nCount == 0)
		{
			cout << " stack is empty" << endl;
			return;
		}
		for (int i = 0; i < m_nCount; i++)
		{
			cout << m_Data[i] << " ";
		}
		cout << endl;
	}



};

int main()
{
	Stack<int> s(10);
	s.push(5);
	s.push(7);
	s.push(4);
	s.Print();
	cout << s.Top() << endl;
	cout << s.Getlength() << endl;

	return 0;
}
