#pragma once
// C++ 深拷贝
// 浅拷贝只是对指针的拷贝，拷贝后两个指针指向用以内存空间，
// 深拷贝不但对指针进行拷贝，而且对指针指向的内容也进行拷贝，经过拷贝后的指针是指向两个不同的地址
#include<iostream>
#include <string.h>
using namespace std;

class C_DeepRep 
{
public:
	// 构造函数
	C_DeepRep(const char *Name)
	{
		_Name = new char[strlen(Name)+1];
		memcpy(_Name,Name,strlen(Name)+1);
	}
	// 拷贝
	C_DeepRep(const C_DeepRep& cd)
	{
		cout << "深度拷贝" << endl;
		C_DeepRep strTemp(cd._Name);
		swap(_Name,strTemp._Name);
	}

	// 析构函数
	~C_DeepRep()
	{
		if (_Name) 
		{
			cout << "析构函数" << endl;
			delete[] _Name;
		}
	}

	void show()
	{
		cout << "Name :" << _Name <<endl;
	}

	void setName(const char *pName)
	{
		_Name = new char[strlen(pName) + 1];
		memcpy(_Name, pName, strlen(pName) + 1);
	}


private:
	char* _Name;
	int nAge;
};



