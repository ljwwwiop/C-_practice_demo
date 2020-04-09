#pragma once
// 浅拷贝
#include <iostream>
#include <string.h>
using namespace std;

class ShallowRep 
{
public:
	// 构造函数
	ShallowRep(const char *Name)
	{

		// 判断指针是否为空
		if (Name == NULL)
		{
			Name = new char[1];
		}
		else 
		{
			Name = new char[strlen(Name)+1];
			memcpy(_Name,Name,strlen(Name)+1 );
		}
	}
	// 析构
	~ShallowRep()
	{
		cout << "这是析构函数" << endl;
		if (_Name)
		{
			delete[] _Name;
		}
	}
	void show() 
	{
		cout << "name is : "<<_Name << endl;
	}






private:
	char* _Name;
};
