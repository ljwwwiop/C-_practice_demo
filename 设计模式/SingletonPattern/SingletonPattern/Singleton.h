#pragma once
#include <iostream>
using namespace std;

// 单例模式
class Singleton {
private:
	// 构造函数
	Singleton() {}
	// 析构函数
	~Singleton() {}
	// 拷贝
	Singleton(const Singleton&);
	// 重载
	Singleton & operator= (const Singleton &);
public:
	static Singleton&GetInstance()
	{
		cout << "Singleton&GetInstance " << endl;
		static Singleton instance;
		return instance;
	}
	void DoSomething();
};

