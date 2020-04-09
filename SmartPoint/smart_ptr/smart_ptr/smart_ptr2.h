#pragma once
#include <functional>
/*
	functional模板 这个包的作用：
	map<string, function<int(int, int)>> binops;
	binops = {
		{"+",add},
		{"-",std::minus<int>()},
		{"/",divide()},
		{"*",[](int i,int j) {return i*j; }},
		{"%",mod}
	};
	binops["+"](10, 5); //调用add(10,5);
	binops["-"](10, 5); //使用minus<int>对象的调用运算符
	binops["/"](10, 5); //使用divide对象的调用运算符
	binops["*"](10, 5); //调用lambda函数对象

*/

using namespace std;
// 模拟shared_ptr实现一个智能指针
template<class T>
class smart_ptr 
{
public:
	// 无参数构造
	smart_ptr();
	// 一个参数构造
	explicit smart_ptr(T*);
	// 拷贝
	smart_ptr(const smart_ptr&);
	// 两个参数的构造
	smart_ptr(T*, function<void(T*)>);
	// 重载
	smart_ptr& operator=(const smart_ptr&);
	// 重载
	T& operator*() const;
	// 重载访问运算符号
	T* operator->() const;

	// 析构
	~smart_ptr();
	// 向bool类型转换
	explicit operator bool() const;

	// 检测是否唯一
	bool unique();
	// 重置函数
	void reset();
	void reset(T*);
	void reset(T*,function<void(T*)>);
	// 释放
	T* release();
	// 获取地址
	T* get() const;

private:
	// 默认delete
	// function<void(T*)>初始化一个T* 类型的default_del
	static function<void(T*)> default_del;
private:
	unsigned* m_p_use_count = nullptr;
	T* m_pobject = nullptr;
	function<void(T*)> m_del = default_del;
};

// 定义好默认delete函数
template<class T>
function<void(T*)> smart_ptr<T>::default_del = [](T *p) 
{delete p; p = nullptr; }

// 传递一个模式T，还有一个任意参数args ，同一个模式T可以传递任意参数
// C++11的新特点 &&右值引用，move语义移动,forword完美转换
// 右值减少内存拷贝，提高性能， forword将左值转换为右值
template <typename T, typename... Args>
smart_ptr<T> make_smart(Args&&... args)
{
	smart_ptr<T> sp(new T(std::forward<Args>(args)...));
	return sp;
}

template<class T>
smart_ptr<T>::smart_ptr():m_pobject(nullptr),m_p_use_count(new unsigned(1))
{
}

template<class T>
smart_ptr<T>::smart_ptr(T *p):m_pobject(p),m_p_use_count(new unsigned(1))
{

}

template<class T>
smart_ptr<T>::smart_ptr(T *p,function<void(T*)> del):m_pobject(p),m_p_use_count(new unsigned(1)),m_del(del)
{
}

// 拷贝函数，当有一个新的指针对象进来，计数器++
template<class T>
smart_ptr<T>::smart_ptr(const smart_ptr & s):m_pobject(s.m_pobject), m_p_use_count(s.m_p_use_count),m_del(s.m_del)
{
	(*m_p_use_count)++;
}

template<class T>
smart_ptr<T>& smart_ptr<T>::operator =(const smart_ptr &s)
{
	m_del = s.m_del;
	// 递减本对象的引用计数
	++(*s.m_p_use_count);
	// 如果管理的对象没有其他用户了，则释放对象分配的成员
	if (--(*m_p_use_count) == 0)
	{
		m_del(m_pobject);
		delete m_p_use_count;
	}
	m_p_use_count = s.m_p_use_count;
	m_pobject = s.m_pobject;
	// 返回该对象
	return *this;
};

template<class T>
T& smart_ptr<T>::operator*() const
{
	return *m_pobject;
}

template<class T>
T* smart_ptr<T>::operator->() const
{
	return &this->operator*();
}

template<class T>
smart_ptr<T>::~smart_ptr()
{
	if (--(*m_p_use_count) == 0)
	{
		m_del(m_pobject);
		m_pobject = nullptr;

		delete m_p_use_count;
		m_p_use_count = nullptr;
	}
}

template<class T>
bool smart_ptr<T>::unique()
{
	return *m_p_use_count == 1;
}

template<class T>
void smart_ptr<T>::reset()
{
	(*m_p_use_count)--;
	if (*m_p_use_count == 0) 
	{
		m_del(m_pobject);
	}
	m_pobject = nullptr;
	*m_p_use_count = 1;
	m_del = default_del;
}

template<class T>
void smart_ptr<T>::reset(T *p)
{
	(*m_p_use_count)--;
	if (*m_p_use_count == 0)
	{
		m_del(m_pobject);
	}
	m_pobject = p;
	*m_p_use_count = 1;
	m_del = default_del;

}

template<class T>
T*  smart_ptr<T>::release()
{
	(*m_p_use_count)--;
	if (*m_p_use_count == 0)
	{
		m_del(m_pobject);
	}
	auto p = m_pobject;
	m_pobject = nullptr;
	return p;
}

template<class T>
T* smart_ptr<T>::get() const
{
	return m_pobject;
}

template<class T>
smart_ptr<T>::operator bool ()const
{
	return m_pobject != nullptr;
}





















